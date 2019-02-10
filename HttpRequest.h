#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>
#include <QNetworkAccessManager>

class HttpRequest : public QObject
{
    Q_OBJECT
public:
    explicit HttpRequest(QObject *parent = nullptr);
    void requestSource(QByteArray date);
signals:
    void sig_recvApiData(QByteArray data);

private slots:
    void slotP_reply(QNetworkReply *reply);

private:
    QNetworkAccessManager* _manage;
    QNetworkRequest request;

    QByteArray getHttpHeaderDate();
};

#endif // HTTPREQUEST_H
