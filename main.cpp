#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "QMLRegister.h"
#include <QFontDatabase>

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

//    //设置字体,并将字体文件打包进apk
//    int avenirLightID = QFontDatabase::addApplicationFont(":/font/Avenir Next Ultra Light.ttf");
//    //将字体Id传给applicationFontFamilies,得到一个QStringList,其中的第一个元素为新添加字体的family
//    QString avenirLight = QFontDatabase::applicationFontFamilies(avenirLightID).at(0);
//    QFont font(avenirLight);
//    QGuiApplication::setFont(font);


    QMLRegister::getSingleton()->registerToQML();


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}
