#include "character.h"
#include <QDebug>


Character::Character()
{
}

bool Character::isDead(){
    if (currentHp_ <= 0){
        return true;
        qDebug() << "Hahmo " << this->getName() << " on kuollut.";
    } else {
        return false;
    }
}


void Character::loseActionPoints() {
    this->currentActionPoints_ = 0;
}


bool Character::useActionPoints(int ap){
    if (ap < currentActionPoints_){
        this->currentActionPoints_ - ap;
        return true;
    } else {
        return false;
    }

}


int Character::getCurrentHP() {
    return currentHp_;
}


int Character::getMaxHP() {
    return maxHp_;
}


int Character::getMaxActionPoints() {
    return maxActionPoints_;
}


int Character::getCurrentActionPoints() {
    return currentActionPoints_;
}


void Character::equipWeapon(std::shared_ptr<Weapon> weapon) {
    equippedWeapon_ = weapon;
}

void Character::equipArmor(std::shared_ptr<Armor> armor) {
    equippedArmor_ = armor;
}


void Character::equipImplant(std::shared_ptr<Implant> implant) {
    equippedImplant_ = implant;
}


QString Character::getName() {
    return name_;
}


std::shared_ptr<Weapon> Character::getEquippedWeapon() {
    return equippedWeapon_;
}


std::shared_ptr<Armor> Character::getEquippedArmor() {
    return equippedArmor_;
}


std::shared_ptr<Implant> Character::getEquippedImplant() {
    return equippedImplant_;
}


bool Character::shoot(){

    // Ladataan jos ase tyhjä ja yritetään ampua uudelleen.
    if (equippedWeapon_->clipEmpty()){
        qDebug() << "Ladataan tyhjä lipas";

        if (this->reload()){
            qDebug() << "Lataaminen onnistui, ammutaan";
            this->shoot();

        } else {
            qDebug() << "Lataaminen epäonnistui.";
        }

    } else {

        if (currentActionPoints_ >= equippedWeapon_->getShootAp()){
            equippedWeapon_->shoot();
            qDebug() << "Lippaassa tarpeeksi ammuksia ja hahmolla tarpeeksi ap:ta, ammutaan";
            qDebug() << "Hahmolla AP:tä " <<  currentActionPoints_;
            currentActionPoints_ = currentActionPoints_ - equippedWeapon_->getShootAp();
            return true;
        } else {
            qDebug() << "Ei tarpeeksi AP:tä, ei voi ampua.";
            qDebug() << "Hahmolla AP:tä " <<  currentActionPoints_;
            return false;

        }

    }
}

bool Character::reload(){
    if (currentActionPoints_ >= equippedWeapon_->getReloadAp()){
        equippedWeapon_->reload();
        currentActionPoints_ = 0;
        return true;
    } else {
        return false;
    }
}

Weapon::WeaponType Character::getAttackType() {
    return this->equippedWeapon_->getType();
}

int Character::receiveDamage(int damage) {
    this->currentHp_ = this->currentHp_ - damage;
    return this->currentHp_;
}

void Character::fillActionPoints(){
    qDebug() << "Asetetaan AP maksimiin hahmolle " << name_;
    qDebug() << "Current AP " << currentActionPoints_ << "Max AP " << maxActionPoints_;
    currentActionPoints_ = maxActionPoints_;
    qDebug() << "New current AP " << currentActionPoints_;
}

void Character::fillHealth() {
    currentHp_ = maxHp_;
}


void Character::loadCharacter(QString name, int maxHp, int currentHp,
                              int maxAp, int currentAp, std::shared_ptr<Weapon>equippedWeapon,
                              std::shared_ptr<Armor> equippedArmor, std::shared_ptr<Implant> equippedImplant) {

    name_ = name;
    maxHp_ = maxHp;
    currentHp_ = currentHp;
    maxActionPoints_ = maxAp;
    currentActionPoints_ = currentAp;
    equippedWeapon_ = equippedWeapon;
    equippedArmor_ = equippedArmor;
    equippedImplant_ = equippedImplant;
}
