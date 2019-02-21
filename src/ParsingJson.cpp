#include "ParsingJson.h"
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>


ParsingJson::ParsingJson(QObject *parent) : QObject(parent)
{

}

void ParsingJson::slot_parsingSource(QByteArray jsonData)
{
//    qDebug() << jsonData;
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData, &json_error));

    if(json_error.error != QJsonParseError::NoError)
    {
        qDebug() << "解析 Json 错误" ;
        return;
    }
    NetworkData data;
    QJsonObject rootObj = jsonDoc.object();
    QJsonObject resultObject = rootObj.value("result").toObject();
    data.status = rootObj.value("status").toString().contains("ok",Qt::CaseInsensitive);

    if(resultObject.contains("hasMore"))
    {
        data.hasMore = resultObject.take("hasMore").toBool(false);
    }
    int keySize = resultObject.size();
    if(keySize == 1)
    {
        QJsonObject dayObject = resultObject.begin().value().toObject();
        data.dateKey = dayObject.value("dateKey").toString("");

        //作者信息
        QJsonObject author = dayObject.value("author").toObject();
        data.name = author.value("name").toString("");
        if(data.name.size() > 0)
            data.hasAuthorInfo = true;

        //text 文本
        QJsonObject text = dayObject.value("text").toObject();
        data.comment1 = text.value("comment1").toString("");
        data.comment2 = text.value("comment2").toString("");
        data.shortText = text.value("short").toString("");
        if(data.shortText.size() > 0)
            data.hasShort = true;

        //geo 信息
        QJsonObject geo = dayObject.value("geo").toObject();
        data.reverse = geo.value("reverse").toString("");

        //背景颜色
        QJsonObject colors = dayObject.value("colors").toObject();
        data.background = colors.value("background").toString("");

        //图片信息
        QJsonObject images = dayObject.value("images").toObject();
        data.image_big = images.value("big").toString("");
        data.image_big2x = images.value("big2x").toString("");
        data.image_big568h2x = images.value("big568h2x").toString("");
        data.image_big568h3x = images.value("big568h3x").toString("");
        data.image_small = images.value("small").toString("");
        data.image_small2x = images.value("small2x").toString("");
        data.image_small568h2x = images.value("small568h2x").toString("");
        data.image_iphoneX = images.value("iphone-x").toString("");

        //音乐信息
        data.hasMusic = dayObject.contains("music");
        if(data.hasMusic)
        {
            QJsonObject music = dayObject.value("music").toObject();
            data.music_artist = music.value("artist").toString("");
            data.music_title = music.value("title").toString("");
            data.music_Url = music.value("url").toString("");
        }

        //视频信息
        data.hasVideo = dayObject.contains("video");
        if(data.hasVideo)
        {
            QJsonObject video = dayObject.value("video").toObject();
            data.video_autoPlay = video.value("autoPlay").toBool(false);
            data.video_autoRepeat = video.value("autoRepeat").toBool(false);
            data.video_url = video.value("url").toString("");
            data.video_height = video.value("width").toInt(0);
            data.video_height = video.value("height").toInt(0);
            data.video_length = video.value("length").toDouble(0);
            data.video_orientation = video.value("orientation").toString("");
        }

        //event 信息
        data.event = dayObject.value("event").toString("");
        if(data.event.size() > 0)
            data.hasEvent = true;

        //缩略图
        QJsonObject thumbnail = dayObject.value("thumbnail").toObject();
        data.thumbnailUrl = thumbnail.value("url").toString("");

        //修改时间
        data.modifiedAt = dayObject.value("modifiedAt").toString("");
    }
    emit sig_parsingOK(data);
}


void ParsingJson::parse()
{

    QByteArray jsonData;

    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData, &json_error));

    if(json_error.error != QJsonParseError::NoError)
    {
        qDebug() << "解析 Json 错误" ;
        return;
    }

    QJsonObject rootObj = jsonDoc.object();
    QJsonObject author = rootObj.value("author").toObject();
    QJsonObject colors = rootObj.value("colors").toObject();
    QJsonObject images = rootObj.value("images").toObject();
    QJsonObject music = rootObj.value("music").toObject();
    QJsonObject text = rootObj.value("text").toObject();
    QJsonObject video = rootObj.value("video").toObject();
    QJsonObject geo = rootObj.value("geo").toObject();
    QJsonObject thumbnail = rootObj.value("thumbnail").toObject();



    QString name = author.value("name").toString("");
    QString dateKey = rootObj.value("dateKey").toString("");
    QString background = colors.value("background").toString("");
    QString big = images.value("big").toString("");
    QString big2x = images.value("big2x").toString("");
    QString big568h2x = images.value("big568h2x").toString("");
    QString big568h3x = images.value("big568h3x").toString("");
    QString small = images.value("small").toString("");
    QString small2x = images.value("small2x").toString("");
    QString small568h2x = images.value("small568h2x").toString("");
    QString artist = music.value("artist").toString("");
    QString title = music.value("title").toString("");
    QString musicUrl = music.value("url").toString("");
    QString comment1 = text.value("comment1").toString("");
    QString comment2 = text.value("comment2").toString("");
    QString shortText = text.value("short").toString("");
    bool autuPlay = video.value("autuPlay").toBool(false);
    bool autuRepeat = video.value("autuRepeat").toBool(false);
    QString sharing = video.value("sharing").toString("");
    QString videoUrl = video.value("url").toString("");
    int width = video.value("width").toInt(0);
    int height = video.value("height").toInt(0);
    double length = video.value("length").toDouble(0);
    QString orientation = video.value("orientation").toString("");
    QString event = rootObj.value("event").toString("");
    QString reverse = geo.value("reverse").toString("");
    QString thumbnailUrl = thumbnail.value("url").toString("");
    QString modifiedAt = rootObj.value("modifiedAt").toString("");


}
