#include "mqttlib.h"

MqttLib::MqttLib()
{
    m_client = new QMqttClient();
}

void MqttLib::ToggleConnection()
{
    if (m_client->state() == QMqttClient::Disconnected) {
        m_client->connectToHost();
    } else {
        m_client->disconnectFromHost();
    }
}

void MqttLib::UpdateLogStateChange()
{
    const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(": State Change")
                    + QString::number(m_client->state())
                    + QLatin1Char('\n');
}

void MqttLib::SetClientPort(int p)
{
    m_client->setPort(p);
}

bool MqttLib::Publish(QMqttTopicName &name, QByteArray &message)
{
    if (m_client->publish(name, message) == -1)
        return false;
    return true;
}

QMqttSubscription* MqttLib::Subscribe(QMqttTopicFilter &filter)
{
    auto subscription = m_client->subscribe(filter);
    if (!subscription)
        return nullptr;
    return subscription;
}
