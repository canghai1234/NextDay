/***************************************************************************
    Copyright (C) 2017 by ZhaoDongshuang
    Author: ZhaoDongshuang
    Email: imtoby@126.com
    Date: 2017/11/07
    File: ObjectModel.h

    Modified: 2019/02/21 by "github.com/canghai1234"
 ***************************************************************************/
#ifndef DATEMODEL_H
#define DATEMODEL_H

#include <QAbstractListModel>
#include "config.h"

class DateModelPrivate;

class DateModel : public QAbstractListModel
{
    Q_OBJECT
public:
    DateModel (QObject * parent = nullptr);
    ~DateModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual QHash<int, QByteArray> roleNames() const;

    void insert(int index, QObject* object);
    void append(QObject* object);
    void push_front(QObject* object);
    void push_back(QObject* object);

    void replace(int index, QObject* object);
    void set(QObjectList * objectList);

    void remove(QObject* object);
    void remove(int index);
    void clear();

    QObject * get(int index);
    QObject *getFirst();
    QObject *getLast();
    QObjectList* getAll();
    int getCount();
private:
    QScopedPointer<DateModelPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DateModel)

};

#endif // DATEMODEL_H
