#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class HttpRequest : public QObject
{
    Q_OBJECT
public:
    explicit HttpRequest(QObject *parent = nullptr);
    void requestSource(QByteArray date);
    void requestSource(QByteArray date1,QByteArray date2);
signals:
    void sig_recvApiData(QByteArray data);

private slots:
    void slotP_reply(QNetworkReply *reply);

private:
    QNetworkAccessManager* _manage;
    QNetworkRequest request;

    QByteArray getHttpHeaderDate();
    QString getNetworkErrorString(QNetworkReply::NetworkError error);
    QString getHttpErrorCodeString(int errorCode);
};

#endif // HTTPREQUEST_H
