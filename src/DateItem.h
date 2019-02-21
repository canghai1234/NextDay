/***************************************************************************
    Copyright (C) 2017 by ZhaoDongshuang
    Author: ZhaoDongshuang
    Email: imtoby@126.com
    Date: 2017/11/07
    File: ObjectModel.h

    Modified: 2019/02/21 by "github.com/canghai1234"
 ***************************************************************************/
#ifndef DATEITEM_H
#define DATEITEM_H

#include <QObject>

class DateItemPrivate;

class DateItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QByteArray date READ date WRITE setDate NOTIFY dateChanged)
public:
    explicit DateItem(QObject *parent = nullptr);
    ~DateItem();

    DateItem(const DateItem &other, QObject *parent = nullptr);
    DateItem& operator=(const DateItem &other);

    QByteArray date() const;
    void setDate(const QByteArray& date);

signals:
    QByteArray dateChanged();

private:
    QScopedPointer<DateItemPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DateItem)
};


#endif // DATEITEM_H
