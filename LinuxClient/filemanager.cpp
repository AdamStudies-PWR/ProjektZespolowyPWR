#include "filemanager.h"

filemanager::filemanager()
{

}

QVector<iot*> filemanager::loaddevices()
{
  QVector<iot*> data;
  QMessageBox mBox;
  QFile file(filename + ".bin");
  if(!file.open(QFile::ReadOnly))
  {
    mBox.critical(0, "Błąd", "Nie otworzyć pliku konfiguracji!");
    mBox.setFixedSize(500, 200);
  }
  else
  {
    int ip_ad[4];
    QTextStream in(&file);
    QString line;
    do
    {
        line = in.readLine();
        if(line == "") break;
        QStringList list = line.split("/");
        QString ip = list.value(3);
        QStringList iplist = ip.split(".");
        ip_ad[0] = iplist.value(0).toInt();
        ip_ad[1] = iplist.value(1).toInt();
        ip_ad[2] = iplist.value(2).toInt();
        ip_ad[3] = iplist.value(3).toInt();
        data.push_back(new iot(list.value(0).toInt(), list.value(1), ip_ad, list.value(2).toInt()));
    }
    while(!line.isNull());
    file.close();
  }
  return data;
}

void filemanager::savedevices(QVector<iot*> data)
{
  QMessageBox mBox;
  QFile file(filename + ".bin");
  if(file.exists()) file.remove();
  if(!file.open(QFile::WriteOnly))
  {
    mBox.critical(0, "Błąd", "Nie można zapisać konfiguracji do pliku!");
    mBox.setFixedSize(500, 200);
  }
  else
  {
    int *ip;
    QTextStream out(&file);
    for(int i=0; i<data.size(); i++)
    {
      out << data[i]->getDevice_id() << "/" << data[i]->getDevice_name() << "/" << data[i]->getProtocol() << "/";
      ip = data[i]->getDevice_ip();
      out << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << "\n";
    }
    file.close();
  }
}
