QT += quick qml core network


TEMPLATE = app
TARGET = NextDay

CONFIG += c++11
CONFIG += qtquickcompiler

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    HttpRequest.cpp \
    DateTime.cpp \
    ParsingJson.cpp \
    RequestImage.cpp \
    Backend.cpp \
    QMLRegister.cpp \
    DateModel/DateModel.cpp \
    DateModel/DateItem.cpp \
    DateModel/ModelManager.cpp \
    NotificationDialog.cpp \
    ImageDownload.cpp \
    Profile.cpp

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
#QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

HEADERS += \
    HttpRequest.h \
    DateTime.h \
    common.h \
    ParsingJson.h \
    RequestImage.h \
    Backend.h \
    Singleton.h \
    QMLRegister.h \
    DateModel/DateModel.h \
    DateModel/DateItem.h \
    DateModel/config.h \
    DateModel/ModelManager.h \
    apikey.h \
    NotificationDialog.h \
    ImageDownload.h \
    Profile.h

RESOURCES += qml.qrc \
    font.qrc \
    icon.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/res/values/libs.xml \
    android/build.gradle
    android/gradle.properties

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
