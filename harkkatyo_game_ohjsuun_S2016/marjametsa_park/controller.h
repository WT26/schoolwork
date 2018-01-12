#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "motorinterface.h"

#include <QObject>

class Controller: public QObject
{
    Q_OBJECT


public:
    Controller();
    ~Controller();
    void setMotor(MotorInterface* motor);


public slots:
    void exitRequested(bool exit);
    void newGameRequested(bool start);
    void mainMenuRequested(bool status);
    void worldMapRequested(bool status);
    void researchCenterRequested(bool status);
    void headquartersRequested(bool status);
    void battleMapRequested(bool status, int parkinghall_index);
    void inventoryRequested(bool status);
    void checkGameStatusRequested();

    void saveAndExitRequested();

    void itemResearched(QString itemName, int cost);
    void itemEquipped(int characterIndex, QString itemName);

    void healTeam(int cost);
    void healCharacter(int index, int cost);

    void moveToTileRequested(bool isPlayerCharacter, int index, int startTile, int targetTile);
    void attackToTileRequested(bool isPlayerCharacter, int index, int startTile, int targetTile);
    void endTurnRequested(bool status);

private:
    MotorInterface* motor_;

};

#endif // CONTROLLER_H
