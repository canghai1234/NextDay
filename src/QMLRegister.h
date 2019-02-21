#ifndef QMLREGISTER_H
#define QMLREGISTER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "Singleton.h"
#include "Backend.h"

class QMLRegister : public QObject , public Singleton<QMLRegister>
{
    Q_OBJECT
public:
    void registerToQML();
signals:


protected:
    static QObject* backendProvider(QQmlEngine *, QJSEngine *){return Backend::getSingleton();}

private:
    QQmlApplicationEngine *engine;
};

#endif // QMLREGISTER_H
