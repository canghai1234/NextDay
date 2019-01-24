#include "DateTime.h"
#include <QDateTime>
#include <QLocale>
#include <QTimeZone>
#include <QDebug>


DateTime::DateTime(QObject *parent) : QObject(parent)
{

}

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

QString DateTime::getHttpHeaderDate()
{
    QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
    QString dataString = currentDateTime.toString("yyyy-MM-dd HH:mm:ss.zzz ");
    QString timezone = currentDateTime.timeZone().displayName(QTimeZone::StandardTime,QTimeZone::ShortName,QLocale::UncodedLanguages);
    QString res = dataString + timezone ;
    qDebug() << "res" << res ;
    return res;
}

int DateTime::stringToInt(QString &string)
{
    int res = string.toInt();
    return res;
}
