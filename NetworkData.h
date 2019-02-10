#ifndef NETWORKDATA_H
#define NETWORKDATA_H

#include <QObject>

class NetworkData
{
public:
    explicit NetworkData();


signals:

public slots:

public:
    bool status;
    bool hasMore;
    QString dateKey;

    //作者信息
    bool hasAuthorInfo;
    QString name;

    //text 文本
    bool hasShort;
    QString comment1;
    QString comment2;
    QString shortText;

    //geo 信息
    QString reverse;

    //背景颜色
    QString background;

    //图片信息
    QString image_big;
    QString image_big2x;
    QString image_big568h2x;
    QString image_big568h3x;
    QString image_small;
    QString image_small2x;
    QString image_small568h2x;
    QString image_iphoneX;

    //音乐信息
    bool hasMusic;
    QString music_artist;
    QString music_title;
    QString music_Url;

    //视频信息
    bool hasVideo;
    bool video_autoPlay;
    bool video_autoRepeat;
    QString video_url;
    int video_width;
    int video_height;
    double video_length;
    QString video_orientation;

    //event 信息
    bool hasEvent;
    QString event;

    //缩略图
    QString thumbnailUrl;

    //修改时间
    QString modifiedAt;

public:
    NetworkData& operator =(NetworkData& data)
    {
        status = data.status;
        hasMore = data.hasMore;
        dateKey = data.dateKey;

        //作者信息
        hasAuthorInfo = data.hasAuthorInfo;
        name = data.name;

        //text 文本
        hasShort = data.hasShort;
        comment1 = data.comment1;
        comment2 = data.comment2;
        shortText = data.shortText;

        //geo 信息
        reverse = data.reverse;

        //背景颜色
        background = data.background;

        //图片信息
        image_big = data.image_big;
        image_big2x = data.image_big2x;
        image_big568h2x = data.image_big568h2x;
        image_big568h3x = data.image_big568h3x;
        image_small = data.image_small;
        image_small2x = data.image_small2x;
        image_small568h2x = data.image_small568h2x;
        image_iphoneX = data.image_iphoneX;

        //音乐信息
        hasMusic = data.hasMusic;
        music_artist = data.music_artist;
        music_title = data.music_title;
        music_Url = data.music_Url;

        //视频信息
        hasVideo = data.hasVideo;
        video_autoPlay = data.video_autoPlay;
        video_autoRepeat = data.video_autoRepeat;
        video_url = data.video_url;
        video_width = data.video_height;
        video_height = data.video_height;
        video_length = data.video_length;
        video_orientation = data.video_orientation;

        //event 信息
        hasEvent = data.hasEvent;
        event = data.event;

        //缩略图
        thumbnailUrl = data.thumbnailUrl;

        //修改时间
        modifiedAt = data.modifiedAt;
        return *this;
    }
};

#endif // NETWORKDATA_H
