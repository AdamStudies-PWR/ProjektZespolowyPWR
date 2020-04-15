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

  ui->pushButton_3->setVisible(false);

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
    QModelIndexList selection = ui->iot_table->selectionModel()->selectedRows();

    if (selection.size() > 0){

        QModelIndex index = selection.at(0);

        int row = index.row();

        if (devices[row]->getProtocol() == 1){

            connected_device = devices[row];

            http.get_request("http://"+connected_device->getIP()+"/sensors");

            ui->pushButton->setVisible(false);

        }
    }
}

//Mateusz Gurski
void UserInterface::http_get_response(QByteArray data)
{
    QString DataAsString = QString(data);

    if (ui->pushButton_3->isVisible()){

        sensor_readings.append(data);

        if(sensor_readings.size() == sensor_units.size() && sensor_units.size()>0){
            for (int i = 0;i<sensor_readings.size();i++) {
                QString reading = sensors_list[i] + ": " + sensor_readings[i] + " " + sensor_units[i];
                ui->textEdit->append(reading);
            }
            sensor_readings.clear();
        }

    }
    else{
        ui->textEdit->clear();
        ui->textEdit->setText("Avaiable sensors: " + data);

        sensors = data;

        QStringList sensors_tmp_list = sensors.split(" ");

        sensor_units.clear();
        for(int i=0;i<sensors_tmp_list.size();i++){
            QStringList tmp = sensors_tmp_list[i].split(":");

            if (tmp.size() > 1){
                sensors_list.append(tmp[0]);
                sensor_units.append(tmp[1]);
            }
        }

        ui->pushButton_3->setVisible(true);
    }

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

void UserInterface::on_addButton_clicked()
{

}


void UserInterface::on_pushButton_3_clicked()
{
   if(connected_device != nullptr){
        if (connected_device->getProtocol() == 1){

             http.get_request("http://"+connected_device->getIP()+"/temperature");
             http.get_request("http://"+connected_device->getIP()+"/humidity");

        }
   }

}

void UserInterface::on_connectButton_clicked()
{
    ui->pushButton_3->setVisible(false);
    ui->pushButton->setVisible(true);
    ui->textEdit->clear();
}
