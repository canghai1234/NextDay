#ifndef DATETIME_H
#define DATETIME_H

#include <QObject>

class DateTime : public QObject
{
    Q_OBJECT
public:
    explicit DateTime(QObject *parent = nullptr);

    QByteArray getToday();
    QByteArray getYesterday(QString date,int day = 1);
    QByteArray getTomorrow(QString date,int day = 1);

    QString getDay(QString date);
    QString getMonthShort(QString date);
    QString getWeek(QString date);

    qint64 daysTo(QByteArray date,QByteArray refDate);
signals:

public slots:

private:
    bool isDateValid(const QString& date);
};

#endif // DATETIME_H
