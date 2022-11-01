#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
#include "manager.h"

using namespace manager;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQuickView view;
    Manager& manager = Manager::getInstance();
    view.setSource(QUrl::fromLocalFile("qt6sens/main.qml"));
    view.setFlags(Qt::FramelessWindowHint);
    QObject *item = reinterpret_cast<QObject *>(view.rootObject());

    QObject::connect(item, SIGNAL(enableI2CSens(bool)), &manager, SLOT(enableI2CSens(bool)));
    QObject::connect(item, SIGNAL(enableMMSens(bool,QString)), &manager, SLOT(enableMMSens(bool,QString)));
    QObject::connect(item, SIGNAL(setSamplingSpeed(QString)), &manager, SLOT(setSamplingSpeed(QString)));

    QObject::connect(&manager, SIGNAL(newMMSensValue(QString)), item, SLOT(newMMSensValue(QString)));
    QObject::connect(&manager, SIGNAL(newI2CSensValue(int)), item, SLOT(newI2CSensValue(int)));

    view.show();
    return app.exec();
}
