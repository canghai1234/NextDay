#include "Backend.h"
#include <QQmlApplicationEngine>
#include <QMetaType>
#include <QGuiApplication>
#include <QScreen>
#include <QFontMetrics>
#define PRELOAD_DAYS 7

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

    QObject::connect(_http,SIGNAL(sig_recvApiData(QByteArray)),_parJson,SLOT(slot_parsingSource(QByteArray)),Qt::UniqueConnection);
    QObject::connect(_parJson,SIGNAL(sig_parsingOK(NetworkData&)),this,SLOT(slotP_parsingJsonOK(NetworkData&)),Qt::UniqueConnection);
}

double Backend::getFontScale()
{
#if defined(Q_OS_ANDROID)
    double width = QGuiApplication::primaryScreen()->physicalSize().width();
#elif defined(Q_OS_WIN)
    double width = 71.0;
#endif
    double res = width / 71.0;
    return res;
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

    QByteArray firstDateKey = _todayModelManage->firstDate();
    qint64 dayToFirst = _date->daysTo( data.dateKey,firstDateKey);
    _todayModelManage->setData(newData,dayToFirst);
}

void Backend::init()
{
    initNetworkModel();
    _isHistoryModel = false;
}

void Backend::qmlIndexChanged(int currentIndex)
{
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
        if(day.size() > 0)
            requestSource(day);
    }
}



