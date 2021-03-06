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
    if(keySize > 0)
    {
        QStringList keysList = resultObject.keys();
        if(keysList.size() != keySize)
            return;
        for(int index = 0; index < keySize; ++ index)
        {
            QString key = keysList.at(index);
            QJsonObject dayObject = resultObject.value(key).toObject();
            data.dateKey = dayObject.value("dateKey").toString("").toUtf8();

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
            data.event = data.event.trimmed();
            if(data.event.size() > 0)
                data.hasEvent = true;
            else
                data.hasEvent = false;

            //缩略图
            QJsonObject thumbnail = dayObject.value("thumbnail").toObject();
            data.thumbnailUrl = thumbnail.value("url").toString("");

            //修改时间
            data.modifiedAt = dayObject.value("modifiedAt").toString("");

            emit sig_parsingOK(data);
        }
    }

}
