#ifndef IOT_H
#define IOT_H

#include <QString>
#include "mqtt.h"

using namespace std;

//Adam Krizar
class iot
{
    int device_id;
    QString device_name;
    int device_ip[4];
    bool active;
    int protocol;
public:
    iot(int id, QString name, int ip[4], int protocol);
    QString toString();

    QString getName();
    int getProtocol();
    QString getIP();
    QMqttClient* m_client;
};

#endif // IOT_H
