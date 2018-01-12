// Pelimoottorin rajapinta, jota Controller-luokka käyttää.

#ifndef MOTORINTERFACE_H
#define MOTORINTERFACE_H


#include <QString>

class MotorInterface
{
    public :
        enum ActiveView { MAIN_MENU, WORLD_MAP, RESEARCH_CENTER,
                          HEADQUARTERS, BATTLE_MAP, INVENTORY};

        // Tyhjä purkaja
        virtual ~MotorInterface(){}
        // Päävalikon ja kartan toimintoihin liittyvät slotit

        virtual void initializeGame() = 0;
        virtual void initializeBattleMap(int parkingHallIndex) = 0;

        // Aloita uusi peli
        virtual void newGame() = 0;

        // Lopeta peli
        virtual void quitGame() = 0;
        // Vaihda näkymää
        virtual void switchView(ActiveView nextView) = 0;

        // Lataa talletus
        virtual void loadGame() = 0;

        // Lataa talletus
        virtual void saveAndExit() = 0;


        // Taisteluruudun metodit
        // Valitse aktiivinen hahmo
        virtual void selectCharacter() = 0;

        // Yritä hyökkäystä kohteeseen
        virtual void attackTarget() = 0;

        // Vaihda aktiivista esinettä
        virtual void changeItem() = 0;

        // Yritä liikkua kohteeseen
        virtual void moveTo(bool isPlayerCharacter, int index, int startTile, int targetTile) = 0;

        // Yritä hyökätä kohteeseen
        virtual void attackTo(bool isPlayerCharacter, int index, int startTile, int targetTile) = 0;

        // Lopeta vuoro
        virtual void endTurn() = 0;

        virtual void healTeam(int cost) = 0;
        virtual void healCharacter(int index, int cost) = 0;

        // Uusi item tutkittu.
        virtual void itemResearched(QString name, int cost) = 0;

        // Uusi item tutkittu.
        virtual void itemEquipped(int characterIndex, QString itemName) = 0;

        virtual void checkGameStatus() = 0;


};

#endif // MOTORINTERFACE_H
