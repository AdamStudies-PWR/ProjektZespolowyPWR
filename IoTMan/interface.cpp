#include "interface.h"

Interface::Interface(QObject *parent) : QObject(parent)
{

}

void Interface::testClick()
{
   // http.get_request(myURL);
}

/*void Interface::http_get_response(QByteArray data)
{
    QString DataAsString = QString(data);
    //ui->textEdit->setText(data);
}*/
