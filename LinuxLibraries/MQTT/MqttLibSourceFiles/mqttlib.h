#ifndef MQTTLIB_H
#define MQTTLIB_H

#include "MqttLib_global.h"

class MQTTLIB_EXPORT MqttLib
{
public:
    MqttLib();
    void UpdateLogStateChange(QMqttClient *m_client);
    void SetClientPort(QMqttClient *m_client, int p);
    //bool Publish(QMqttClient *m_client, QMqttTopicName &name, QByteArray &message);
    QMqttSubscription* Subscribe(QMqttClient *m_client, QString &topic);
    //QMqttClient *m_client;
    void Connect(QMqttClient *m_client);
    void Disconnect(QMqttClient *m_client);
    QString GetHost(QMqttClient* m_client);
};

#endif // MQTTLIB_H
