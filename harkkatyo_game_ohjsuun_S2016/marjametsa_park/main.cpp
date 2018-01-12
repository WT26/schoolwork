#include "motor.h"
#include "controller.h"
#include "view.h"

#include <memory>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

 int main(int argc, char *argv[])
 {
     QGuiApplication app(argc, argv);

     // Luodaan instanssit pääluokista
     std::unique_ptr<Motor> motor(new Motor);
     std::unique_ptr<Controller> controller(new Controller);
     std::unique_ptr<View> view(new View);

     // Välitetään instanssit private-puolelle
     motor->setView(view.get());
     controller->setMotor(motor.get());
     view->setController(controller.get());

     // Luodaan ApplicationEngine ja annetaan näkymäluokalle
     QQmlApplicationEngine* engine = new QQmlApplicationEngine;
     view->setEngine(engine);

     // Peli käyntiin
     motor->initializeGame();

     return app.exec();
 }
