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
  void closeEvent(QCloseEvent *event);

  void on_addButton_clicked();

  void on_pushButton_3_clicked();

  void on_connectButton_clicked();

private:
  Http_client http;
  filemanager manager;
  QVector<iot*> devices;
  QString sensors;
  QStringList sensors_list;
  QStringList sensor_units;
  QStringList sensor_readings;
  iot *connected_device;

  QThread time;

  //Testing the get request
  QString myURL = "http://172.16.0.5/temperature";

  Ui::UserInterface *ui;
};
#endif // USERINTERFACE_H
