#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>

class Profile : public QObject
{
    Q_OBJECT
public:
    explicit Profile(QObject *parent = nullptr);
    void readParameter(QString filePath);

    Q_INVOKABLE void setTextScaleUser(int scale);
    Q_INVOKABLE int getTextScaleUser();
signals:

public slots:

private:
    void saveParameter();
    int _userScale;
    QString _filePath;
};

#endif // PROFILE_H
