#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "Singleton.h"

#include "HttpRequest.h"
#include "ParsingJson.h"
#include "DateTime.h"
#include "common.h"

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

    Q_INVOKABLE void qmlIndexChanged(int currentIndex);
    Q_INVOKABLE double getFontScale();

private:
    void requestSource(QByteArray date);
    void requestSource(QByteArray date1,QByteArray date2);

signals:


private slots:
    void slotP_parsingJsonOK(NetworkData& data);
private:
    HttpRequest* _http;
    ParsingJson* _parJson;
    DateTime* _date;

    ModelManager* _todayModelManage;
    ModelManager* _historyModelManage;

    bool _isHistoryModel;
    void initNetworkModel();

};

#endif // BACKEND_H
