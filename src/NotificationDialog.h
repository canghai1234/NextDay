#ifndef NOTIFY_H
#define NOTIFY_H

#include <QObject>
#include "Singleton.h"

class NotificationDialog : public QObject, public Singleton<NotificationDialog>
{
    Q_OBJECT

public:
    Q_INVOKABLE void insertNotify(int type, QString string);

signals:
    void sig_newNotify(int errType, QString errString);

};

#endif // NOTIFY_H
