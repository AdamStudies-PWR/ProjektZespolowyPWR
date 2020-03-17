#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFile>
#include <QVector>
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <QDataStream>
#include "iot.h"

using namespace std;


//Adam Krizar
class filemanager
{
private:
  QString filename = "appdata";
public:
  filemanager();
  QVector<iot*> loaddevices();
  void savedevices(QVector<iot*>);
};

#endif // FILEMANAGER_H
