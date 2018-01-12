#ifndef PLAYABLECHARACTER_H
#define PLAYABLECHARACTER_H

#include "character.h"
#include "item.h"

#include <vector>

// Luokka ei-pelaaja-hahmoille.
class PlayableCharacter: public Character
{
public:
    PlayableCharacter(QString name, int maxHp, int currentHp, int maxActionPoints,
                      int currentActionPoints, std::shared_ptr<Weapon>equippedWeapon,
                      std::shared_ptr<Armor> equippedArmor, std::shared_ptr<Implant> equippedImplant);
    ~PlayableCharacter(){}

private:
    std::vector<Item*> inventory_;
};

#endif // PLAYABLECHARACTER_H
