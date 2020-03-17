#include "userinterface.h"
#include "ui_userinterface.h"

//Mateusz Gurski
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

//Mateusz Gurski
void UserInterface::on_pushButton_clicked()
{
    http.get_request(myURL);
}

//Mateusz Gurski
void UserInterface::http_get_response(QByteArray data)
{
    QString DataAsString = QString(data);
    ui->textEdit->setText(data);

}

void UserInterface::load_devices()
{
  devices = manager.loaddevices();
  if(devices.size() <= 0) return;
  else
  {
    for(int i=0; i<devices.size(); i++)
    {
      //iot_table->setItem(devices.)
    }
  }
}

void UserInterface::closeEvent(QCloseEvent *event)
{
  manager.savedevices(devices);
}


