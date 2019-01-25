#include "ParsingJson.h"
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>


ParsingJson::ParsingJson(QObject *parent) : QObject(parent)
{

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
