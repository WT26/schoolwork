#ifndef VIEWINTERFACE_H
#define VIEWINTERFACE_H

#include "gameprogress.h"

#include <vector>

class ViewInterface
{

public:
    enum ActiveView { MAIN_MENU, WORLD_MAP, RESEARCH_CENTER, HEADQUARTERS, BATTLE_MAP, INVENTORY};
    //
    // Tyhjä purkaja
    virtual ~ViewInterface(){}

    // Vaihda näkymää
    virtual bool switchView(ActiveView requestedView, GameProgress progress, QList<std::shared_ptr<ParkingHall>> parkinghalls) = 0;

    // Tulosta viesti viestilaatikkoon
    virtual bool logMessage() = 0;

    // Sulje pelin ikkuna
    virtual void closeAll()= 0;

    // Asettaa characterit taisteluareenalle.
    virtual void initializeCharactersToMap(QList<int> playableCharactersLocations,
                                           QList<int> enemyCharactersLocations,
                                           QList<int>enemyCharactersHealth) = 0;

    // Tarkistaa onko liikkuminen sallittu.
    virtual void isMovePermitted(bool permission) = 0;

    // Tarkistaa onko hyökkääminen sallittu.
    virtual void isAttackPermitted(bool permission) = 0;

    // Päivittää Characterien sijainnit kartalla.
    virtual void updateCharactersLocations(QList<int> playableCharactersLocations, QList<int> enemyCharactersLocations) = 0;

    // Päivittää vastustajien vuorot.
    virtual void updateEnemyTurnLocation(int tile) = 0;

    // Päivittää vastustajan tekemät vahingot näkymälle.
    virtual void characterAttacking(QList<int> playableCharactersHealths,
                                    QList<int> playableCharactersMaxHealths,
                                    QList<int> playableCharactersAps,
                                    QList<int> enemyCharactersAps,
                                    QList<int> enemyCharactersHealths,
                                    int attackingTile, int attackedTile) = 0;

    // Vaihtaa seuraavan vuoron.
    virtual void nextTurn() = 0;

    // Taistelu loppui, päivitetään voittoraha ja vallattu
    // parkkihalli.
    virtual void battleOver(QString hallName, int prizeMoney) = 0;

    // Näytetään näkymässä pelin häviöviesti.
    virtual void gameOver(QString reason) = 0;

    // Näytetään näkymässä pelin voittoviesti.
    virtual void gameWon(QString message) = 0;

    // Palauttaa vuoron pelaajalle.
    virtual void enemyTurnOver() = 0;

    virtual void updateResearchCenterPropertys(GameProgress progress) = 0;
    virtual void updateInventoryPropertys(GameProgress progress) = 0;


};

#endif // VIEWINTERFACE_H
