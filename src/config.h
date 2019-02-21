/***************************************************************************
    Copyright (C) 2017 by ZhaoDongshuang
    Author: ZhaoDongshuang
    Email: imtoby@126.com
    Date: 2017/11/07
    File: ObjectModel.h

    Modified: 2019/02/21 by "github.com/canghai1234"
 ***************************************************************************/
#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#define C_D(Class) const Class##Private * const d = d_func()
typedef QList<QObject* > QObjectList;

#endif // CONFIG_H
