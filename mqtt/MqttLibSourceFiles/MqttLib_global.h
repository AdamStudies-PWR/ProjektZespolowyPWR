#ifndef MQTTLIB_GLOBAL_H
#define MQTTLIB_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QtMqtt/QMqttClient>

#if defined(MQTTLIB_LIBRARY)
#  define MQTTLIB_EXPORT Q_DECL_EXPORT
#else
#  define MQTTLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // MQTTLIB_GLOBAL_H
