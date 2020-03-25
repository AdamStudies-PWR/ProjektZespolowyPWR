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

private:
  Http_client http;
  filemanager manager;
  QVector<iot*> devices;

  //Testing the get request
  QString myURL = "https://www.youtube.com";

  Ui::UserInterface *ui;
};
#endif // USERINTERFACE_H
