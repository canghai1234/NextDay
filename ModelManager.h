/***************************************************************************
    Copyright (C) 2017 by ZhaoDongshuang
    Author: ZhaoDongshuang
    Email: imtoby@126.com
    Date: 2017/11/07
    File: ObjectModel.h

    Modified: 2019/02/21 by "github.com/canghai1234"
 ***************************************************************************/


#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <QObject>
#include "DateModel.h"

class ModelManagerPrivate;

class ModelManager : public QObject
{
    Q_OBJECT
public:
    explicit ModelManager(QObject *parent = nullptr);
    ~ModelManager();

    Q_INVOKABLE void initData();
    Q_INVOKABLE DateModel* dateModel();

    void append(QByteArray date);
    void insert(QByteArray date,int index = 0);
private:
    QScopedPointer<ModelManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(ModelManager)
};
#endif // MODELMANAGER_H
