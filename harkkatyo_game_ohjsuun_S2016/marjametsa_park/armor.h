#ifndef ARMOR_H
#define ARMOR_H

#include "item.h"

#include <QString>

// Charactereilla oleva suojavaruste. Lisää Characterin suojausta
// vahinkoa vastaan.
class Armor : public Item
{
public:
    Armor(QString name, int damage_resistance, int price);
    QString getName();
    int getDefence();
    int getPrice();

private:
    int damageResistance_;

};

#endif // ARMOR_H
