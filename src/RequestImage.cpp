#include "RequestImage.h"
#include <QVariant>
#include <QNetworkReply>
#include <QPixmap>

RequestImage::RequestImage(QObject *parent) : QObject(parent)
{
    _manage = new QNetworkAccessManager();
    connect(_manage,SIGNAL(finished(QNetworkReply*)),this, SLOT(slotP_reply(QNetworkReply*)),Qt::UniqueConnection);
}

void RequestImage::slotP_reply(QNetworkReply *reply)
{
    QVariant nCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    int statusCode = nCode.toInt();

//    200 - 请求成功
//    301 - 资源（网页等）被永久转移到其它URL
//    404 - 请求的资源（网页等）不存在
//    500 - 内部服务器错误

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(bytes);

        // 缓存到本地
//        QFile file("E:/head.jpg");
//        if (file.open(QIODevice::Append))
//            file.write(bytes);

//        file.close();

    }
    else
    {
        qDebug() << "error" << statusCode;
        qDebug() << reply->errorString();
        qDebug() << "url " << reply->request().url();
        foreach (QByteArray array, reply->request().rawHeaderList()) {
            qDebug() << array << request.rawHeader(array);
        }
        return;
    }
}
