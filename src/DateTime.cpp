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

QByteArray DateTime::getYesterday(QString date, int day)
{
    QByteArray res;
    if(isDateValid(date))
    {
        QDate dateObj = QDate::fromString(date,"yyyyMMdd");
        QDate yesterday = dateObj.addDays(-1 * day);
        res = yesterday.toString("yyyyMMdd").toUtf8();
    }
    return res;
}

QByteArray DateTime::getTomorrow(QString date,int day)
{
    QByteArray res;
    if(isDateValid(date))
    {
        QDate dateObj = QDate::fromString(date,"yyyyMMdd");
        QDate yesterday = dateObj.addDays(day);
        res = yesterday.toString("yyyyMMdd").toUtf8();
    }
    return res;
}

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

qint64 DateTime::daysTo(QByteArray date,QByteArray refDate)
{
    if(isDateValid(date) && isDateValid(refDate))
    {
        QDate dateObj = QDate::fromString(date,"yyyyMMdd");
        QDate refdateObj = QDate::fromString(refDate,"yyyyMMdd");
        qint64 count = dateObj.daysTo(refdateObj);
        return count;
    }
    return 0;
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
