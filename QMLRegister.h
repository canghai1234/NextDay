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
    static void registerToQML();
signals:


protected:
    static QObject* backendProvider(QQmlEngine *, QJSEngine *){return Backend::getSingleton();}
public slots:
};

#endif // QMLREGISTER_H
