#ifndef MQTT_GLOBAL_H
#define MQTT_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QtMqtt/QMqttClient>

#if defined(MQTT_LIBRARY)
#  define MQTT_EXPORT Q_DECL_EXPORT
#else
#  define MQTT_EXPORT Q_DECL_IMPORT
#endif

#endif // MQTT_GLOBAL_H
