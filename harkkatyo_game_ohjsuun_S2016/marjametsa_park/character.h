#ifndef CHARACTER_H
#define CHARACTER_H

#include "weapon.h"
#include "implant.h"
#include "armor.h"

#include <vector>
#include <memory>
#include <QString>

// Hahmoluokka, josta periytyy PlayableCharacter sekä Enemy luokat.
class Character
{

public:
    Character();
    virtual ~Character(){}

    // Kertoo onko hahmo kuollut
    bool isDead();

    int getCurrentHP();
    int getMaxHP();

    int getMaxActionPoints();
    int getCurrentActionPoints();

    void equipWeapon(std::shared_ptr<Weapon> weapon);
    void equipArmor(std::shared_ptr<Armor> armor);
    void equipImplant(std::shared_ptr<Implant> implant);


    bool shoot();
    bool reload();

    void fillActionPoints();
    void fillHealth();

    QString getName();

    std::shared_ptr<Weapon> getEquippedWeapon();
    std::shared_ptr<Armor> getEquippedArmor();
    std::shared_ptr<Implant> getEquippedImplant();

    // Palauttaa AP:t maksimiarvoon
    void resetActionPoints();

    // Asettaa AP:t nollaan
    void loseActionPoints();

    // Palauttaa epätoden, jos yritetään käyttää enemmän action pointeja
    // kuin niitä on jäljellä
    bool useActionPoints(int ap);

    // Palauttaa hyökkäyksen tyypin
    Weapon::WeaponType getAttackType();

    // Ottaa vastaan vahinkoa. Palauttaa osumapisteet vahingon välityksen
    // jälkeen.
    int receiveDamage(int damage);

    void loadCharacter(QString name, int maxHp, int currentHp, int maxAp,
                       int currentAp, std::shared_ptr<Weapon> equippedWeapon,
                       std::shared_ptr<Armor> equippedArmor, std::shared_ptr<Implant> equippedImplant);

protected:
    QString name_;
    int maxHp_;
    int currentHp_;
    int maxActionPoints_;
    int currentActionPoints_;

    std::shared_ptr<Weapon> equippedWeapon_;
    std::shared_ptr<Armor> equippedArmor_;
    std::shared_ptr<Implant> equippedImplant_;
};



#endif // CHARACTER_H
