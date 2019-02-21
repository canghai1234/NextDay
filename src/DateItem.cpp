/***************************************************************************
    Copyright (C) 2017 by ZhaoDongshuang
    Author: ZhaoDongshuang
    Email: imtoby@126.com
    Date: 2017/11/07
    File: ObjectModel.h

    Modified: 2019/02/21 by "github.com/canghai1234"
 ***************************************************************************/
#include "DateItem.h"

#include "Config.h"

class DateItemPrivate
{
public:
    DateItemPrivate(DateItem *parent)
        : q_ptr(parent)
        , date("")
    {}

private:
    DateItem * const q_ptr;
    Q_DECLARE_PUBLIC(DateItem)

    QByteArray date;
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

QByteArray DateItem::date() const
{
    C_D(DateItem);
    return d->date;
}

void DateItem::setDate(const QByteArray& date)
{
    Q_D(DateItem);
    if (date != d->date) {
        d->date = date;
        emit dateChanged();
    }
}
