#ifndef COMMONH
#define COMMONH

#include <QObject>

struct dataUI
{
    int year ; //2019
    int month ; //01
    int day; // 23
    QString week ; //Wednesday
    QString s_monthShort; //Jan

    dataUI& operator =(dataUI& data)
    {
        year = data.year;
        month  = data.month;
        day = data.day;
        week = data.week;
        s_monthShort = data.s_monthShort;
        return *this;
    }
    dataUI() {}
};

struct dateimeInfo
{
    int year ; //2019
    int month ; //01
    int day; //
    int hour ;
    int minute ;
    int second ;
    int millisecond;
    int week;
    QString weekShort ;
//    QString week ;
    QString s_monthShort;
    QString s_month;

    QString timeZone;
    dateimeInfo()
    {

    }
};

struct NetworkSource
{
    QString name;
    QString dateKey;
    QString background;
    QString big;
    QString big2x;
    QString big568h2x;
    QString big568h3x;
    QString small;
    QString small2x;
    QString small568h2x;
    QString artist;
    QString title;
    QString musicUrl;
    QString comment1;
    QString comment2;
    QString shortText;
    bool autuPlay;
    bool autuRepeat;
    QString sharing;
    QString videoUrl;
    int width;
    int height;
    double length;
    QString orientation;
    QString event;
    QString reverse;
    QString thumbnailUrl;
    QString modifiedAt;

    bool video_autoPlay;
    bool video_autoRepeat;
    QString video_url;
    int video_width;
    int vide0_height;
    double video_length;
    QString video_orientation;

    NetworkSource& operator =(NetworkSource& data)
    {
        name = data.name;
        dateKey = data.dateKey;
        background = data.background;
        big = data.big;
        big2x = data.big2x;
        big568h2x = data.big568h2x;
        big568h3x = data.big568h3x;
        small = data.small;
        small2x = data.small2x;
        small568h2x = data.small568h2x;
        artist = data.artist;
        title = data.title;
        musicUrl = data.musicUrl;
        comment1 = data.comment1;
        comment2 = data.comment2;
        shortText = data.shortText;
        autuPlay = data.autuPlay;
        autuRepeat = data.autuRepeat;
        sharing = data.sharing;
        videoUrl = data.videoUrl;
        width = data.width;
        height = data.height;
        length = data.length;
        orientation = data.orientation;
        event = data.event;
        reverse = data.reverse;
        thumbnailUrl = data.thumbnailUrl;
        modifiedAt = data.modifiedAt;
        return *this;
    }
};

#endif // COMMONH
