#include "controller.h"

#include <QDebug>

Controller::Controller()
{
}

Controller::~Controller() {}

void Controller::setMotor(MotorInterface* motorInstance)
{
    motor_=motorInstance;
}

void Controller::exitRequested(bool exit) {
    qDebug() << "Controller exitRequested";
    motor_->quitGame();
}

void Controller::newGameRequested(bool start) {
    qDebug() << "Aloitetaan uusi peli";
    motor_->newGame();
    return;
}

void Controller::mainMenuRequested(bool status) {
    qDebug() << "Siittytään takaisin päävalikkoon";
    motor_->switchView(MotorInterface::ActiveView::MAIN_MENU);
}

void Controller::worldMapRequested(bool status) {
    qDebug() << "Siittytään takaisin päävalikkoon";
    motor_->switchView(MotorInterface::ActiveView::WORLD_MAP);
}

void Controller::researchCenterRequested(bool status) {
    qDebug() << "Siittytään tutkimuskeskukseen";
    motor_->switchView(MotorInterface::ActiveView::RESEARCH_CENTER);
}

void Controller::headquartersRequested(bool status) {
    qDebug() << "Siittytään Tukikohtaan";
    motor_->switchView(MotorInterface::ActiveView::HEADQUARTERS);

}

void Controller::battleMapRequested(bool status, int parkinghallIndex) {
    // Alustetaan taistelukartta.
    motor_->initializeBattleMap(parkinghallIndex);
    qDebug() << "Siittytään taistelumappiin";
    motor_->switchView(MotorInterface::ActiveView::BATTLE_MAP);
}

void Controller::inventoryRequested(bool status) {
    qDebug() << "Siirrytään inventoryyn";
    motor_->switchView(MotorInterface::ActiveView::INVENTORY);
}

void Controller::checkGameStatusRequested() {
    motor_->checkGameStatus();
}

void Controller::saveAndExitRequested() {
    motor_->saveAndExit();
}

void Controller::itemResearched(QString itemName, int cost) {
    qDebug()<< "Item " +  itemName + " Researched!\nCost: " + QString::number(cost);
    motor_->itemResearched(itemName, cost);
}

void Controller::itemEquipped(int characterIndex, QString itemName) {
    motor_->itemEquipped(characterIndex, itemName);
}

void Controller::healTeam(int cost) {
    motor_->healTeam(cost);
}

void Controller::healCharacter(int index, int cost) {
    motor_->healCharacter(index, cost);
}

void Controller::moveToTileRequested(bool isPlayerCharacter, int index, int startTile, int targetTile) {
    motor_->moveTo(isPlayerCharacter, index, startTile, targetTile);
}

void Controller::attackToTileRequested(bool isPlayerCharacter, int index, int startTile, int targetTile) {
    motor_->attackTo(isPlayerCharacter, index, startTile, targetTile);
}

void Controller::endTurnRequested(bool status) {
    qDebug()<<"End Turn Requested";
    motor_->endTurn();
}
