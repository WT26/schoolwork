#include "battleai.h"

#include <QDebug>

BattleAI::BattleAI()
{

}

BattleAI::~BattleAI(){}

void BattleAI::setBattleMap(BattleMap* battleMap){
    map_ = battleMap;
}

void BattleAI::performTurn(){
    auto aiCharacters =  map_->listEnemyCharacters();

    // Käydään läpi jokainen tekoälyn hahmo ja mietitään liikkeet
    for (QList<std::shared_ptr<Enemy>>::iterator it = (*aiCharacters).begin(); \
            it != (*aiCharacters).end(); ++it) {
        if (!(*it)->isDead()){
            qDebug() << "AI-hahmon vuoro.";
            int startTile = map_->getCharacterTile(*it);
            map_->emitUpdateEnemyTurnLocation(startTile);
            map_->emitDelay(1);
            decideCharacterMove((*it), startTile);

        }
    }

    map_->enemyTurnOver();
}


void BattleAI::decideCharacterMove(std::shared_ptr<Character> aiCharacter,
                                   int startTile){

    int maxShootingRange = aiCharacter->getEquippedWeapon()->getMaxRange();
    int minShootingRange = aiCharacter->getEquippedWeapon()->getMinRange();
    int characterTile;

    // Etsitään lähin hahmo
    std::shared_ptr<Character> closestCharacter = nullptr;
    double closestDistance = 100000;
    int closestCharacterTile;
    auto playerCharacters = map_->listPlayerCharacters();


    for (QList<std::shared_ptr<Character>>::iterator it = (*playerCharacters).begin();\
            it != (*playerCharacters).end(); ++it) {

        // Jos hahmo on elossa, katsotaan onko se lähimpänä ja laitetaan tiedot talteen
        if(!(*it)->isDead()){
            characterTile = map_->getCharacterTile((*it));

            double distance = \
                    BattleMap::getEuclideanDistance(startTile, characterTile);

            if (distance < closestDistance){
                closestDistance = distance;
                closestCharacter = *it;
                closestCharacterTile = characterTile;
            }

        }

    }

    characterTile = closestCharacterTile;

    // Jos hahmo löytyy, hyökätään ja/tai liikutaan
    if(!(closestCharacter == nullptr)){
        if(map_->performAttack(aiCharacter, startTile, characterTile)){
            // Hyökkäys onnistui
            return;

        } else if (aiCharacter->getCurrentActionPoints() > 0){
            qDebug() << "Hamolla on AP:ta";
            int totalDistance = \
                    BattleMap::getManhattanDistance(startTile, characterTile);
            // Liikutaan aseen kantaman päähän jos ollaan liian kaukana
            if (totalDistance > maxShootingRange){

                // Liian kaukana ampumiseen. Liikutaan lähemmäs
                // Selvitellään etäisyyksiä
                int xCharacter = characterTile % 15;
                int xAiCharacter = startTile % 15;

                int yCharacter = floor(characterTile / 15);
                int yAiCharacter = floor(startTile / 15);

                bool previousBlocked = false;
                bool yBlocked = false;
                bool xBlocked = false;

                BattleMap::getEuclideanDistance(startTile,
                                                characterTile);

                QList<int> visitedTiles ;

                // Liikutaan kunnes ollaan tarpeeksi lähellä tai liikkuminen ei onnistu
                // enää.
                while(totalDistance > maxShootingRange & \
                      aiCharacter->getCurrentActionPoints() > 0 & \
                      (previousBlocked != (visitedTiles.indexOf(startTile) == -1))){
                    previousBlocked = xBlocked & yBlocked;

                    visitedTiles.append(startTile);

                    int xDistance = xCharacter - xAiCharacter;
                    int yDistance = yCharacter - yAiCharacter;

                    // Katsotaan mihin suuntaan olisi tarkoitus liikkua
                    int yDirection;
                    if (yDistance == 0){
                        yDirection = 1;
                    } else {
                        yDirection = yDistance/abs(yDistance);
                    }

                    int xDirection;
                    if (xDistance == 0){
                        xDirection = 1;
                    } else {
                        xDirection = xDistance/abs(xDistance);
                    }

                    // Yritetään liikkua oikeaan suuntaan ja liikutaan seuraavalla kierroksella muualle
                    // jos oikeaan suuntaan liikkuminen ei onnistu.
                    if ((yDistance != 0 & !yBlocked) | (xBlocked & !yBlocked)){
                        if (map_->moveCharacter(aiCharacter, startTile,
                                                startTile + yDirection*15)){
                            startTile = startTile + yDirection*15;
                            yAiCharacter = yAiCharacter + yDirection*1;
                            xBlocked = false;
                            yBlocked = false;
                            previousBlocked = false;
                            totalDistance = \
                                    BattleMap::getEuclideanDistance(startTile,
                                                                    characterTile);
                            continue;
                        } else {
                            yBlocked = true;
                        }
                    }

                    if ((yBlocked & xBlocked))  {
                        if (map_->moveCharacter(aiCharacter, startTile,
                                                startTile - yDirection*15)){
                            startTile = startTile - yDirection*15;
                            yAiCharacter = yAiCharacter - yDirection*1;
                            xBlocked = false;
                            yBlocked = false;
                            previousBlocked = false;
                            totalDistance = \
                                    BattleMap::getEuclideanDistance(startTile,
                                                                    characterTile);
                            continue;
                        }

                    }

                   if ((xDistance != 0 & !xBlocked) | (yBlocked & !xBlocked)){
                        if (map_->moveCharacter(aiCharacter, startTile,
                                                startTile + xDirection*1)){
                            startTile = startTile + xDirection*1;
                            xAiCharacter = xAiCharacter + xDirection*1;
                            xBlocked = false;
                            yBlocked = false;
                            previousBlocked = false;
                            totalDistance = \
                                    BattleMap::getEuclideanDistance(startTile,
                                                                    characterTile);
                            continue;

                        } else {
                            xBlocked = true;
                        }
                    }

                    if (yBlocked & xBlocked) {
                        if (map_->moveCharacter(aiCharacter, startTile,
                                                startTile - xDirection*1)){
                            startTile = startTile - xDirection*1;
                            xAiCharacter = xAiCharacter - xDirection*1;
                            yBlocked = false;
                            xBlocked = false;
                            previousBlocked = false;
                            totalDistance = \
                                    BattleMap::getEuclideanDistance(startTile,
                                                                    characterTile);
                            continue;
                        }
                    }

                }

                // Käytetään loput pisteet hyökkäykseen
                while(map_->performAttack(aiCharacter, startTile, characterTile)){
                }

            }
        }
    }
}

