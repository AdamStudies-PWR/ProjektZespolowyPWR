#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "filemanager.h"
#include "interface.h"

int main(int argc, char *argv[])
{
    filemanager manager;
    //manager.loaddevices();
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    //Jak przekazywać syganły z interfejsu do qml
    //engine.rootContext()->setContextProperty("interface", &interface);
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
