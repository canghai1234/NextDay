#include "ImageDownload.h"
#include "NotificationDialog.h"

ImageDownload::ImageDownload(QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager;
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onFinished(QNetworkReply*)),Qt::UniqueConnection);
}

ImageDownload::~ImageDownload()
{
    manager->deleteLater();
}

void ImageDownload::setFile(QString url,QString filePath)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    manager->get(request);

    file = new QFile;
    file->setFileName(filePath);
    file->open(QIODevice::ReadWrite);
}

void ImageDownload::onFinished(QNetworkReply * reply)
{
    switch(reply->error())
    {
    case QNetworkReply::NoError:
    {
        if(file->isOpen())
        {
            file->write(reply->readAll());
            QString fileName = file->fileName();
            file->close();
            file->deleteLater();
            NotificationDialog::getSingleton()->insertNotify(1,"背景图片保存成功,位于： " + fileName);
        }
    }break;
    default:{
        NotificationDialog::getSingleton()->insertNotify(2,"背景图片保存失败");
    };
    }

}


