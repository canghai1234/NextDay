#include "NetworkData.h"

NetworkData::NetworkData()
{
    status = false;
    hasMore = false;
    dateKey = "";

    //作者信息
    hasAuthorInfo = false;
    name = "";

    //text 文本
    hasShort = false;
    comment1 = "";
    comment2 = "";
    shortText = "";

    //geo 信息
    reverse = "";

    //背景颜色
    background = "";

    //图片信息
    image_big = "";
    image_big2x = "";
    image_big568h2x = "";
    image_big568h3x = "";
    image_small = "";
    image_small2x = "";
    image_small568h2x = "";
    image_iphoneX = "";

    //音乐信息
    hasMusic = false;
    music_artist = "";
    music_title = "";
    music_Url = "";

    //视频信息
    hasVideo = false;
    video_autoPlay = false;
    video_autoRepeat = false;
    video_url = "";
    video_width = 0;
    video_height = 0;
    video_length = 0.0;
    video_orientation = "";

    //event 信息
    hasEvent = false;
    event = "";

    //缩略图
    thumbnailUrl = "";

    //修改时间
    modifiedAt = "";
}


