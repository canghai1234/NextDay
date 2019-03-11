#include "HttpRequest.h"
#include <QUrl>
#include <QTimeZone>
#include <QCryptographicHash>
#include <QDate>
#include "apikey.h"
#include "NotificationDialog.h"
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
        QString dataString = currentDateTime.toString("yyyy-MM-dd HH:mm:ss.zzz");
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

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray answer = reply->readAll();
        emit sig_recvApiData(answer);
    }
    else
    {
        QString errString;
        int statusCode = nCode.toInt();
        errString = "状态码: " + QString::number(statusCode);
        errString = errString + "\r\n" + getHttpErrorCodeString(statusCode);
        NotificationDialog::getSingleton()->insertNotify(3,errString);
        return;
    }
}

QByteArray HttpRequest::getHttpHeaderDate()
{
    QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
    QString dataString = currentDateTime.toString("yyyy-MM-dd HH:mm:ss.zzz");
    QString timezone = currentDateTime.timeZone().displayName(QTimeZone::StandardTime,QTimeZone::ShortName,QLocale::UncodedLanguages);
    QByteArray res = (dataString + timezone).toUtf8() ;
    return res;
}

//暂时没有使用到此函数
QString HttpRequest::getNetworkErrorString(QNetworkReply::NetworkError error)
{
    QString res;
    switch (error) {
    case QNetworkReply::ConnectionRefusedError :
    {
        res = QString("远程服务器拒绝连接（服务器不接受请求）");
        break;
    }
    case QNetworkReply::RemoteHostClosedError :
    {
        res = QString("在收到并处理完整个回复之前，远程服务器提前关闭了连接");
        break;
    }
    case QNetworkReply::HostNotFoundError :
    {
        res = QString("找不到远程主机名（无效的主机名）");
        break;
    }
    case QNetworkReply::TimeoutError :
    {
        res = QString("与远程服务器的连接超时");
        break;
    }
    case QNetworkReply::OperationCanceledError :
    {
        res = QString("在完成之前通过调用abort（）或close（）取消了操作。");
        break;
    }
    case QNetworkReply::SslHandshakeFailedError :
    {
        res = QString("SSL/TLS握手失败，无法建立加密通道。");
        break;
    }
    case QNetworkReply::TemporaryNetworkFailureError :
    {
        res = QString("由于与网络断开连接断开连接，但系统已启动漫游到另一个接入点。请求应重新提交，并在重新建立连接后立即处理。");
        break;
    }
    case QNetworkReply::NetworkSessionFailedError :
    {
        res = QString("由于断开网络或无法启动网络，连接中断。");
        break;
    }
    case QNetworkReply::BackgroundRequestNotAllowedError :
    {
        res = QString("由于平台策略，当前不允许后台请求。");
        break;
    }
    case QNetworkReply::TooManyRedirectsError :
    {
        res = QString("在重定向后，达到了最大限制。）");
        break;
    }
    case QNetworkReply::InsecureRedirectError :
    {
        res = QString("在跟踪重定向时，网络访问API检测到从加密协议（https）到未加密协议（http）的重定向。");
        break;
    }
    case QNetworkReply::ProxyConnectionRefusedError :
    {
        res = QString("拒绝与代理服务器的连接（代理服务器不接受请求）");
        break;
    }
    case QNetworkReply::ProxyConnectionClosedError :
    {
        res = QString("在收到并处理完整个回复之前，代理服务器提前关闭了连接");
        break;
    }
    case QNetworkReply::ProxyNotFoundError :
    {
        res = QString("找不到代理主机名（无效的代理主机名）");
        break;
    }
    case QNetworkReply::ProxyTimeoutError :
    {
        res = QString("与代理的连接超时或代理没有及时回复发送的请求");
        break;
    }
    case QNetworkReply::ProxyAuthenticationRequiredError :
    {
        res = QString("代理需要身份验证才能兑现请求，但不接受任何提供的凭据（如果有）");
        break;
    }
    case QNetworkReply::ContentAccessDenied :
    {
        res = QString("拒绝访问远程内容（类似于HTTP错误403）");
        break;
    }
    case QNetworkReply::ContentOperationNotPermittedError :
    {
        res = QString("不允许在远程内容上请求的操作");
        break;
    }
    case QNetworkReply::ContentNotFoundError :
    {
        res = QString("在服务器上找不到远程内容（类似于HTTP错误404）");
        break;
    }
    case QNetworkReply::AuthenticationRequiredError :
    {
        res = QString("远程服务器需要身份验证才能提供内容，但不接受提供的凭据（如果有）");
        break;
    }
    case QNetworkReply::ContentReSendError :
    {
        res = QString("需要再次发送请求，但这例子失败，例如因为第二次无法读取上载数据。");
        break;
    }
    case QNetworkReply::ContentConflictError :
    {
        res = QString("由于与资源的当前状态冲突，无法完成请求。");
        break;
    }
    case QNetworkReply::ContentGoneError :
    {
        res = QString("服务器上不再提供所请求的资源。");
        break;
    }
    case QNetworkReply::InternalServerError :
    {
        res = QString("服务器遇到意外情况，导致无法完成请求。");
        break;
    }
    case QNetworkReply::OperationNotImplementedError :
    {
        res = QString("服务器不支持完成请求所需的功能。");
        break;
    }
    case QNetworkReply::ServiceUnavailableError :
    {
        res = QString("此时服务器无法处理请求。");
        break;
    }
    case QNetworkReply::ProtocolUnknownError :
    {
        res = QString("由于协议未知，因此Network Access API无法遵守请求");
        break;
    }
    case QNetworkReply::ProtocolInvalidOperationError :
    {
        res = QString("请求的操作对此协议无效");
        break;
    }
    case QNetworkReply::UnknownNetworkError :
    {
        res = QString("检测到与网络无关的未知错误");
        break;
    }
    case QNetworkReply::UnknownProxyError :
    {
        res = QString("检测到未知的代理相关错误");
        break;
    }
    case QNetworkReply::UnknownContentError :
    {
        res = QString("检测到与远程内容相关的未知错误");
        break;
    }
    case QNetworkReply::ProtocolFailure :
    {
        res = QString("检测到协议故障（解析错误，无效或意外响应等）");
        break;
    }
    case QNetworkReply::UnknownServerError :
    {
        res = QString("检测到与服务器响应相关的未知错误");
        break;
    }
    default:
        res = QString("未定义错误");
    }
    return res;
}

QString HttpRequest::getHttpErrorCodeString(int errorCode)
{
    QString res;
    switch (errorCode) {
    case 204 :
    {
        res = QString("请求成功处理，没有实体的主体返回");
        break;
    }
    case 206 :
    {
        res = QString("范围请求已成功处理");
        break;
    }
    case 301 :
    {
        res = QString("永久重定向，资源已永久分配新URI");
        break;
    }
    case 302 :
    {
        res = QString("临时重定向，资源已临时分配新URI");
        break;
    }
    case 303 :
    {
        res = QString("临时重定向，期望使用GET定向获取");
        break;
    }
    case 304 :
    {
        res = QString("发送的附带条件请求未满足");
        break;
    }
    case 307 :
    {
        res = QString("临时重定向，POST不会变成GET");
        break;
    }
    case 400 :
    {
        res = QString("请求报文语法错误或参数错误");
        break;
    }
    case 401 :
    {
        res = QString("需要通过HTTP认证，或认证失败");
        break;
    }
    case 403 :
    {
        res = QString("请求资源被拒绝");
        break;
    }
    case 404 :
    {
        res = QString("无法找到请求资源（服务器无理由拒绝）");
        break;
    }
    case 429 :
    {
        res = QString("API 使用次数超过限制，请稍后再试");
        break;
    }
    case 500 :
    {
        res = QString("服务器故障或Web应用故障");
        break;
    }
    case 503 :
    {
        res = QString("服务器超负载或停机维护");
        break;
    }
    default:
        res = QString("未知的错误");
    }
    return res;
}
