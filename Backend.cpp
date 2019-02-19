#include "Backend.h"
#include <QQmlApplicationEngine>
#include <QMetaType>
#include <QGuiApplication>
#include <QScreen>
#include <QFontMetrics>

void Backend::requestSource()
{
    _http->requestSource(_date->getToday());
}

QByteArray Backend::getTodayByte()
{
    return _date->getToday();
}

void Backend::requestSource(QByteArray date)
{
    _http->requestSource(date);
}

void Backend::initNetworkModel()
{
    qRegisterMetaType<NetworkData>("NetworkData");
    _http = new HttpRequest;
    _parJson = new ParsingJson;
    _date = new DateTime;
    QObject::connect(_http,SIGNAL(sig_recvApiData(QByteArray)),_parJson,SLOT(slot_parsingSource(QByteArray)),Qt::UniqueConnection);
    QObject::connect(_parJson,SIGNAL(sig_parsingOK(NetworkData&)),this,SLOT(slotP_parsingJsonOK(NetworkData&)),Qt::UniqueConnection);
}

QString Backend::getImageURL()
{
    return _lastSource.image_big568h3x;
}

QString Backend::getGeoInfo()
{
    return _lastSource.reverse;
}

QString Backend::getBackgroundColor()
{
    return _lastSource.background;
}

QString Backend::getComment1()
{
    if(_lastSource.hasShort)
        return _lastSource.shortText;
    else
        return _lastSource.comment1;
}

QString Backend::getComment2()
{
    if(_lastSource.hasShort)
        return "";
    else
        return _lastSource.comment2;
}

QString Backend::getDay()
{
    return _date->getDay(_lastSource.dateKey);
}

QString Backend::getWeek()
{
    QString week = _date->getWeek(_lastSource.dateKey);
    QString month = _date->getMonthShort(_lastSource.dateKey);
    QString res = month + ". " + week;
    res = res.toUpper();
    //        qDebug() << "res" << res << res.toUpper();
    return res;
}

QString Backend::getEvent()
{
    QString res = "";
    if(_lastSource.hasEvent)
        res += ", " + _lastSource.event;
    return res;
}

QString Backend::getAuthor()
{
    QString res = "@" + _lastSource.name;
    return res;
}

bool Backend::hasShort()
{
    return _lastSource.hasShort;
}

double Backend::getDPI()
{
    return QGuiApplication::primaryScreen()->logicalDotsPerInch();
}

void Backend::slotP_parsingJsonOK(NetworkData &data)
{
    _lastSource = data;
    emit sig_requestSourceSucceed();
}

void Backend::setCurrentShowDate(const QByteArray &currentShowDate)
{
    _currentShowDate = currentShowDate;
    qDebug() << _currentShowDate;
}

