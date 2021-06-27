#ifndef MQTT_H
#define MQTT_H

#include "mqtt_global.h"

class MQTT_EXPORT Mqtt
{
public:
    Mqtt();
    void UpdateLogStateChange();
    void SetClientPort(int p);
    bool Publish(QMqttTopicName &name, QByteArray &message);
    QMqttSubscription* Subscribe(QMqttTopicFilter &filter);
    QMqttClient *m_client;
    void ToggleConnection();
};

#endif // MQTT_H
