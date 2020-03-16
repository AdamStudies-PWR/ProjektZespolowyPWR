#include "userinterface.h"
#include "ui_userinterface.h"

UserInterface::UserInterface(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::UserInterface)
{
  ui->setupUi(this);

  connect(&http, SIGNAL(dataReady(QByteArray)), this, SLOT(http_get_response(QByteArray)));

  load_devices();
}

UserInterface::~UserInterface()
{
    delete ui;
}

void UserInterface::on_pushButton_clicked()
{
    http.get_request(myURL);
}

void UserInterface::http_get_response(QByteArray data)
{
    QString DataAsString = QString(data);
    ui->textEdit->setText(data);

}

void UserInterface::load_devices()
{
  devices = manager.loaddevices();
}


