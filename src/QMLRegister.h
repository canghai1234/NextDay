#ifndef QMLREGISTER_H
#define QMLREGISTER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "Backend.h"
#include "NotificationDialog.h"

class QMLRegister : public QObject , public Singleton<QMLRegister>
{
    Q_OBJECT
public:
    void registerToQML();
signals:


protected:
    static QObject* backendProvider(QQmlEngine *, QJSEngine *){return Backend::getSingleton();}

    static QObject* notifyProvider(QQmlEngine *, QJSEngine *){return NotificationDialog::getSingleton();}

private:
    QQmlApplicationEngine *engine;
};

#endif // QMLREGISTER_H
