#ifndef IOT_H
#define IOT_H

#include <QString>

using namespace std;

class iot
{
  int device_id;
  QString device_name;
  int device_ip[4];
  bool active;
  int protocol;
public:
  iot(int id, QString name, int ip[4], int protocol);
  int getDevice_id();
  QString getDevice_name();
  int getProtocol();
  int *getDevice_ip();
};

#endif // IOT_H
