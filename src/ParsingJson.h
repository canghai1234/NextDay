#ifndef PARSINGJSON_H
#define PARSINGJSON_H

#include <QObject>
#include "common.h"

class ParsingJson : public QObject
{
    Q_OBJECT
public:
    explicit ParsingJson(QObject *parent = nullptr);

signals:
    void sig_parsingOK(NetworkData& data);
public slots:
    void slot_parsingSource(QByteArray jsonData);
};

#endif // PARSINGJSON_H
