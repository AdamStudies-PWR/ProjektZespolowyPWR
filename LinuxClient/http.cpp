#include "http.h"

//Mateusz Gurski
Http_client::Http_client(QObject *parent) : QObject(parent)
{
connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(readReady(QNetworkReply*)));
}

//Mateusz Gurski
Http_client::~Http_client()
{

}

//Mateusz Gurski
void Http_client::get_request(QString location)
{
    const QUrl url = QUrl(location);
    QNetworkRequest request(url);

    manager->get(request);
}

//Mateusz Gurski
void Http_client::readReady(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    emit(dataReady(data));
}

//Mateusz Gurski
QString Http_client::toString() {return "Http";}
