#include "battlemap.h"
#include "weapon.h"

#include <QDebug>

BattleMap::BattleMap(QList<std::shared_ptr<Character>> friendlyCharacters,
                     int difficulty,
                     QVector<std::shared_ptr<Enemy>> allEnemies)
{

    mapTiles_ = initializeTiles();
    friendlyCharacters_ = friendlyCharacters;
    initializeFriendlyCharacters();

    enemyCharacters_ = initializeEnemyCharacters(difficulty, allEnemies);
}
BattleMap::~BattleMap(){}

QList<std::shared_ptr<Enemy>> BattleMap::initializeEnemyCharacters(
        int difficulty, QVector<std::shared_ptr<Enemy>> allEnemies){

    int i = 0;
    QList<std::shared_ptr<Enemy>> enemyCharacters;
    int xLocation = 1;
    int startingLocation;
    while (i < difficulty){
        startingLocation = 15*i + xLocation;
        if(15*i > 149){
            startingLocation -= 148;
        }

        std::shared_ptr<Enemy> newEnemy(new Enemy(*allEnemies.at(0)));

        enemyCharacters.append(newEnemy);
        characterLocations_[newEnemy] = startingLocation;
        qDebug() << "Asetetaan vihollinen tileen " << startingLocation;
        mapTiles_[startingLocation]->addCharacter(newEnemy);
        newEnemy = nullptr;
        i += 1;
    }

    return enemyCharacters;

}


void BattleMap::initializeFriendlyCharacters(){
    int i = 0;
    while (i < friendlyCharacters_.size()){
        int startingLocation = 15*i + 14;
        characterLocations_[friendlyCharacters_.at(i)] = startingLocation;
        mapTiles_[startingLocation]->addCharacter(friendlyCharacters_.at(i));
        i += 1;

    }

    return;

}

QList<std::shared_ptr<MapTile>> BattleMap::initializeTiles(){
    int i = 0;
    QList<std::shared_ptr<MapTile>> mapTiles;
    while ( i < 150){
        std::shared_ptr<MapTile> newTile(new MapTile);
        mapTiles.append(newTile);
        i += 1;
        newTile = nullptr;
    }
    return mapTiles;
}

bool BattleMap::moveCharacter(bool isPlayerCharacter, int index, int startTile,
                         int targetTile){

    if (index < 0 | index > 149){
        return false;
    }

    // Tässä selvitetään mikä hahmo haluaa liikkua isPlayerCharacter ja
    // indeksin(friendly tai enemy -vektoreihin) avulla.
    std::shared_ptr<Character> selectedCharacter = nullptr;
    if (isPlayerCharacter) {
        selectedCharacter = friendlyCharacters_[index];
    }
    else {
        selectedCharacter = enemyCharacters_[index];
    }
    // Tarkistetaan etäisyys ja että hahmolla on tarpeeksi
    // toimintapisteitä
    int distance = getManhattanDistance(startTile, targetTile);
    if (distance > selectedCharacter->getCurrentActionPoints()){
            return false;
    }

    // Kokeillaan siirtoa
    if ((mapTiles_.at(targetTile))->addCharacter(selectedCharacter)){

        // Poistetaan hahmo edellisestä ruudusta
        (mapTiles_.at(startTile))->removeCharacter();

        selectedCharacter->useActionPoints(distance);

        //Päivitetään hahmon sijainti.
        characterLocations_[selectedCharacter] = targetTile;
        return true;

    } else {
        return false;
    }


}

bool BattleMap::moveCharacter(std::shared_ptr<Character> selectedCharacter, int startTile,
                         int targetTile){

    if (targetTile < 0 | targetTile > 149){
        return false;
    }

    // Tarkistetaan etäisyys ja että hahmolla on tarpeeksi
    // toimintapisteitä
    int distance = getManhattanDistance(startTile, targetTile);

    if (distance > selectedCharacter->getCurrentActionPoints()){
        return false;
    }

    // Kokeillaan siirtoa
    if ((mapTiles_.at(targetTile))->addCharacter(selectedCharacter)){

        // Poistetaan hahmo edellisestä ruudusta
        (mapTiles_.at(startTile))->removeCharacter();

        selectedCharacter->useActionPoints(distance);

        characterLocations_[selectedCharacter] = targetTile;
        enemyMoved();
        qDebug()<<"What";
        updateEnemyTurnLocation(targetTile);
        return true;

    } else {

        qDebug()<<"Could not move.";
        return false;
    }


}


QList<std::shared_ptr<MapTile>>* BattleMap::getTileMap(){
    return &mapTiles_;
}

QList<std::shared_ptr<Character>>* BattleMap::listPlayerCharacters(){
    return &friendlyCharacters_;
}


QList<std::shared_ptr<Enemy>>* BattleMap::listEnemyCharacters(){
    return &enemyCharacters_;
}

int BattleMap::getCharacterTile(std::shared_ptr<Character> character){
    return characterLocations_[character];
}

bool BattleMap::performAttack(std::shared_ptr<Character> selectedCharacter,
                              int characterTile, int targetTile){
    updateEnemyTurnLocation(characterTile);

    qDebug()<<"Hyökätään hahmolla " << selectedCharacter->getName();
    qDebug() << "Hahmolla AP:ta " << selectedCharacter->getCurrentActionPoints();
    // Tarkistetaan että kohderuudussa on hahmo
    if ((mapTiles_.at(targetTile))->getCharacter() == nullptr){
        return false;
        qDebug() << "Kohdetiilessä ei ole vihollista.";
    }
    qDebug()<<"Kohde löytynyt";

    // Tarkistetaan etäisyys
    double distance = getEuclideanDistance(characterTile, targetTile);

    int maxRange = selectedCharacter->getEquippedWeapon()->getMaxRange() + \
            selectedCharacter->getEquippedImplant()->getRangeBonus();
    int minRange = selectedCharacter->getEquippedWeapon()->getMinRange();



    if (distance < minRange | distance > maxRange){
        qDebug() << "Väärä etäisyys";
        return false;
    }

    // Yritetään ampumista. Jos ei onnistu (liian vähän toimintapisteitä)
    // , palautetaan false.
    if (!selectedCharacter->shoot()){
        qDebug() << "Ampuminen epäonnistui";
        return false;
    }

    // Arvotaan aseen osuus vahingosta
    int minWeaponDamage = selectedCharacter->getEquippedWeapon()->getMinDamage();
    int maxWeaponDamage = selectedCharacter->getEquippedWeapon()->getMaxDamage();

    // Heitetään noppaa.
    int weaponDamage = this->die_->rollDie(minWeaponDamage, maxWeaponDamage);
    qDebug() << "weaponDamage:"<< weaponDamage;

    // Lisätään bonukset
    int totalDamage = weaponDamage + \
            selectedCharacter->getEquippedImplant()->getAttackBonus();

    qDebug() << "totalDamage:"<< totalDamage;

    // Haetaan kohteessa oleva hahmo
    std::shared_ptr<Character> targetCharacter = \
            (mapTiles_.at(targetTile))->getCharacter();

    // Lasketaan haarniskan puolustusbonus jos ase ei ole läpäisevä
    int armorResistance;
    Weapon::WeaponType weaponType = \
            selectedCharacter->getEquippedWeapon()->getType();
    if (weaponType != Weapon::WeaponType::ANTI_ARMOR ){
        armorResistance = targetCharacter->getEquippedArmor()->getDefence();
    }

    // Muut bonukset
    int implantResistance = targetCharacter->getEquippedImplant()->getDefenceBonus();

    // Annetaan kokonaisvahinko jos yli nollan
    int damageThrough = totalDamage - armorResistance - implantResistance;
    qDebug()<<"damage: " + QString::number(damageThrough);

    if (damageThrough <= 0){
        // Hyökkäys onnistui mutta ei antanut vahinkoa
        enemyAttacking(characterTile, targetTile);
        return true;

    } else {
        targetCharacter->receiveDamage(damageThrough);

        // Tarkistetaan kuoliko hahmo
        if (targetCharacter->isDead()){
            (mapTiles_.at(targetTile))->removeCharacter();

            characterKilled(targetCharacter, characterTile);
        }
    }
    enemyAttacking(characterTile, targetTile);
    return true;
}

int BattleMap::getManhattanDistance(int tileOne, int tileTwo){
    int xOne = (tileOne) % 15;
    int yOne = floor(tileOne / 15);

    int xTwo = tileTwo % 15;
    int yTwo = floor(tileTwo / 15);

    // Manhattan-etäisyys
    int distance = abs(xOne-xTwo) + abs(yOne-yTwo);

    return distance;

}


double BattleMap::getEuclideanDistance(int tileOne, int tileTwo){
    int xOne = (tileOne) % 15;
    int yOne = floor(tileOne / 15);

    int xTwo = tileTwo % 15;
    int yTwo = floor(tileTwo / 15);

    //Euklidinen etäisyys
    double distance = sqrt(pow(abs(xOne - xTwo), 2) + pow(abs(yOne - yTwo),2));

    return distance;


}


void BattleMap::nextTurn(){


    // Palautetaan toimintapisteet
    for(QList<std::shared_ptr<Enemy>>::iterator it = enemyCharacters_.begin();
        it != enemyCharacters_.end(); ++it) {

        (*it)->fillActionPoints();
    }


    for(QList<std::shared_ptr<Character>>::iterator it = friendlyCharacters_.begin();
        it != friendlyCharacters_.end(); ++it) {
        (*it)->fillActionPoints();

    }

    if (BattleMap::battleOver()){

        for (auto enemy: enemyCharacters_){
            enemiesKilled_ += 1;
        }

        battleFinished(enemiesKilled_);

    } else if (BattleMap::battleLost()){
        playerLost();
    }

}


void BattleMap::emitUpdateEnemyTurnLocation(int tile) {
    updateEnemyTurnLocation(tile);
}


void BattleMap::emitDelay(int seconds) {
    delaySeconds(seconds);
}


bool BattleMap::battleOver(){
    qDebug() << "Vihollisia yhteensä " << (enemyCharacters_.size());
    for(QList<std::shared_ptr<Enemy>>::iterator it = enemyCharacters_.begin();
        it != enemyCharacters_.end(); ++it) {
        if (!(*it)->isDead()){
            return false;
        }
    }

    return true;
}

bool BattleMap::battleLost(){
    for(QList<std::shared_ptr<Character>>::iterator it = friendlyCharacters_.begin();
        it != friendlyCharacters_.end(); ++it) {
        if (!(*it)->isDead()){
            return false;
        }
    }
    qDebug() << "BattleMap kertoo että peli on hävitty";

    return true;
}
