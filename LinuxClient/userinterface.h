#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
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

private:
  Http_client http;

  //Testing the get request
  QString myURL = "https://www.youtube.com/watch?v=O-kDhSWRcgo";

  Ui::UserInterface *ui;
};
#endif // USERINTERFACE_H
