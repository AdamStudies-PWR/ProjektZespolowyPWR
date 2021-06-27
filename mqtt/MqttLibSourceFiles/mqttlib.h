#ifndef MQTTLIB_H
#define MQTTLIB_H

#include "MqttLib_global.h"

class MQTTLIB_EXPORT MqttLib
{
public:
    MqttLib();
    void UpdateLogStateChange();
    void SetClientPort(int p);
    bool Publish(QMqttTopicName &name, QByteArray &message);
    QMqttSubscription* Subscribe(QMqttTopicFilter &filter);
    QMqttClient *m_client;
    void ToggleConnection();
};

#endif // MQTTLIB_H
