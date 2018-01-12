#ifndef IMPLANT_H
#define IMPLANT_H

#include "item.h"

// Implantluokka, jota Characterit käyttävät. Lisäävät erinäisiä Boosteja
// Charactereille.
class Implant : public Item
{
public:
    Implant(QString name, int price, int rangeBonus, int attackBonus, int defenceBonus);
    QString getName();
    int getPrice();
    int getRangeBonus();
    int getAttackBonus();
    int getDefenceBonus();

private:
    int rangeBonus_;
    int attackBonus_;
    int defenceBonus_;
};

#endif // IMPLANT_H
