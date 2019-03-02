/***************************************************************************
    Copyright (C) 2017 by ZhaoDongshuang
    Author: ZhaoDongshuang
    Email: imtoby@126.com
    Date: 2017/11/07
    File: ObjectModel.h

    Modified: 2019/02/21 by "github.com/canghai1234"
 ***************************************************************************/
#include "DateItem.h"
#include "config.h"

class DateItemPrivate
{
public:
    DateItemPrivate(DateItem *parent)
        : q_ptr(parent)
        , dateKey(""), dataInited(false)
    {}

private:
    DateItem * const q_ptr;
    Q_DECLARE_PUBLIC(DateItem)


    QByteArray dateKey;
    QString imageURL;
    QString geoInfo;
    QString backgroundColor;
    QString comment1;
    QString comment2;
    QString day;
    QString week;
    QString event;
    QString author;
    bool hasShort;
    bool dataInited;
};

DateItem::DateItem(QObject *parent) :
    QObject(parent) ,
    d_ptr(new DateItemPrivate(this))
{
}

DateItem::~DateItem()
{
}

DateItem::DateItem(const DateItem &other, QObject *parent) :
    QObject(parent) ,
    d_ptr(new DateItemPrivate(this))
{
    d_ptr.swap(const_cast< QScopedPointer<DateItemPrivate>&>(other.d_ptr));
}

DateItem &DateItem::operator=(const DateItem &other)
{
    d_ptr.swap(const_cast< QScopedPointer<DateItemPrivate>&>(other.d_ptr));
    return *this;
}

void DateItem::setData(dataUI &data)
{
    Q_D(DateItem);
    d->dateKey = data.dateKey;
    d->dataInited = data.dataInited;
    setDay(data.day);
    setWeek(data.week);
    setEvent(data.event);
    setGeoInfo(data.geoInfo);

    setHasShort(data.hasShort);
    setBackgroundColor(data.backgroundColor);
    setComment1(data.comment1);
    setComment2(data.comment2);
    setAuthor(data.author);
    setImageURL(data.imageURL);
}

QByteArray DateItem::dateKey() const
{
    C_D(DateItem);
    return d->dateKey;
}

bool DateItem::dataInited() const
{
    C_D(DateItem);
    return d->dataInited;
}

bool DateItem::hasShort() const
{
    C_D(DateItem);
    return d->hasShort;
}

void DateItem::setDay(const QString &day)
{
    Q_D(DateItem);
    if (day != d->day) {
        d->day = day;
        emit dayChanged();
    }
}

void DateItem::setWeek(const QString &week)
{
    Q_D(DateItem);
    if (week != d->week) {
        d->week = week;
        emit weekChanged();
    }
}

void DateItem::setEvent(const QString &event)
{
    Q_D(DateItem);
    if (event != d->event) {
        d->event = event;
        emit eventChanged();
    }
}

void DateItem::setGeoInfo(const QString &geo)
{
    Q_D(DateItem);
    if (geo != d->geoInfo) {
        d->geoInfo = geo;
        emit geoInfoChanged();
    }
}

void DateItem::setHasShort(const bool hasShort)
{
    Q_D(DateItem);
    if (hasShort != d->hasShort) {
        d->hasShort = hasShort;
        emit hasShortChanged();
    }
}

void DateItem::setBackgroundColor(const QString &color)
{
    Q_D(DateItem);
    if (color != d->backgroundColor) {
        d->backgroundColor = color;
        emit backgroundColorChanged();
    }
}

void DateItem::setComment1(const QString &comment1)
{
    Q_D(DateItem);
    if (comment1 != d->comment1) {
        d->comment1 = comment1;
        emit comment1Changed();
    }
}

void DateItem::setComment2(const QString &comment2)
{
    Q_D(DateItem);
    if (comment2 != d->comment2) {
        d->comment2 = comment2;
        emit comment2Changed();
    }
}

void DateItem::setAuthor(const QString &author)
{
    Q_D(DateItem);
    if (author != d->author) {
        d->author = author;
        emit authorChanged();
    }
}

void DateItem::setImageURL(const QString &image)
{
    Q_D(DateItem);
    if (image != d->imageURL) {
        d->imageURL = image;
        emit imageURLChanged();
    }
}
QString DateItem::author() const
{
    C_D(DateItem);
    return d->author;
}

QString DateItem::comment1() const
{
    C_D(DateItem);
    return d->comment1;
}

QString DateItem::comment2() const
{
    C_D(DateItem);
    return d->comment2;
}

QString DateItem::geoInfo() const
{
    C_D(DateItem);
    return d->geoInfo;
}

QString DateItem::backgroundColor() const
{
    C_D(DateItem);
    return d->backgroundColor;
}

QString DateItem::imageURL() const
{
    C_D(DateItem);
    return d->imageURL;
}

QString DateItem::eventString() const
{
    C_D(DateItem);
    return d->event;
}

QString DateItem::week() const
{
    C_D(DateItem);
    return d->week;
}

QString DateItem::day() const
{
    C_D(DateItem);
    return d->day;
}
