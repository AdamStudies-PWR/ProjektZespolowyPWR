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
  ui->textEdit_2->setVisible(false);

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
    else
    {
        ui->textEdit_2->setText("No device selected");
    }
}

//Mateusz Gurski
void UserInterface::http_get_response(QByteArray data)
{
    QString DataAsString = QString(data);

    if(wifi_connection_test)
    {
        if(data.size() > 0)
        {
            ui->textEdit_2->append("WiFi connection seems OK");
            wifi_connection_test = false;
            return;
        }
        else
        {
            ui->textEdit_2->append("Check your WiFi connection");
            wifi_connection_test = false;
            return;
        }
    }

    if(iot_connection_test)
    {
        if(data.size() > 0)
        {
            ui->textEdit_2->append("Response received: ");
            ui->textEdit_2->append(data);
            iot_connection_test = false;
            return;
        }
        else
        {
            ui->textEdit_2->append("IoT not responding.");
            iot_connection_test = false;
            return;
        }
    }


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

        if (sensors.size() == 0)
        {
            ui->textEdit_2->setText("No sensors detected. Device ip may be wrong or "
                                    "the device is offline");

            return;
        }

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
    int ip_ad[4];
    iot* device;
    int index = devices.size();
    bool ok, correct=true;

    QString name = QInputDialog::getText(this, "Dodaj", "Nazwa urządzenia", QLineEdit::Normal, "", &ok);
    if(ok)
    {
        QString ip = QInputDialog::getText(this, "Dodaj", "Adres IP", QLineEdit::Normal, "", &ok);
        if(ok)
        {
            QStringList iplist = ip.split(".");
            ip_ad[0] = iplist.value(0).toInt();
            ip_ad[1] = iplist.value(1).toInt();
            ip_ad[2] = iplist.value(2).toInt();
            ip_ad[3] = iplist.value(3).toInt();
            for (int i=0; i<4; i++)if(ip_ad[i]>255 || ip_ad[i]<0)correct=false;

            if(correct)
            {
                device = new iot(index, name, ip_ad, 0);
                devices.push_back(device);
            }
        }
    }
}

void UserInterface::on_pushButton_3_clicked()
{
   if(connected_device != nullptr){
        if (connected_device->getProtocol() == 1){

            for (int i=0;i<sensors_list.size();i++) {
                http.get_request("http://"+connected_device->getIP()+"/"+sensors_list[i]);
            }
        }
   }
}

void UserInterface::on_connectButton_clicked()
{
    ui->pushButton_3->setVisible(false);
    ui->pushButton->setVisible(true);
    ui->textEdit->clear();
}

void UserInterface::on_actionO_programie_triggered()
{
    QMessageBox info;
    info.setWindowTitle("O programie");
    info.setText("Informacje o programie \n\n"
                 "Aplikacja do zarządzania urządzeniami IoT \n"
                 "Qt 5.14.1");
    info.exec();
}

void UserInterface::on_actionInstrukcja_obs_ugi_triggered()
{
    QMessageBox help;
    help.setWindowTitle("Instrukcja");
    help.setText("Instrukcja obsługi programu \n\n");
    help.exec();
}

void UserInterface::on_subClose_triggered()
{
    QCoreApplication::quit();
}

void UserInterface::on_actionZapisz_dane_z_sesnor_triggered()
{
    bool ok;
    QString fname = QInputDialog::getText(this, "Zapis", "Nazwa pliku", QLineEdit::Normal, "dane_IoT", &ok);

    if(ok && !fname.isEmpty())
    {
        manager.setFilename(fname);
        manager.savedevices(devices);
    }
}

void UserInterface::on_actionZapis_okresowy_triggered()
{
    bool ok;
    int time = QInputDialog::getInt(this, "Zapis okresowy", "Przedzial czasu w minutach:", 5, 1, 60, 1, &ok);
    if(ok)
    {
        QString fname = QInputDialog::getText(this, "Zapis okresowy", "Nazwa pliku", QLineEdit::Normal, "dane_IoT", &ok);
        if(ok && !fname.isEmpty())
        {
            manager.setFilename(fname);
            manager.savedevices(devices);
        }
    }
}

void UserInterface::on_deleteButton_clicked()
{
    QModelIndexList selection = ui->iot_table->selectionModel()->selectedRows();

    if (selection.size() > 0)
    {
        QModelIndex index = selection.at(0);
        int row = index.row();

        devices.removeAt(row);
    }
}

void UserInterface::on_actionTryb_programisty_triggered()
{

    if(ui->textEdit_2->isVisible())
    {
        ui->textEdit_2->setVisible(false);
    }
    else
    {
        ui->textEdit_2->setVisible(true);

        wifi_connection_test = true;

        ui->textEdit_2->setText("Running Wifi connection test..");

        http.get_request("https://postman-echo.com/get?foo1");

        bool iot_test;

        QString fname = QInputDialog::getText(this, "Test łączności z IoT", "Wpisz adres zapytania", QLineEdit::Normal, "http://0.0.0.0/sensors", &iot_test);

        if(iot_test && !fname.isEmpty())
        {
            ui->textEdit_2->append("Running app<->IoT connection test..");

            iot_connection_test = true;

            http.get_request(fname);

        }

    }
}

