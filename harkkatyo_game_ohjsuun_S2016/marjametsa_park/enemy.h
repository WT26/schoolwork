#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

// Vihollishahmoluokka. BattleMapissä yrittää hyökätä PlayerCharacterien kimppuun.
class Enemy : public Character
{
public:
    Enemy(QString name, int maxHp, int currentHp, int actionPoints,
          int currentActionPoints, std::shared_ptr<Weapon> equippedWeapon,
          std::shared_ptr<Armor> equippedArmor, std::shared_ptr<Implant> equippedImplant);

    Enemy(const Enemy &enemyObject);

    ~Enemy();

};

#endif // ENEMY_H

