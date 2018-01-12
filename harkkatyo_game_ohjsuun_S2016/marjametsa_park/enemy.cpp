#include "enemy.h"

Enemy::Enemy(QString name, int maxHp, int currentHp, int maxActionPoints,
             int currentActionPoints, std::shared_ptr<Weapon> equippedWeapon,
             std::shared_ptr<Armor> equippedArmor, std::shared_ptr<Implant> equippedImplant)
{
    name_ = name;
    maxHp_ = maxHp;
    currentHp_ = currentHp;
    maxActionPoints_ = maxActionPoints;
    currentActionPoints_ = currentActionPoints;
    equippedWeapon_ = equippedWeapon;
    equippedArmor_ = equippedArmor;
    equippedImplant_ = equippedImplant;

}

Enemy::Enemy(const Enemy &enemyObject){
    name_ = enemyObject.name_;
    maxHp_ = enemyObject.maxHp_;
    currentHp_ = enemyObject.currentHp_;
    maxActionPoints_ = enemyObject.maxActionPoints_;
    currentActionPoints_ = enemyObject.currentActionPoints_;
    equippedWeapon_ = enemyObject.equippedWeapon_;
    equippedArmor_ = enemyObject.equippedArmor_;
    equippedImplant_ = enemyObject.equippedImplant_;
}

Enemy::~Enemy(){
}
