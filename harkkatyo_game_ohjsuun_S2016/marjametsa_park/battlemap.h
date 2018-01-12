#ifndef BATTLEMAP_H
#define BATTLEMAP_H

#include "character.h"
#include "enemy.h"
#include "maptile.h"

#include "die.h"

#include <vector>

class BattleMap: public QObject
{
Q_OBJECT
public:
    BattleMap(QList<std::shared_ptr<Character>> friendlyCharacters,
              int difficulty, QVector<std::shared_ptr<Enemy>> allEnemies);
    ~BattleMap();

    QList<std::shared_ptr<Enemy>> initializeEnemyCharacters(
            int difficulty, QVector<std::shared_ptr<Enemy>> allEnemies);
    void initializeFriendlyCharacters();
    QList<std::shared_ptr<MapTile>> initializeTiles();

    static int getManhattanDistance(int tileOne, int tileTwo);
    static double getEuclideanDistance(int tileOne, int tileTwo);

    QList<std::shared_ptr<MapTile>>* getTileMap();
    QList<std::shared_ptr<Character>>* listPlayerCharacters();
    QList<std::shared_ptr<Enemy>>* listEnemyCharacters();

    int getCharacterTile(std::shared_ptr<Character> character);


    // Liikkumiselle on määritelty kaksi funktiota. Toista kutsutaan
    // kun liikkuminen tapahtuu käyttöliittymän kautta. Toista kutsutaan
    // kun liikuttajana on tekoäly.
    bool moveCharacter(std::shared_ptr<Character> selectedCharacter,
                       int startTile, int targetTile);
    bool moveCharacter(bool isPlayerCharacter, int index,
                       int startTile, int targetTile);


    bool performAttack(std::shared_ptr<Character> selectedCharacter,
                       int characterTile, int targetTile);

    void escapeBattle();
    void nextTurn();
    void emitUpdateEnemyTurnLocation(int tile);
    void emitDelay(int seconds);

    // Tarkistaa onko kaikki viholliset tapettu
    bool battleOver();
    bool battleLost();


signals:
    void enemyMoved();
    void characterKilled(std::shared_ptr<Character> killedCharacter,
                         int characterTile);
    void enemyAttacking(int attackingTile, int attackedTile);
    void enemyTurnOver();

    void delaySeconds(int seconds);

    void updateEnemyTurnLocation(int tile);
    void battleFinished(int enemiesKilled);
    void playerLost();

public slots:

private:
    QList<std::shared_ptr<MapTile>> mapTiles_;
    QList<std::shared_ptr<Character>> friendlyCharacters_;
    QList<std::shared_ptr<Enemy>> enemyCharacters_;

    std::map<std::shared_ptr<Character>, int> characterLocations_;

    Die* die_;

    int enemiesLeft_;
    int enemiesKilled_;

};

#endif // BATTLEMAP_H
