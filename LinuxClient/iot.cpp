#include "iot.h"

//Adam Krizar
iot::iot(int id, QString name, int ip[4], int protocol)
{
  this->device_id = id;
  this->device_name = name;
  this->device_ip[0] = ip[0];
  this->device_ip[1] = ip[1];
  this->device_ip[2] = ip[2];
  this->device_ip[3] = ip[3];
  this->protocol = protocol;

  active = false;
}

//Adam Krizar
QString iot::toString()
{
  return (QString::number(device_id) + "/" + device_name + "/" + QString::number(protocol) + "/" + QString::number(device_ip[0]) + "." + QString::number(device_ip[1]) + "." + QString::number(device_ip[2]) + "." + QString::number(device_ip[3]) + "\n");
}

//Adam Krizar
QString iot::getName() {return device_name;}

//Adam Krizar
QString iot::getIP()
{
  return (QString::number(device_ip[0]) + "." + QString::number(device_ip[1]) + "." + QString::number(device_ip[2]) + "." + QString::number(device_ip[3]));
}

//Adam Krizar
int iot::getProtocol() {return protocol;}
