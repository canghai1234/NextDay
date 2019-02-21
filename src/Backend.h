#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "Singleton.h"

#include "HttpRequest.h"
#include "ParsingJson.h"
#include "DateTime.h"
#include "NetworkData.h"


#include "DateModel/ModelManager.h"

#include <QDebug>

class Backend : public QObject, public Singleton<Backend>
{
    Q_OBJECT
public:

    void init();
    ModelManager* getTodayListManage()
    {
        return _todayModelManage;
    }



    Q_INVOKABLE void qmlRequestYesterday();
    Q_INVOKABLE void qmlRequestTomorrow();

    Q_INVOKABLE void requestSource();
    Q_INVOKABLE QByteArray getTodayByte();
    Q_INVOKABLE void requestSource(QByteArray date);

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
    QList<QVariant> todayListChanged();
private slots:
    void slotP_parsingJsonOK(NetworkData& data);
private:
    HttpRequest* _http;
    ParsingJson* _parJson;
    DateTime* _date;
    NetworkData _lastSource;
    ModelManager* _todayModelManage;
    ModelManager* _historyModelManage;

    QByteArray _currentShowDate;

    bool _isHistoryModel;
    void initNetworkModel();

};

#endif // BACKEND_H
