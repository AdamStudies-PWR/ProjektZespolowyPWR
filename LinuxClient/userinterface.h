#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QVector>
#include <QComboBox>
#include <QCheckBox>
#include <QImage>
#include <QLabel>
#include <QFileDialog>
#include <QInputDialog>
#include <QStringList>
#include "filemanager.h"
#include "http.h"
#include "iot.h"
#include "QTime"
#include "QTimer"
#include "QThread"

QT_BEGIN_NAMESPACE
namespace Ui { class UserInterface; }
QT_END_NAMESPACE

class UserInterface : public QMainWindow
{
    Q_OBJECT

public:
    UserInterface(QWidget *parent = nullptr);
    ~UserInterface();

private slots:
    void on_pushButton_clicked();
    void http_get_response(QByteArray);
    void load_devices();
    void display();
    void closeEvent(QCloseEvent *event);

    void on_addButton_clicked();

    void on_pushButton_3_clicked();

    void on_connectButton_clicked();

    void on_actionO_programie_triggered();

    void on_actionInstrukcja_obs_ugi_triggered();

    void on_subClose_triggered();

    void on_actionZapisz_dane_z_sesnor_triggered();

    void on_actionZapis_okresowy_triggered();

    void on_deleteButton_clicked();

    void on_actionTryb_programisty_triggered();

    void on_pushButton_2_clicked();

    void on_helpButton_clicked();

private:
    Http_client http;
    filemanager manager;
    QVector<iot*> devices;
    QString sensors;
    QStringList sensors_list;
    QStringList sensor_units;
    QStringList sensor_readings;
    iot *connected_device;

    bool wifi_connection_test = false;
    bool iot_connection_test = false;
    bool helpmode = false;

    QThread time;

    //Testing the get request
    QString myURL = "http://172.16.0.5/temperature";

    Ui::UserInterface *ui;
};
#endif // USERINTERFACE_H
