#include "implant.h"

Implant::Implant(QString name, int price, int rangeBonus, int attackBonus, int defenceBonus) {
    name_ = name;
    price_ = price;
    rangeBonus_ = rangeBonus;
    attackBonus_ = attackBonus;
    defenceBonus_ = defenceBonus;
}

QString Implant::getName() {
    return name_;
}

int Implant::getPrice() {
    return price_;
}

int Implant::getRangeBonus() {
    return rangeBonus_;
}

int Implant::getAttackBonus() {
    return attackBonus_;
}

int Implant::getDefenceBonus() {
    return defenceBonus_;
}
