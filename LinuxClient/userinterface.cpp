#include "userinterface.h"
#include "ui_userinterface.h"

//Mateusz Gurski
UserInterface::UserInterface(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::UserInterface)
{
  ui->setupUi(this);
  ui->iot_table->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  ui->iot_table->horizontalHeader()->setStretchLastSection(true);

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

//Adam Krizar
void UserInterface::load_devices()
{
  devices = manager.loaddevices();
  if(devices.size() <= 0) return;
  else
  {
    QComboBox *pBox;
    QCheckBox *cBox;
    QWidget *widget;
    QHBoxLayout *layout;
    QLabel *img;
    QPixmap pmap("x.png");
    pmap = pmap.scaled(20, 20, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->iot_table->setRowCount(devices.size());
    for(int i=0; i<devices.size(); i++)
    {
      pBox = new QComboBox();
      pBox->addItem("HTTP");
      pBox->addItem("MQTT");
      cBox = new QCheckBox();
      widget = new QWidget();
      layout = new QHBoxLayout();
      layout->setAlignment(Qt::AlignCenter);
      layout->addWidget(cBox);
      widget->setLayout(layout);
      img = new QLabel;
      img->setPixmap(pmap);
      img->setAlignment(Qt::AlignCenter);
      if(devices[i]->getProtocol() == 0) pBox->setCurrentIndex(1);
      ui->iot_table->setItem(i,0, new QTableWidgetItem(devices[i]->getName()));
      ui->iot_table->setCellWidget(i, 1, pBox);
      ui->iot_table->setCellWidget(i, 3, widget);
      ui->iot_table->setCellWidget(i, 2, img);
    }
  }
}

void UserInterface::closeEvent(QCloseEvent *event)
{
  manager.savedevices(devices);
}


