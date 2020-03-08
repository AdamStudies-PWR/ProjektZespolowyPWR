#include "http.h"

Http_client::Http_client(QObject *parent) : QObject(parent)
{
connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(readReady(QNetworkReply*)));
}

Http_client::~Http_client()
{

}

void Http_client::get_request(QString location)
{
    const QUrl url = QUrl(location);
    QNetworkRequest request(url);

    manager->get(request);
}

void Http_client::readReady(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    emit(dataReady(data));
}


