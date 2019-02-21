#ifndef REQUESTIMAGE_H
#define REQUESTIMAGE_H

#include <QObject>
#include <QNetworkAccessManager>

class RequestImage : public QObject
{
    Q_OBJECT
public:
    explicit RequestImage(QObject *parent = nullptr);

signals:

private slots:
    void slotP_reply(QNetworkReply *reply);

private:
    QNetworkAccessManager* _manage;
    QNetworkRequest request;
};

#endif // REQUESTIMAGE_H
