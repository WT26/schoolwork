#ifndef VIEW_H
#define VIEW_H

#include "viewinterface.h"
#include "controller.h"
#include "gameprogress.h"

#include <map>
#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QQmlComponent>
#include <QQuickItem>

// Näkymä luokka. Luokka ainoastaan toimii näkymien vaihtamisessa käyttäen QML tiedostoja.
class View : public ViewInterface, public QObject
{

public:
    View();
    ~View();

    // Aseta controlleri
    void setController(Controller* controllerInstance);

    // Aseta QMLApplicationEngine
    void setEngine(QQmlApplicationEngine *engineInstance);

    // Vaihdea näkymää
    bool switchView(View::ActiveView requestedView, GameProgress progress, QList<std::shared_ptr<ParkingHall>> parkinghalls);

    //bool drawParkingHalls(std::vector<pair<int,int>> coordinates);

    // Tulosta viesti viestilaatikkoon
    bool logMessage();

    // Sulje pelin ikkuna
    void closeAll();

    // Asettaa characterit taisteluareenalle.
    void initializeCharactersToMap(QList<int> playableCharactersLocations,
                                   QList<int> enemyCharactersLocations,
                                   QList<int>enemyCharactersHealth);
    // Tarkistaa onko liikkuminen sallittu.
    void isMovePermitted(bool permission);

    // Tarkistaa onko hyökkääminen sallittu.
    void isAttackPermitted(bool permission);
    // Päivittää Characterien sijainnit kartalla.
    void updateCharactersLocations(QList<int> playableCharactersLocations,
                                   QList<int> enemyCharactersLocations);
    // Päivittää vastustajien vuorot.
    void updateEnemyTurnLocation(int tile);

    // Päivittää vastustajan tekemät vahingot näkymälle.
    void characterAttacking(QList<int> playableCharactersHealths,
                            QList<int> playableCharactersMaxHealths,
                                        QList<int> playableCharactersAps,
                                        QList<int> enemyCharactersAps,
                                        QList<int> enemyCharactersHealths,
                                        int attackingTile, int attackedTile);

    // Vaihtaa seuraavan vuoron.
    void nextTurn();

    // Palauttaa vuoron pelaajalle.
    void enemyTurnOver();

    // Taistelu loppui, päivitetään voittoraha ja vallattu
    // parkkihalli.
    void battleOver(QString hallName, int prizeMoney);

    // Näytetään näkymässä pelin häviöviesti.
    void gameOver(QString reason);

    // Näytetään näkymässä pelin voittoviesti.
    void gameWon(QString message);

    // Päivitetään tutkimuskeskuksen tiedot.
    void updateResearchCenterPropertys(GameProgress progress);

    // Päivitetään inventoryn tiedot.
    void updateInventoryPropertys(GameProgress progress);
private:
    Controller* controller_;
    QQmlApplicationEngine* engine_;
    std::map<View::ActiveView, QQuickItem*> views_;
    View::ActiveView currentView_;

    // Metodit joilla alustetaan propertyt näkymiin.
    void setUpWorldMap(QObject* requestedWindow, GameProgress progress, QList<std::shared_ptr<ParkingHall>> parkinghalls);
    void setUpHeadquarters(QObject* requestedWindow, GameProgress* progress, QList<std::shared_ptr<ParkingHall>> parkinghalls);
    void setUpResearchCenter(QObject* requestedWindow, GameProgress progress, QList<std::shared_ptr<ParkingHall>> parkinghalls);
    void setUpBattleMap(QObject* requestedWindow, GameProgress progress,
                        QList<std::shared_ptr<ParkingHall>> parkinghalls);
    void setUpInventory(QObject* requestedWindow, GameProgress progress, QList<std::shared_ptr<ParkingHall>> parkinghalls);

};

#endif // VIEW_H
