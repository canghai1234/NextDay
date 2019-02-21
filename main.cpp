#include <QGuiApplication>

#include "QMLRegister.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QMLRegister::getSingleton()->registerToQML();

    return app.exec();
}
