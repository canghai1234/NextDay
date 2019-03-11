#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "Singleton.h"

#include "HttpRequest.h"
#include "ParsingJson.h"
#include "DateTime.h"
#include "common.h"
#include "ImageDownload.h"
#include "Profile.h"

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

    Q_INVOKABLE double getSettingItemHeight();

    Q_INVOKABLE QString getTodayImagePath();
    Q_INVOKABLE void saveTodayBackgroundImage();

    Q_INVOKABLE double getFontScale(); //根据屏幕获取比例
    Q_INVOKABLE void setTextScaleUser(int scale); //用户自己调整的比例
    Q_INVOKABLE int getTextScaleUser();

private:
    void requestSource(QByteArray date);
    void requestSource(QByteArray date1,QByteArray date2);

signals:
    void sig_hasMusic(bool hasMusic);
    void sig_musicURL(QString url);
    void sig_musicTitle(QString title);
    void sig_musicArtist(QString artist);

private slots:
    void slotP_parsingJsonOK(NetworkData& data);
    void slotP_dataUpdated(qint64 index);

private:
    HttpRequest* _http;
    ParsingJson* _parJson;
    DateTime* _date;
    Profile* _profile;

    ModelManager* _todayModelManage;
    ModelManager* _historyModelManage;

    ImageDownload* _download;
    bool _isHistoryModel;
    void initNetworkModel();

    QByteArray _todayDateKey;
    int _currentIndex;
    QString _rootPath;
};

#endif // BACKEND_H
