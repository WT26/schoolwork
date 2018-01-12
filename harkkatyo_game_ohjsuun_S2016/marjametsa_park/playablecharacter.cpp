#include "playablecharacter.h"

PlayableCharacter::PlayableCharacter(QString name, int maxHp, int currentHp, int maxActionPoints,
         int currentActionPoints, std::shared_ptr<Weapon>equippedWeapon,
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
