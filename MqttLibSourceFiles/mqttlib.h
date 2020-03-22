#ifndef MQTTLIB_H
#define MQTTLIB_H

#include "MqttLib_global.h"

class MQTTLIB_EXPORT MqttLib
{
public:
    MqttLib();
    void updateLogStateChange();
    void setClientPort(int p);
    bool on_buttonPublish_clicked(QMqttTopicName &name, QByteArray &message);
    QMqttSubscription* on_buttonSubscribe_clicked(QMqttTopicFilter &filter);
    QMqttClient *m_client;
    void ToggleConnection();
};

#endif // MQTTLIB_H
