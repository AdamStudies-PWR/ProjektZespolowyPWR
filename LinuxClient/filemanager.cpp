#include "filemanager.h"

filemanager::filemanager()
{

}

//Adam Krizar
QVector<iot*> filemanager::loaddevices()
{
  QVector<iot*> data;
  QMessageBox mBox;
  QFile file(filename + ".bin");
  if(file.open(QFile::ReadOnly))
  {
    int ip_ad[4];
    QTextStream in(&file);
    QString line;
    do
    {
        try
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
        catch(exception)
        {
          mBox.critical(0, "Błąd", "Błąd wczytywania danych konfiguracyjnych. Niepoprawne dane!");
          mBox.setFixedSize(500, 200);
        }
    }
    while(!line.isNull());
    file.close();
  }
  return data;
}

//Adam Krizar
void filemanager::savedevices(QVector<iot*> data)
{

  /*
  int t1[4] = {123,123,123,123};
  int t2[4] = {123,123,123,124};
  int t3[4] = {123,123,123,125};
  int t4[4] = {123,123,123,126};
  int t5[4] = {123,123,123,127};
  int t6[4] = {123,123,123,128};
  int t7[4] = {123,123,123,129};
  int t8[4] = {123,123,123,144};
  int t9[4] = {123,123,123,112};
  int t10[4] = {123,123,123,190};
  data.push_back(new iot(1, "Kuchnia", t1, 1));
  data.push_back(new iot(2, "Salon", t2, 1));
  data.push_back(new iot(3, "Garaż", t3, 1));
  data.push_back(new iot(4, "Ogród", t4, 1));
  data.push_back(new iot(5, "C3", t5, 1));
  data.push_back(new iot(6, "C4", t6, 1));
  data.push_back(new iot(7, "C16", t7, 1));
  data.push_back(new iot(8, "C13", t8, 1));
  data.push_back(new iot(9, "Kosmos", t9, 1));
  data.push_back(new iot(10, "xd", t10, 1));
*/

  //int t1[4] = {172,16,0,5};
  //data.push_back(new iot(1, "HTTP_TEST", t1, 1));


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
    QTextStream out(&file);
    for(int i=0; i<data.size(); i++) out << data[i]->toString();
    file.close();
  }
}
