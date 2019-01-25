#ifndef PARSINGJSON_H
#define PARSINGJSON_H

#include <QObject>

class ParsingJson : public QObject
{
    Q_OBJECT
    void parse();
public:
    explicit ParsingJson(QObject *parent = nullptr);

signals:

public slots:
};

#endif // PARSINGJSON_H
