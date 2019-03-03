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
#include "common.h"

class DateItemPrivate;

class DateItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString imageURL READ imageURL WRITE setImageURL NOTIFY imageURLChanged)
    Q_PROPERTY(QString geoInfo READ geoInfo WRITE setGeoInfo NOTIFY geoInfoChanged)
    Q_PROPERTY(QString backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QString comment1 READ comment1 WRITE setComment1 NOTIFY comment1Changed)
    Q_PROPERTY(QString comment2 READ comment2 WRITE setComment2 NOTIFY comment2Changed)
    Q_PROPERTY(QString day READ day WRITE setDay NOTIFY dayChanged)
    Q_PROPERTY(QString week READ week WRITE setWeek NOTIFY weekChanged)
    Q_PROPERTY(QString event READ eventString WRITE setEvent NOTIFY eventChanged)
    Q_PROPERTY(bool hasShort READ hasShort WRITE setHasShort NOTIFY hasShortChanged)
    Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged)

public:
    explicit DateItem(QObject *parent = nullptr);
    ~DateItem();

    DateItem(const DateItem &other, QObject *parent = nullptr);
    DateItem& operator=(const DateItem &other);

    void setData(dataUI &data);

    QByteArray dateKey() const;
    bool dataInited() const;

    QString imageURL() const;
    QString geoInfo() const;
    QString backgroundColor() const;
    QString comment1() const;
    QString comment2() const;
    QString day() const;
    QString week() const;
    QString eventString() const;
    QString author() const;
    bool hasShort() const;

    bool hasMusic() const;
    QString musicArtist() const;
    QString musicTitle() const;
    QString musicUrl() const;

signals:
    void imageURLChanged();
    void geoInfoChanged();
    void backgroundColorChanged();
    void comment1Changed();
    void comment2Changed();
    void dayChanged();
    void weekChanged();
    void eventChanged();
    void hasShortChanged();
    void authorChanged();

private:
    QScopedPointer<DateItemPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DateItem)

    void setImageURL(const QString& image);
    void setGeoInfo(const QString& geo);
    void setBackgroundColor(const QString& color);
    void setComment1(const QString& comment1);
    void setComment2(const QString& comment2);
    void setDay(const QString& day);
    void setWeek(const QString& week);
    void setEvent(const QString& event);
    void setHasShort(const bool hasShort);
    void setAuthor(const QString& author);
};


#endif // DATEITEM_H
