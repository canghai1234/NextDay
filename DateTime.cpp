#include "DateTime.h"
#include <QDateTime>
#include <QLocale>
#include <QTimeZone>
#include <QDebug>


DateTime::DateTime(QObject *parent) : QObject(parent)
{
    
}

QByteArray DateTime::getToday()
{
    QByteArray res;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    int year = currentDateTime.toString("yyyy").toInt();
    int month = currentDateTime.toString("MM").toInt();
    int day = currentDateTime.toString("dd").toInt();
    if(year >= 2013 && (month > 0 && month < 13) && (day > 0 && day < 32))
    {
        res +=  currentDateTime.toString("yyyy").toUtf8()
                + currentDateTime.toString("MM").toUtf8()
                + currentDateTime.toString("dd").toUtf8();
    }
    return res;
}

QByteArray DateTime::getYesterday(QString date)
{
    QByteArray res;
    if(isDateValid(date))
    {
        QDate dateObj = QDate::fromString(date,"yyyyMMdd");
        QDate yesterday = dateObj.addDays(-1);
        res = yesterday.toString("yyyyMMdd").toUtf8();
    }
    return res;
}

QByteArray DateTime::getTomorrow(QString date)
{
    QByteArray res;
    if(isDateValid(date))
    {
        QDate dateObj = QDate::fromString(date,"yyyyMMdd");
        QDate yesterday = dateObj.addDays(1);
        res = yesterday.toString("yyyyMMdd").toUtf8();
    }
    return res;
}

/*
void DateTime::getToday()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    int year = currentDateTime.toString("yyyy").toInt();
    int month = currentDateTime.toString("MM").toInt();
    int day = currentDateTime.toString("dd").toInt();
    int hour = currentDateTime.toString("HH").toInt(); //12 与 24 小时制的问题，待测
    int minute = currentDateTime.toString("mm").toInt();
    int second = currentDateTime.toString("ss").toInt();
    int millisecond = currentDateTime.toString("zzz").toInt();
    QLocale eng = QLocale::English;
    QString weekShort = eng.toString(currentDateTime,"ddd");
    QString week = eng.toString(currentDateTime,"dddd");
    QString s_monthShort = eng.toString(currentDateTime,"MMM");
    QString s_month = eng.toString(currentDateTime,"MMMM");
    QString timezone = currentDateTime.timeZone().displayName(QTimeZone::StandardTime,QTimeZone::ShortName,QLocale::C);
    QTimeZone zone = QTimeZone::systemTimeZone();
    QTimeZone zone2(currentDateTime.timeZone().id());
    qDebug() << zone2.displayName(QTimeZone::StandardTime,QTimeZone::ShortName,QLocale::UncodedLanguages);
    qDebug() << currentDateTime.timeZoneAbbreviation() << zone2;
    qDebug() << currentDateTime.timeZone().id() << currentDateTime.timeZone() << zone.abbreviation(currentDateTime);
    qDebug() <<year << month << day << hour << minute << second << millisecond;
    qDebug() << week << weekShort << s_month << s_monthShort << timezone;
}
*/


QString DateTime::getDay(QString date)
{
    if(isDateValid(date))
        return date.right(2);
    else
        return "";
}

QString DateTime::getMonthShort(QString date)
{
    if(isDateValid(date))
    {
        QDate dateObj = QDate::fromString(date,"yyyyMMdd");
        QLocale eng = QLocale::English;
        return eng.toString(dateObj,"MMM");
    }
    else
        return "";
}

QString DateTime::getWeek(QString date)
{
    if(isDateValid(date))
    {
        QDate dateObj = QDate::fromString(date,"yyyyMMdd");
        QLocale eng = QLocale::English;
        return eng.toString(dateObj,"dddd");
    }
    else
        return "";
}

bool DateTime::isDateValid(const QString &date)
{
    int dateSize = date.size();
    if(dateSize != 8)
        return false;
    int year = date.left(4).toInt();
    int month = date.mid(4,2).toInt();
    int day = date.right(2).toInt();
    return QDate::isValid(year,month,day);
}
