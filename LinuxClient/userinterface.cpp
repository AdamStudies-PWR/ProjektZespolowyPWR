#include "userinterface.h"
#include "ui_userinterface.h"
bool first = true;
bool mqttAwaitingOutput = false;
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

    //connect(ui->lineEditHost, &QLineEdit::textChanged, m_client, &QMqttClient::setHostname);
    //connect(ui->spinBoxPort, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setClientPort);
    //updateLogStateChange();

    load_devices();
}

//void UserInterface::updateLogStateChange()
//{
//    const QString content = QDateTime::currentDateTime().toString()
//                    + QLatin1String(": State Change")
//                    + QString::number(m_client->state())
//                    + QLatin1Char('\n');
//    ui->textEdit->append(content);
//}

void UserInterface::brokerDisconnected()
{
    //ui->lineEditHost->setEnabled(true);
    //ui->spinBoxPort->setEnabled(true);
    //ui->buttonConnect->setText(tr("Connect"));
}

//void UserInterface::con()
//{
//    if (m_client->state() == QMqttClient::Disconnected) {
//        //ui->lineEditHost->setEnabled(false);
//        //ui->spinBoxPort->setEnabled(false);
//        //ui->buttonConnect->setText(tr("Disconnect"));
//        m_client->connectToHost();
//    } else {
//        //ui->lineEditHost->setEnabled(true);
//        //ui->spinBoxPort->setEnabled(true);
//        //ui->buttonConnect->setText(tr("Connect"));
//        m_client->disconnectFromHost();
//    }
//}

//void UserInterface::sub()
//{
//    QString topic = "broker/humidity";
//    QString topic2 = "broker/tempereture";
//    auto subscription = m_client->subscribe(topic);
//    auto subscription2 = m_client->subscribe(topic2);
//    if (!subscription || !subscription2) {
//        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
//        return;
//    }
//}

UserInterface::~UserInterface()
{
    delete ui;
}

//Mateusz Gurski
void UserInterface::on_pushButton_clicked()
{
    japierdole:
    if(helpmode)
    {
        QMessageBox info;
        info.setWindowTitle("Pomoc");
        info.setText("Łączy się z wybranym urządzeniem");
        info.exec();

        return;
    }

    QModelIndexList selection = ui->iot_table->selectionModel()->selection().indexes();

    if (selection.size() > 0){

        QModelIndex index = selection.at(0);

        int row = index.row();

        if (devices[row]->getProtocol() == 1){

            connected_device = devices[row];

            http.get_request("http://"+connected_device->getIP()+"/sensors");

            ui->pushButton->setVisible(false);

        }
        else if(devices[row]->getProtocol() == 2)
        {
            //TODO
            connected_device = devices[row];
            //connected_device->m_client = new QMqttClient();
            connected_device->m_client->setHostname(connected_device->getIP());
            connected_device->m_client->setPort(1883);
            if(first)
            {
                connect(connected_device->m_client, &QMqttClient::disconnected, this, &UserInterface::brokerDisconnected);
                connect(connected_device->m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
                    if(mqttAwaitingOutput)
                    {const QString content = QDateTime::currentDateTime().toString()
                                + QLatin1String(" Received Topic: ")
                                + topic.name()
                                + QLatin1String(" Message: ")
                                + message
                                + QLatin1Char('\n');
                    ui->textEdit->insertPlainText(content);
                    mqttAwaitingOutput=false;
                    }
                });

                connect(connected_device->m_client, &QMqttClient::pingResponseReceived, this, [this]() {
                    if(mqttAwaitingOutput)
                    {const QString content = QDateTime::currentDateTime().toString()
                                + QLatin1String(" PingResponse")
                                + QLatin1Char('\n');
                    ui->textEdit->insertPlainText(content);
                    mqttAwaitingOutput=false;
                    }
                });
            }
            //connect(connected_device->m_client, &QMqttClient::stateChanged, this, &UserInterface::updateLogStateChange);
            //ui->textEdit->insertPlainText(mqtt.GetHost(connected_device->m_client) + '\n');
            //mqtt.Connect(connected_device->m_client);
            connected_device->m_client->connectToHost();
            if(connected_device->m_client->state() == QMqttClient::Disconnected)
                ui->textEdit->append("kurwa");
            QString topic = "broker/temperature";
            connected_device->m_client->publish(topic, topic.toUtf8());
            QMqttSubscription *sub;
            sleep(2);
            sub = connected_device->m_client->subscribe(topic);
            sleep(2);
            if(!sub)
                ui->textEdit->insertPlainText("Cannot subscribe to " + topic + '\n');
//            topic = "broker/humidity";
//            sub = connected_device->m_client->subscribe(topic);
//            if(!sub)
//                ui->textEdit->insertPlainText("Cannot subscribe to " + topic + '\n');
            if(first)
            {
                first = false;
                goto japierdole;
            }
            ui->pushButton_3->setVisible(true);
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
    display();
}

void UserInterface::display()
{
    if(devices.size() <= 0) return;
    else
    {
        QComboBox *pBox;
        QLabel *img;
        QPixmap pmap("x.png");
        pmap = pmap.scaled(20, 20, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->iot_table->setRowCount(devices.size());
        for(int i=0; i<devices.size(); i++)
        {
            pBox = new QComboBox();
            pBox->addItem("HTTP");
            pBox->addItem("MQTT");
            img = new QLabel;
            img->setPixmap(pmap);
            img->setAlignment(Qt::AlignCenter);
            if(devices[i]->getProtocol() == 0) pBox->setCurrentIndex(1);
            ui->iot_table->setItem(i,0, new QTableWidgetItem(devices[i]->getName()));
            ui->iot_table->setCellWidget(i, 1, pBox);
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
    if(helpmode)
    {
        QMessageBox info;
        info.setWindowTitle("Pomoc");
        info.setText("Dodaje urządzenie o podanych informacjach:\n"
                     "Nazwa\n"
                     "Numer IP w formacie 192.168.0.1");
        info.exec();

        return;
    }

    int ip_ad[4];
    iot* device;
    int index = devices.size();
    bool ok, correct=true;

    QString name = QInputDialog::getText(this, "Dodaj", "Nazwa urządzenia", QLineEdit::Normal, "", &ok);
    if(ok)
    {
        QString ip = QInputDialog::getText(this, "Dodaj", "Adres IP", QLineEdit::Normal, "", &ok);
        QRegExp ipFormat("^[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}$");
        if(ok && ipFormat.exactMatch(ip))
        {
            QStringList iplist = ip.split(".");
            ip_ad[0] = iplist.value(0).toInt();
            ip_ad[1] = iplist.value(1).toInt();
            ip_ad[2] = iplist.value(2).toInt();
            ip_ad[3] = iplist.value(3).toInt();
            for (int i=0; i<4; i++)if(ip_ad[i]>255 || ip_ad[i]<0)correct=false;

            if(correct)
            {

                QString protocol = QInputDialog::getText(this, "Dodaj", "Protokół", QLineEdit::Normal, "", &ok);

                int p = 0;

                if(ok)
                {
                    if(protocol == "http" || protocol == "HTTP"){
                      p = 1;
                    }
                    else if(protocol == "mqtt" || protocol == "MQTT")
                    {
                        p=2;
                    }

                    device = new iot(index, name, ip_ad, p);
                    devices.push_back(device);
                    display();

                }
            }
        }
    }
}

void UserInterface::on_pushButton_3_clicked()
{
    if(helpmode)
    {
        QMessageBox info;
        info.setWindowTitle("Pomoc");
        info.setText("Wyświetla dane odczytane z połączonego czujnika");
        info.exec();

        return;
    }

   if(connected_device != nullptr){
        if (connected_device->getProtocol() == 1){

            for (int i=0;i<sensors_list.size();i++) {
                http.get_request("http://"+connected_device->getIP()+"/"+sensors_list[i]);
            }
        }
        else if(connected_device->getProtocol()==2)
        {
            //TODO MqttLib
            mqttAwaitingOutput = true;
        }
   }
}

void UserInterface::on_connectButton_clicked()
{
    if(helpmode)
    {
        QMessageBox info;
        info.setWindowTitle("Pomoc");
        info.setText("Rozłącza urządzenie i czyści pole tekstowe");
        info.exec();

        return;
    }

    ui->pushButton_3->setVisible(false);
    ui->pushButton->setVisible(true);
    ui->textEdit->clear();
}

void UserInterface::on_actionO_programie_triggered()
{
    if(helpmode)
    {
        QMessageBox info;
        info.setWindowTitle("Pomoc");
        info.setText("Wyświetla informacje o programie");
        info.exec();

        return;
    }

    QMessageBox info;
    info.setWindowTitle("O programie");
    info.setText("Informacje o programie \n\n"
                 "Aplikacja do zarządzania urządzeniami IoT \n"
                 "Qt 5.14.1");
    info.exec();
}

void UserInterface::on_actionInstrukcja_obs_ugi_triggered()
{
    if(helpmode)
    {
        QMessageBox info;
        info.setWindowTitle("Pomoc");
        info.setText("Wyświetla instrukcję obsługi programu");
        info.exec();

        return;
    }

    QMessageBox help;
    help.setWindowTitle("Instrukcja");
    help.setText("Instrukcja obsługi programu \n\n"
                 "Lista urządzeń zapisuje się automatycznie przy zamknięciu programu!\n\n"
                 "W celu dodania nowego urządzenia do listy urządzeń należy wcisnąć przycisk 'Dodaj'.\n\n"
                 "Żeby wybrać urządzenie należy wcisnąć numer odpowiadającego mu wiersza po lewej.\n\n"
                 "Po wybraniu wiersza można połączyć się z wybranym urządzeniem za pomocą przycisku "
                 "'Połącz'. \n Następnie w celu uzyskania odczytu należy wcisnąć 'Odczyt'.\n\n"
                 "Do zakończenia pracy na obecnym urządzeniu należy wcisnąć 'Rozłącz'.\n\n"
                 "Żeby usunąć urządzenie z listy należy po wybraniu go w tablicy wcisnąć 'Usuń'.\n\n"
                 "W celu zapisania listy urządzeń należy otworzyć zakładkę 'Plik'.");
    help.exec();
}

void UserInterface::on_subClose_triggered()
{
    if(helpmode)
    {
        QMessageBox info;
        info.setWindowTitle("Pomoc");
        info.setText("Zamyka program");
        info.exec();

        return;
    }

    QCoreApplication::quit();
}

void UserInterface::on_actionZapisz_dane_z_sesnor_triggered()
{
    bool ok;
    QString fname = QInputDialog::getText(this, "Zapis", "Nazwa pliku", QLineEdit::Normal, "appdata", &ok);

    if(ok && !fname.isEmpty())
    {
        manager.setFilename(fname);
        manager.savedevices(devices);
    }
}

void UserInterface::on_actionZapis_okresowy_triggered()
{
    if(helpmode)
    {
        QMessageBox info;
        info.setWindowTitle("Pomoc");
        info.setText("Pozwala na ustalenie okresu czasu, co jaki ma być dokonywany zapis"
                     "oraz nazwy pliku, do którego dane o urządzeniach mają być zapisane. \n"
                     "Okres czasu może być w przedziale od 1 do 360 minut. ");
        info.exec();

        return;
    }

    bool ok;
    int time = QInputDialog::getInt(this, "Zapis okresowy", "Przedzial czasu w minutach:", 5, 1, 360, 1, &ok);
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
    if(helpmode)
    {
        QMessageBox info;
        info.setWindowTitle("Pomoc");
        info.setText("Usuwa wybrane urządzenie z listy");
        info.exec();

        return;
    }

    QModelIndexList selection = ui->iot_table->selectionModel()->selectedRows();

    if (selection.size() > 0)
    {
        QMessageBox confirm;
        confirm.setText("Czy na pewno chcesz usunąć wybrane urządzenie?");
        confirm.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        int ret = confirm.exec();

        if(ret==QMessageBox::Ok)
        {
            QModelIndex index = selection.at(0);
            int row = index.row();

            devices.removeAt(row);

            display();
        }
    }
}


void UserInterface::on_actionTryb_programisty_triggered()
{
    if(helpmode)
    {
        QMessageBox info;
        info.setWindowTitle("Pomoc");
        info.setText("Pozwala przejść w tryb programisty:\n\n"
                     "Sprawdzenie łączności Wi-Fi - automatyczne\n"
                     "Test łączności z ręcznie wpisanym adresem - należy ręcznie zmienić "
                     "domyślne 0.0.0.0 na adres, z którym chcemy sprawdzić łączność");
        info.exec();

        return;
    }


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


void UserInterface::on_helpButton_clicked()
{
    if(helpmode)
    {
        helpmode=false;
        this->setCursor(Qt::ArrowCursor);
    }
    else
    {
        helpmode=true;
        this->setCursor(Qt::WhatsThisCursor);

    }
}
