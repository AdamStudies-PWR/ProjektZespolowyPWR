#include "mqtt.h"

Mqtt::Mqtt()
{
    m_client = new QMqttClient();
}

void Mqtt::ToggleConnection()
{
    if (m_client->state() == QMqttClient::Disconnected) {
        m_client->connectToHost();
    } else {
        m_client->disconnectFromHost();
    }
}

void Mqtt::UpdateLogStateChange()
{
    const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(": State Change")
                    + QString::number(m_client->state())
                    + QLatin1Char('\n');
}

void Mqtt::SetClientPort(int p)
{
    m_client->setPort(p);
}

bool Mqtt::Publish(QMqttTopicName &name, QByteArray &message)
{
    if (m_client->publish(name, message) == -1)
        return false;
    return true;
}

QMqttSubscription* Mqtt::Subscribe(QMqttTopicFilter &filter)
{
    auto subscription = m_client->subscribe(filter);
    if (!subscription)
        return nullptr;
    return subscription;
}
