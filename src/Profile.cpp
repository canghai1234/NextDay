#include "Profile.h"
#include <QSettings>

Profile::Profile(QObject *parent) : QObject(parent)
{
    _userScale = 100;
}

void Profile::readParameter(QString filePath)
{
    _filePath = filePath;
    QSettings settings (_filePath, QSettings::IniFormat ,this);
    settings.beginGroup("TextScale");
    _userScale = settings.value("TextScale/UserCustom",100).toInt();
    if(_userScale < 50 || _userScale > 150)
        _userScale = 100;
    settings.endGroup();
}

void Profile::setTextScaleUser(int scale)
{
    _userScale = scale;
    saveParameter();
}

int Profile::getTextScaleUser()
{
    return _userScale;
}

void Profile::saveParameter()
{
    QSettings settings (_filePath, QSettings::IniFormat ,this);
    settings.beginGroup("TextScale");
    settings.setValue("TextScale/UserCustom", _userScale);
    settings.endGroup();
}
