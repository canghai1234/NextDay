/***************************************************************************
    Copyright (C) 2017 by ZhaoDongshuang
    Author: ZhaoDongshuang
    Email: imtoby@126.com
    Date: 2017/11/07
    File: ObjectModel.h

    Modified: 2019/02/21 by "github.com/canghai1234"
 ***************************************************************************/
#include "ModelManager.h"
#include <QThread>

#include "DateItem.h"

class ModelManagerPrivate
{
public:
    ModelManagerPrivate(ModelManager *parent)
        : q_ptr(parent)
        , dateModel(nullptr)
    {
    }

    void init();
    void uninit();

private:
    ModelManager * const q_ptr;
    Q_DECLARE_PUBLIC(ModelManager)

    DateModel* dateModel;
    QThread workerThread;
};

ModelManager::ModelManager(QObject *parent) :
    QObject(parent),
    d_ptr(new ModelManagerPrivate(this))
{
    Q_D(ModelManager);
    d->init();
}

ModelManager::~ModelManager()
{
    Q_D(ModelManager);
    d->uninit();
}

void ModelManager::initData()
{
    Q_D(ModelManager);
    QObjectList DateItemList;
    d->dateModel->set(&DateItemList);
}

DateModel *ModelManager::dateModel()
{
    Q_D(ModelManager);
    return d->dateModel;
}

void ModelManager::append(QByteArray date)
{
    Q_D(ModelManager);
    DateItem* newDateItem = new DateItem(this);
    newDateItem->setDate(date);
    d->dateModel->append(newDateItem);
}

void ModelManager::insert(QByteArray date, int index)
{
    Q_D(ModelManager);
    DateItem* newDateItem = new DateItem(this);
    newDateItem->setDate(date);
    d->dateModel->insert(index,newDateItem);
}

void ModelManagerPrivate::init()
{
    Q_Q(ModelManager);
    if (dateModel == nullptr) {
        dateModel = new DateModel(q);
    }
}

void ModelManagerPrivate::uninit()
{
    if (dateModel) {
        dateModel->deleteLater();
        dateModel = nullptr;
    }
}
