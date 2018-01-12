#include "armor.h"

Armor::Armor(QString name, int price, int damageResistance) {
    name_ = name;
    price_ = price;
    damageResistance_ = damageResistance;
}

QString Armor::getName() {
    return name_;
}

int Armor::getDefence() {
    return damageResistance_;
}

int Armor::getPrice() {
    return price_;
}
