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
#include <QDebug>
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

void ModelManager::push_back(dataUI date)
{
    Q_D(ModelManager);
    DateItem* newDateItem = new DateItem(this);
    newDateItem->setData(date);
    d->dateModel->push_back(newDateItem);
}

void ModelManager::push_front(dataUI date)
{
    Q_D(ModelManager);
    DateItem* newDateItem = new DateItem(this);
    newDateItem->setData(date);
    d->dateModel->push_front(newDateItem);
}

QByteArray ModelManager::lastDate()
{
    Q_D(ModelManager);
    DateItem* tempItem = static_cast<DateItem*>(d->dateModel->getLast());
    if(nullptr != tempItem)
        return tempItem->dateKey();
    return "";
}

QByteArray ModelManager::firstDate()
{
    Q_D(ModelManager);
    DateItem* tempItem = static_cast<DateItem*>(d->dateModel->getFirst());
    if(nullptr != tempItem)
        return tempItem->dateKey();
    return "";
}

QByteArray ModelManager::dateKey(int index)
{
    Q_D(ModelManager);
    DateItem* tempItem = static_cast<DateItem*>(d->dateModel->get(index));
    if(nullptr != tempItem)
        return tempItem->dateKey();
    return "";
}

void ModelManager::setData(dataUI data, qint64 index)
{
    Q_D(ModelManager);
    DateItem* tempItem;
    tempItem = static_cast<DateItem*>(d->dateModel->get(index));
    if(nullptr != tempItem)
    {
        if(data.dateKey == tempItem->dateKey())
        {
            DateItem* newDateItem = new DateItem(this);
            newDateItem->setData(data);
            d->dateModel->replace(index,newDateItem);
            emit sig_dataReceived(index);
            return;
        }
    }
}

bool ModelManager::dataInited(int index)
{
    Q_D(ModelManager);
    DateItem* tempItem;
    tempItem = static_cast<DateItem*>(d->dateModel->get(index));
    if(nullptr != tempItem)
    {
        return tempItem->dataInited();
    }
    return false;
}

QString ModelManager::imagePath(int index)
{
    Q_D(ModelManager);
    DateItem* tempItem = static_cast<DateItem*>(d->dateModel->get(index));
    if(nullptr != tempItem)
    {
        return tempItem->imageURL();
    }
    return "";
}

QString ModelManager::musicTitle(int index)
{
    Q_D(ModelManager);
    DateItem* tempItem = static_cast<DateItem*>(d->dateModel->get(index));
    if(nullptr != tempItem)
    {
        return tempItem->musicTitle();
    }
    return "";
}

QString ModelManager::musicArtist(int index)
{
    Q_D(ModelManager);
    DateItem* tempItem = static_cast<DateItem*>(d->dateModel->get(index));
    if(nullptr != tempItem)
    {
        return tempItem->musicArtist();
    }
    return "";
}

QString ModelManager::musicURL(int index)
{
    Q_D(ModelManager);
    DateItem* tempItem = static_cast<DateItem*>(d->dateModel->get(index));
    if(nullptr != tempItem)
    {
        return tempItem->musicUrl();
    }
    return "";
}

bool ModelManager::hasMusic(int index)
{
    Q_D(ModelManager);
    DateItem* tempItem = static_cast<DateItem*>(d->dateModel->get(index));
    if(nullptr != tempItem)
    {
        return tempItem->hasMusic();
    }
    return false;
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
