#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "HttpRequest.h"
#include "DateTime.h"
int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    HttpRequest http;
    http.slot_requestData("20190124");

    return app.exec();
}
