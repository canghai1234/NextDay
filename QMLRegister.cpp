#include "QMLRegister.h"
#include "Backend.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QGuiApplication>
#include <QDebug>

void QMLRegister::registerToQML()
{
    qmlRegisterSingletonType<Backend>("NextDay",0,1,"Backend",backendProvider);
    Backend::getSingleton()->init();



    engine = new QQmlApplicationEngine;

    qmlRegisterUncreatableType<DateModel, 1>("Next", 1, 0, "DateModel", "Cannot create DateModel");
    engine->rootContext()->setContextProperty("todayModelManage", Backend::getSingleton()->getTodayListManage()/*->dateModel()*/);

    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine->rootObjects().isEmpty())
    {
        qDebug() << "exit -1";
        qApp->exit(-1);
    }
}
