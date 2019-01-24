#ifndef DATETIME_H
#define DATETIME_H

#include <QObject>

class DateTime : public QObject
{
    Q_OBJECT
public:
    explicit DateTime(QObject *parent = nullptr);
    void getToday();
    QString getHttpHeaderDate();
signals:

public slots:

private:
    struct dateimeInfo
    {
        int _year , _month , _day;
        int _hour , _minute , _second , _millisecond;
        int _week;
        QString timeZone;
        dateimeInfo()
        {

        }
    };
    int stringToInt(QString& string);
};

#endif // DATETIME_H
