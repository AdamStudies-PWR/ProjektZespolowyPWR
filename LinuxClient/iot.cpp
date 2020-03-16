#include "iot.h"

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

int iot::getDevice_id() {return device_id;}
QString iot::getDevice_name() {return device_name;}
int iot::getProtocol() {return protocol;}
int *iot::getDevice_ip() {return device_ip;}
