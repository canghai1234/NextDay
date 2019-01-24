#ifndef COMMONH
#define COMMONH

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
    QString week ;
    QString s_monthShort;
    QString s_month;

    QString timeZone;
    dateimeInfo()
    {

    }
};


#endif // COMMONH
