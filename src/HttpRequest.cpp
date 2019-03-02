#include "HttpRequest.h"
#include <QNetworkReply>
#include <QUrl>
#include <QTimeZone>
#include <QCryptographicHash>
#include <QDate>
#include "apikey.h"

#include <QDebug>

#define HOST QByteArray("http://api.nextday.im")
#define URL QByteArray("/api/calendar")


HttpRequest::HttpRequest(QObject *parent) : QObject(parent)
{
    _manage = new QNetworkAccessManager();
    connect(_manage,SIGNAL(finished(QNetworkReply*)),this, SLOT(slotP_reply(QNetworkReply*)),Qt::UniqueConnection);
}

void HttpRequest::requestSource(QByteArray date)
{
    requestSource(date,date);
}

void HttpRequest::requestSource(QByteArray date1, QByteArray date2)
{
    //1. 验证 data 的有效性
    QDate dateObj = QDate::fromString(QString(date1),"yyyyMMdd");
    if(!dateObj.isValid())
        return;

    if(date1 != date2)
    {
        dateObj = QDate::fromString(QString(date2),"yyyyMMdd");
        if(!dateObj.isValid())
            return;
    }

    //2. 构造 http url
    QByteArray headerUrl = URL + QByteArray("?from=") + date1 + QByteArray("&to=") + date2;
    QByteArray urlAddress = HOST + headerUrl;
    QUrl url(QString::fromStdString(urlAddress.toStdString()));
    request.setUrl(url);

    //3. 构造 http header 数据
    //3.1 获取 "Date" 数据
    QByteArray headerDate;
    {
        QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
        QString dataString = currentDateTime.toString("yyyy-MM-dd HH:mm:ss.zzz ");
        QString timezone = currentDateTime.timeZone().displayName(QTimeZone::StandardTime,QTimeZone::ShortName,QLocale::UncodedLanguages);
        headerDate = (dataString + timezone).toUtf8() ;
    }

    //3.2 获取 "Authorization" 数据
    QByteArray headerAuthorization;
    {
        QByteArray byteToMd5;
        QByteArray charAnd = QByteArray("&");
        byteToMd5 = headerUrl + charAnd + PARTNERNAME + charAnd + headerDate + charAnd + PARTNERSECRET ;
        QByteArray md5Value = QCryptographicHash::hash(byteToMd5, QCryptographicHash::Md5).toHex();
        headerAuthorization = PARTNERNAME + QByteArray(":") + md5Value;
    }

    //4. 网络请求
    request.setRawHeader("Date",headerDate);
    request.setRawHeader("Authorization",headerAuthorization);
    request.setRawHeader("Connection","Keep-Alive");
    request.setRawHeader("host","api.nextday.im");

    _manage->get(request);
}

void HttpRequest::slotP_reply(QNetworkReply *reply)
{
    QVariant nCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    int statusCode = nCode.toInt();

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray answer = reply->readAll();
//        qDebug() << answer;
        emit sig_recvApiData(answer);
    }
    else
    {
        qDebug() << "error" << reply->error();
        qDebug() << reply->errorString();
        qDebug() << "url " << reply->request().url();
        foreach (QByteArray array, reply->request().rawHeaderList()) {
            qDebug() << array << request.rawHeader(array);
        }
        return;
    }


}

QByteArray HttpRequest::getHttpHeaderDate()
{
    QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
    QString dataString = currentDateTime.toString("yyyy-MM-dd HH:mm:ss.zzz ");
    QString timezone = currentDateTime.timeZone().displayName(QTimeZone::StandardTime,QTimeZone::ShortName,QLocale::UncodedLanguages);
    QByteArray res = (dataString + timezone).toUtf8() ;
    return res;
}
