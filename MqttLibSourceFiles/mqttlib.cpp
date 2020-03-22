#include "mqttlib.h"

MqttLib::MqttLib()
{     
}

void MqttLib::ToggleConnection()
{
    if (m_client->state() == QMqttClient::Disconnected) {
        m_client->connectToHost();
    } else {
        m_client->disconnectFromHost();
    }
}

void MqttLib::updateLogStateChange()
{
    const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(": State Change")
                    + QString::number(m_client->state())
                    + QLatin1Char('\n');
}

void MqttLib::setClientPort(int p)
{
    m_client->setPort(p);
}

bool MqttLib::on_buttonPublish_clicked(QMqttTopicName &name, QByteArray &message)
{
    if (m_client->publish(name, message) == -1)
        return false;
    return true;
}

QMqttSubscription* MqttLib::on_buttonSubscribe_clicked(QMqttTopicFilter &filter)
{
    auto subscription = m_client->subscribe(filter);
    if (!subscription)
        return nullptr;
    return subscription;
}
