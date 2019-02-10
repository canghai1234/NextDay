#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "QMLRegister.h"

/*
 * 1. 获取当前设备信息
 * 2. 获取当前日期
 * 3. http 请求 json 字符串
 * 4. 解析 json 字符串
 * 5. 请求网络图片
 * 6. 显示到页面上
*/
int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QMLRegister::getSingleton()->registerToQML();


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}
