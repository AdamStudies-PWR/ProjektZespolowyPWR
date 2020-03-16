#ifndef HTTP_H
#define HTTP_H
#include <QObject>
#include <QDebug>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>

using namespace std;

class Http_client : public QObject{

    Q_OBJECT

public:
    explicit Http_client(QObject *parent = 0);
    ~Http_client();

    //HTTP GET
    void get_request(QString);
    QString toString();

signals:
    //The signal is emitted to let the GUI know, that the data is ready
    void dataReady(QByteArray);

private slots:
    void readReady(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

};


#endif // HTTP_H
