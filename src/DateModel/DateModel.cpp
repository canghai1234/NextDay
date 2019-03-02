/***************************************************************************
    Copyright (C) 2017 by ZhaoDongshuang
    Author: ZhaoDongshuang
    Email: imtoby@126.com
    Date: 2017/11/07
    File: ObjectModel.h

    Modified: 2019/02/21 by "github.com/canghai1234"
 ***************************************************************************/
#include "DateModel.h"
#include <QMutex>

namespace {
enum {
    DateModelRole = Qt::UserRole + 1
};
}

class DateModelPrivate
{
public:
    DateModelPrivate(DateModel * parent)
        : q_ptr(parent)
        , mutex(nullptr)
    {
    }

    void init();
    void uninit();

private:
    DateModel * const q_ptr;
    Q_DECLARE_PUBLIC(DateModel)

    QHash<int, QByteArray> rolesNames;
    QObjectList objectList;
    QMutex *mutex;
};

DateModel::DateModel(QObject *parent) :
    QAbstractListModel(parent),
    d_ptr(new DateModelPrivate(this))
{
    Q_D(DateModel);
    d->init();
    d->rolesNames[DateModelRole] = "DateModelRole";
}

DateModel::~DateModel()
{
    Q_D(DateModel);
    d->uninit();
}

int DateModel::rowCount(const QModelIndex &parent) const
{
    C_D(DateModel);
    Q_UNUSED(parent);
    return d->objectList.size();
}

int DateModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant DateModel::data(const QModelIndex &index, int role) const
{
    C_D(DateModel);
    if (index.row() >= 0 && index.row() < d->objectList.size() ) {
        if (role == DateModelRole) {
            QObject *object = d->objectList.at(index.row());
            return QVariant::fromValue(object);
        }
    }
    return QVariant(0);
}

bool DateModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_D(DateModel);
    if (index.row() >= 0 && index.row() < d->objectList.size() ) {
        if (role == DateModelRole) {
            d->mutex->lock();
            d->objectList.replace(index.row(), value.value<QObject *>());
            d->mutex->unlock();
            return true;
        }
    }
    return false;
}

QHash<int, QByteArray> DateModel::roleNames() const
{
    C_D(DateModel);
    return d->rolesNames;
}

void DateModel::insert(int index, QObject *object)
{
    Q_D(DateModel);
    if (index >= 0  && index <= d->objectList.size()) {
        d->mutex->lock();
        beginInsertRows(QModelIndex(), index, index);
        d->objectList.insert(index, object);
        endInsertRows();
        d->mutex->unlock();
    }
}

void DateModel::append(QObject *object)
{
    Q_D(DateModel);
    insert(d->objectList.size(), object);
}

void DateModel::push_front(QObject *object)
{
    insert(0, object);
}

void DateModel::push_back(QObject *object)
{
    append(object);
}

void DateModel::replace(int index, QObject *object)
{
    Q_D(DateModel);
    if (index >= 0  && index < d->objectList.size()) {
        d->mutex->lock();
        d->objectList.replace(index, object);
        d->mutex->unlock();
        emit dataChanged(createIndex(index, 0), createIndex(index, 0));
    }
}

void DateModel::set(QObjectList *objectList)
{
    Q_D(DateModel);
    d->mutex->lock();
    beginResetModel();
    d->objectList = *objectList;
    endResetModel();
    d->mutex->unlock();
}

void DateModel::remove(QObject *object)
{
    Q_D(DateModel);
    d->mutex->lock();
    const int index = d->objectList.indexOf(object);
    if (index >= 0) {
        beginRemoveRows(QModelIndex(), index, index);
        d->objectList.removeAt(index);
        endRemoveRows();
    }
    d->mutex->unlock();
}

void DateModel::remove(int index)
{
    Q_D(DateModel);
    if (index >= 0 && index < d->objectList.size()) {
        d->mutex->lock();
        beginRemoveRows(QModelIndex(), index, index);
        QObject* object = d->objectList.at(index);
        d->objectList.removeAt(index);
        object->deleteLater();
        endRemoveRows();
        d->mutex->unlock();
    }
}

void DateModel::clear()
{
    Q_D(DateModel);
    d->mutex->lock();
    beginResetModel();
    qDeleteAll(d->objectList.begin(), d->objectList.end());
    d->objectList.clear();
    endResetModel();
    d->mutex->unlock();
}

QObject *DateModel::get(int index)
{
    Q_D(DateModel);
    if (index >= 0 && index < d->objectList.size()) {
        d->mutex->lock();
        QObject * object = d->objectList.at(index);
        d->mutex->unlock();
        return object;
    }
    return nullptr;
}

QObject *DateModel::getFirst()
{
    Q_D(DateModel);
    if (d->objectList.size() > 0) {
        d->mutex->lock();
        QObject * object = d->objectList.at(0);
        d->mutex->unlock();
        return object;
    }
    return nullptr;
}

QObject *DateModel::getLast()
{
    Q_D(DateModel);
    int size = d->objectList.size();
    if (size > 0) {
        d->mutex->lock();
        QObject * object = d->objectList.at(size - 1);
        d->mutex->unlock();
        return object;
    }
    return nullptr;
}

QObjectList *DateModel::getAll()
{
    Q_D(DateModel);
    d->mutex->lock();
    QObjectList * objectList = &(d->objectList);
    d->mutex->unlock();
    return objectList;
}

int DateModel::getCount()
{
    C_D(DateModel);
    return d->objectList.size();
}


void DateModelPrivate::init()
{
    rolesNames.clear();
    objectList.clear();
    if (mutex == nullptr) {
        mutex = new QMutex(QMutex::Recursive);
    }
}

void DateModelPrivate::uninit()
{
    qDeleteAll(objectList.begin(), objectList.end());
    objectList.clear();
    rolesNames.clear();
    if (mutex) {
        delete mutex;
        mutex = nullptr;
    }
}
