#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>
#include <QNetworkAccessManager>

class HttpRequest : public QObject
{
    Q_OBJECT
public:
    explicit HttpRequest(QObject *parent = nullptr);

signals:
    void sig_recvApiData(QByteArray data);

private slots:
    void slotP_reply(QNetworkReply *reply);

public slots:
    void slot_requestData(QByteArray date);

private:
    QNetworkAccessManager* _manage;
    QNetworkRequest request;
    QByteArray getHeaderURL();
    QByteArray getJsonData();
    QByteArray getHttpHeaderDate();
    QByteArray getHttpHeaderAuthorization();
};

#endif // HTTPREQUEST_H
