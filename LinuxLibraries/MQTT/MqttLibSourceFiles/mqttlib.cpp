#include "mqttlib.h"

MqttLib::MqttLib()
{
    //m_client = new QMqttClient();
}

void MqttLib::Connect(QMqttClient *m_client)
{
    if (m_client->state() == QMqttClient::Disconnected) {
        m_client->connectToHost();
    }
}

QString MqttLib::GetHost(QMqttClient *m_client)
{
    return m_client->hostname();
}

void MqttLib::Disconnect(QMqttClient *m_client)
{
    if(m_client->state() == QMqttClient::Connected)
        m_client->disconnectFromHost();
}

void MqttLib::UpdateLogStateChange(QMqttClient *m_client)
{
    const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(": State Change")
                    + QString::number(m_client->state())
                    + QLatin1Char('\n');
}

void MqttLib::SetClientPort(QMqttClient *m_client, int p)
{
    m_client->setPort(p);
}

//bool MqttLib::Publish(QMqttClient *m_client, QMqttTopicName &name, QByteArray &message)
//{
//    if (m_client->publish(name, message) == -1)
//        return false;
//    return true;
//}

QMqttSubscription* MqttLib::Subscribe(QMqttClient *m_client, QString &topic)
{
    //QString topic = "broker/humidity";
    //QString topic2 = "broker/tempereture";
    auto subscription = m_client->subscribe(topic);
    //auto subscription2 = m_client->subscribe(topic2);
    if (!subscription) {
        //QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
        return nullptr;
    }
    return subscription;
}
