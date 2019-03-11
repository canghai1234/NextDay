#include "Backend.h"
#include <QQmlApplicationEngine>
#include <QMetaType>
#include <QGuiApplication>
#include <QScreen>
#include <QFontMetrics>
#include <QPixmap>
#include <QStandardPaths>
#include <QDir>

#define PRELOAD_DAYS 15

void Backend::requestSource(QByteArray date)
{
    _http->requestSource(date);
}

void Backend::requestSource(QByteArray date1, QByteArray date2)
{
    _http->requestSource(date1,date2);
}

void Backend::initNetworkModel()
{
    qRegisterMetaType<NetworkData>("NetworkData");
    _http = new HttpRequest;
    _parJson = new ParsingJson;
    _date = new DateTime;
    _todayModelManage = new ModelManager(this);
    _todayModelManage->initData();
    _historyModelManage = new ModelManager;
    _historyModelManage->initData();

    _download = new ImageDownload(this);

    QObject::connect(_http,SIGNAL(sig_recvApiData(QByteArray)),_parJson,SLOT(slot_parsingSource(QByteArray)),Qt::UniqueConnection);
    QObject::connect(_parJson,SIGNAL(sig_parsingOK(NetworkData&)),this,SLOT(slotP_parsingJsonOK(NetworkData&)),Qt::UniqueConnection);
    QObject::connect(_todayModelManage,SIGNAL(sig_dataReceived(qint64)),this,SLOT(slotP_dataUpdated(qint64)),Qt::UniqueConnection);

}

double Backend::getFontScale()
{
#if defined(Q_OS_ANDROID)
    double width = QGuiApplication::primaryScreen()->physicalSize().width();
    double height = QGuiApplication::primaryScreen()->physicalSize().height();
    width = width * (height / width) / (18.0 / 9.0);
#elif defined(Q_OS_WIN)
    double width = 71.0;
#endif
    double res = width / 71.0;
    return res;
}

void Backend::setTextScaleUser(int scale)
{
    _profile->setTextScaleUser(scale);
}

int Backend::getTextScaleUser()
{
    return _profile->getTextScaleUser();
}

double Backend::getSettingItemHeight()
{
    double dpiY = QGuiApplication::primaryScreen()->logicalDotsPerInchY();
    double cmDots = dpiY / 2.54 ;
    return cmDots;
}

QString Backend::getTodayImagePath()
{
    QString res = _rootPath + "/today/" +  _todayDateKey + ".png";
    return res;
}

void Backend::saveTodayBackgroundImage()
{
    QString res = _rootPath + "/source/" + _todayDateKey + ".png";
    QString url = _todayModelManage->imagePath(_currentIndex);
    _download->setFile(url , res);
}

void Backend::slotP_parsingJsonOK(NetworkData &data)
{
    dataUI newData;
    newData.dataInited = true;
    newData.dateKey = data.dateKey;
    newData.day = _date->getDay(data.dateKey);

    QString week = _date->getWeek(data.dateKey);
    QString month = _date->getMonthShort(data.dateKey);
    newData.week = QString(month + ". " + week).toUpper();

    if(data.hasEvent)
        newData.event = ", " + data.event;
    newData.geoInfo = data.reverse;

    newData.hasShort = data.hasShort;
    if(data.hasShort)
        newData.comment1 = data.shortText;
    else
    {
        newData.comment1 = data.comment1;
        newData.comment2 = data.comment2;
    }
    newData.backgroundColor = data.background;

    newData.imageURL = data.image_big568h3x;

    if(data.hasAuthorInfo)
        newData.author = "@" + data.name;

    newData.hasMusic = data.hasMusic;
    newData.music_artist = data.music_artist;
    newData.music_title = data.music_title;
    newData.music_Url = data.music_Url;

    QByteArray firstDateKey = _todayModelManage->firstDate();
    qint64 dayToFirst = _date->daysTo( data.dateKey,firstDateKey);
    _todayModelManage->setData(newData,dayToFirst);
}

void Backend::slotP_dataUpdated(qint64 index)
{
    if(index == _currentIndex)
    {
        int currentIndex = static_cast<int>(index);
        bool hasMusic = _todayModelManage->hasMusic(currentIndex);
        QString musicTitle = _todayModelManage->musicTitle(currentIndex);
        QString musicArtist = _todayModelManage->musicArtist(currentIndex);
        QString musicURL = _todayModelManage->musicURL(currentIndex);
        emit sig_hasMusic(hasMusic);
        emit sig_musicURL(musicURL);
        emit sig_musicTitle(musicTitle);
        emit sig_musicArtist(musicArtist);
    }
}

void Backend::init()
{
    initNetworkModel();

#ifdef Q_OS_ANDROID
    _rootPath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
#else
    _rootPath = qApp->applicationDirPath();
#endif

    bool exist;
    _rootPath +=  "/NextDay" ;
    QDir folderToday(_rootPath + "/today");
       //判断创建文件夹是否存在
    exist = folderToday.exists();
    if(!exist)
        folderToday.mkpath(".");

    QDir folderSource(_rootPath + "/source");
       //判断创建文件夹是否存在
    exist = folderSource.exists();
    if(!exist)
        folderSource.mkpath(".");


    QString settingPath = _rootPath + "/settings.ini" ;
    _profile = new Profile(this);
    _profile->readParameter(settingPath);
}

void Backend::qmlIndexChanged(int currentIndex)
{
    _currentIndex = currentIndex;
    int modelCount = _todayModelManage->dateModel()->getCount();
    if(0 == modelCount)
    {
        dataUI todayData;
        todayData.dataInited = false;
        todayData.dateKey = _date->getToday();
        _todayModelManage->push_back(todayData);
        modelCount = _todayModelManage->dateModel()->getCount();
    }

    if(currentIndex == (modelCount - 1))
    {
        QByteArray dateKey = _todayModelManage->lastDate();
        QByteArray firstDate ,lastDate;
        for(int day = 0; day < PRELOAD_DAYS; ++ day)
        {
            dataUI yesterdayData;
            yesterdayData.dataInited = false;
            yesterdayData.dateKey = _date->getYesterday(dateKey,day+1);
            _todayModelManage->push_back(yesterdayData);
            if(0 == day)
                firstDate = yesterdayData.dateKey;
            else if((PRELOAD_DAYS -1) == day)
                lastDate = yesterdayData.dateKey;
        }
        requestSource(lastDate,firstDate);
    }

    bool dataInited = _todayModelManage->dataInited(currentIndex);
    if(!dataInited)
    {
        QByteArray day = _todayModelManage->dateKey(currentIndex);
        _todayDateKey = day;
        if(day.size() > 0)
            requestSource(day);
    }
    else
    {
        _todayDateKey = _todayModelManage->dateKey(currentIndex);
        bool hasMusic = _todayModelManage->hasMusic(currentIndex);
        QString musicTitle = _todayModelManage->musicTitle(currentIndex);
        QString musicArtist = _todayModelManage->musicArtist(currentIndex);
        QString musicURL = _todayModelManage->musicURL(currentIndex);
        emit sig_hasMusic(hasMusic);
        emit sig_musicURL(musicURL);
        emit sig_musicTitle(musicTitle);
        emit sig_musicArtist(musicArtist);
    }
}



