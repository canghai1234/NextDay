#ifndef IMAGEDOWNLOAD_H
#define IMAGEDOWNLOAD_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>

class ImageDownload : public QObject
{
    Q_OBJECT
public:
    explicit ImageDownload(QObject *parent = 0);
    virtual ~ImageDownload();
    void setFile(QString url,QString filePath);

private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QFile *file;

private slots:
//    void onDownloadProgress(qint64,qint64);
    void onFinished(QNetworkReply*);
//    void onReadyRead();
};


#endif // IMAGEDOWNLOAD_H
