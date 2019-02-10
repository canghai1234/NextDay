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
    Q_INVOKABLE void requestSource(QByteArray date);
    void init();
    Q_INVOKABLE QString getImageURL()
    {
        return _lastSource.image_big568h3x;
    }

    Q_INVOKABLE QString getGeoInfo()
    {
        return _lastSource.reverse;
    }

    Q_INVOKABLE QString getBackgroundColor()
    {
        return _lastSource.background;
    }

    Q_INVOKABLE QString getComment1()
    {
        if(_lastSource.hasShort)
            return _lastSource.shortText;
        else
            return _lastSource.comment1;
    }

    Q_INVOKABLE QString getComment2()
    {
        if(_lastSource.hasShort)
            return "";
        else
            return _lastSource.comment2;
    }

    Q_INVOKABLE QString getDay()
    {
        return _date->getDay(_lastSource.dateKey);
    }

    Q_INVOKABLE QString getWeek()
    {
        QString week = _date->getWeek(_lastSource.dateKey);
        QString month = _date->getMonthShort(_lastSource.dateKey);
        QString res = month + "." + week;
        res = res.toUpper();
        if(_lastSource.hasEvent)
            res += "," + _lastSource.event;
        return res;
    }

    Q_INVOKABLE QString getAuthor()
    {
        QString res = "@" + _lastSource.name;
        return res;
    }

signals:
    void sig_requestSourceSucceed();

private slots:
    void slotP_parsingJsonOK(NetworkData& data);
private:
    HttpRequest* _http;
    ParsingJson* _parJson;
    DateTime* _date;
    NetworkData _lastSource;
};

#endif // BACKEND_H
