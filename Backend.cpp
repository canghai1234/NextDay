#include "Backend.h"
#include <QQmlApplicationEngine>
#include <QMetaType>

void Backend::requestSource()
{
    _http->requestSource(_date->getToday());
}

void Backend::requestSource(QByteArray date)
{
    _http->requestSource(date);
}

void Backend::init()
{
    qRegisterMetaType<NetworkData>("NetworkData");
    _http = new HttpRequest;
    _parJson = new ParsingJson;
    _date = new DateTime;
    QObject::connect(_http,SIGNAL(sig_recvApiData(QByteArray)),_parJson,SLOT(slot_parsingSource(QByteArray)),Qt::UniqueConnection);
    QObject::connect(_parJson,SIGNAL(sig_parsingOK(NetworkData&)),this,SLOT(slotP_parsingJsonOK(NetworkData&)),Qt::UniqueConnection);
}

void Backend::slotP_parsingJsonOK(NetworkData &data)
{
    _lastSource = data;
    qDebug() << "data.image_big" << data.image_big << "\n"
             << "data.image_big2x" << data.image_big2x << "\n"
             << "data.image_big568h2x" << data.image_big568h2x << "\n"
             << "data.image_big568h3x" << data.image_big568h3x << "\n"
             << "data.image_iphoneX" << data.image_iphoneX << "\n"
             << "data.image_small" << data.image_small << "\n"
             << "data.image_small2x" << data.image_small2x << "\n"
             << "data.image_small568h2x" << data.image_small568h2x;
    emit sig_requestSourceSucceed();
}

