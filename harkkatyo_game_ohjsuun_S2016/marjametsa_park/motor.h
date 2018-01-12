#ifndef MOTOR_H
#define MOTOR_H

#include "motorinterface.h"
#include "viewinterface.h"
#include "weapon.h"
#include "armor.h"
#include "implant.h"
#include "enemy.h"
#include "playablecharacter.h"
#include "tampereparkinginterface.hh"
#include "tampereparking.hh"
#include "gameprogress.h"
#include "parkinghall.hh"
#include "battlemap.h"
#include "battleai.h"

#include <vector>
#include <QObject>
#include <QStringList>
#include <QVector>
#include <QString>
#include <QTimer>


class Motor :  public QObject, public MotorInterface
{
    Q_OBJECT
    enum ActiveView { MAIN_MENU, WORLD_MAP, RESEARCH_CENTER, HEADQUARTERS, BATTLE_MAP, INVENTORY};

public:
    Motor();
    ~Motor();

    // Funktio näkymäpointerin asettamiseksi
    void setView(ViewInterface* viewInstance);

    // Käynnistää pelin
    void initializeGame();

    // Alustaa taistelunäkymän
    void initializeBattleMap(int parkingHallIndex);

    // Päävalikon ja kartan toimintoihin liittyvät slotit
    // Aloita uusi peli
    void newGame();

    // Sulje peli
    void quitGame();

    // Vaihda näkymää
    void switchView(MotorInterface::ActiveView nextView);

    // Lataa talletus
    void loadGame();

    void saveAndExit();

    // Taisteluruudun metodit
    // Valitse aktiivinen hahmo
    void selectCharacter();

    // Yritä hyökkäystä kohteeseen
    void attackTarget();

    // Vaihda aktiivista esinettä
    void changeItem();

    // Yritä liikkua kohteeseen
    void moveTo(bool isPlayerCharacter, int index, int startTile, int targetTile);

    // Yritä hyökätä kohteeseen
    void attackTo(bool isPlayerCharacter, int index, int startTile, int targetTile);

    // Lopeta vuoro
    void endTurn();    

    void healTeam(int cost);
    void healCharacter(int index, int cost);
    // Uusi item tutkittu.
    void itemResearched(QString name, int cost);

    // Uusi item tutkittu.
    void itemEquipped(int characterIndex, QString itemName);

    void checkGameStatus();

    //
    bool checkWinningCondition();

    void battleOver(QString hallName, int prizeMoney);

    void gameOver(QString reason);

    void gameWon(QString message);

signals:
    void quitApplication();


public slots:
    void updateHallsRequested();
    void battleFinished(int battleScore);
    void enemyMoved();
    void enemyAttacking(int attackingTile, int attackedTile);
    void enemyTurnOver();
    void updateEnemyTurnLocation(int tile);
    void delaySeconds(int seconds);
    void playerLost();

private:
    ViewInterface* viewInstance;

    Parking::TampereParking* datex2Api_;

    BattleMap* battleMap_;
    GameProgress progress_;

    QTimer* updateHallDataTimer_;
    BattleAI* battleAi_;

    int saveSlot_;

    int activeHall_=-1;
    int totalHalls_;

    bool gameLost_;
    bool gameWon_;

    void delay();
};


#endif // MOTOR_H
