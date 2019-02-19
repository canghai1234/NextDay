#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "Singleton.h"

#include "HttpRequest.h"
#include "ParsingJson.h"
#include "DateTime.h"
#include "NetworkData.h"

#include <QDebug>

class Backend : public QObject, public Singleton<Backend>
{
    Q_OBJECT
public:
    Q_INVOKABLE void requestSource();
    Q_INVOKABLE QByteArray getTodayByte();
    Q_INVOKABLE void requestSource(QByteArray date);

    void initNetworkModel();

    //用来给 QML 获取图片以及文字等相关的资源
    Q_INVOKABLE QString getImageURL();
    Q_INVOKABLE QString getGeoInfo();
    Q_INVOKABLE QString getBackgroundColor();
    Q_INVOKABLE QString getComment1();
    Q_INVOKABLE QString getComment2();
    Q_INVOKABLE QString getDay();
    Q_INVOKABLE QString getWeek();
    Q_INVOKABLE QString getEvent();
    Q_INVOKABLE QString getAuthor();
    Q_INVOKABLE bool hasShort();

    Q_INVOKABLE double getDPI();

    Q_INVOKABLE void setCurrentShowDate(const QByteArray &currentShowDate);

signals:
    void sig_requestSourceSucceed();

private slots:
    void slotP_parsingJsonOK(NetworkData& data);
private:
    HttpRequest* _http;
    ParsingJson* _parJson;
    DateTime* _date;
    NetworkData _lastSource;

    QByteArray _currentShowDate;
};

#endif // BACKEND_H
