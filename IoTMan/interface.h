#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <QByteArray>
#include <QString>
//#include "http.h"

class Interface : public QObject
{
    Q_OBJECT
private:
    //Testing the get request
    QString myURL = "https://www.youtube.com";
   // Http_client http;
public:
    explicit Interface(QObject *parent = nullptr);

signals:

private slots:
    //void http_get_response(QByteArray);

public slots:
    void testClick();
};

#endif // INTERFACE_H
