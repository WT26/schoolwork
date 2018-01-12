#include "weapon.h"

Weapon::Weapon(QString name, int price, WeaponType type, int minDamage,
               int maxDamage, int minRange, int maxRange, int shootAp,
               int reloadAp, int spread, int clipsize, int bulletsPerShot)
{
    name_ = name;
    price_ = price;
    type_ = type;

    minDamage_ = minDamage;
    maxDamage_ = maxDamage;
    minRange_ = minRange;
    maxRange_ = maxRange;
    shootAp_= shootAp;
    reloadAp_ = reloadAp;
    spread_ = spread;

    clipsize_ = clipsize,
    bulletsInClip_ = clipsize,
    bulletsPerShot_ = bulletsPerShot;

}

Weapon::~Weapon() {
}

QString Weapon::getName() {
    return name_;
}

int Weapon::getPrice() {
    return price_;
}

int Weapon::getMinDamage() {
    return minDamage_;
}

int Weapon::getMaxDamage() {
    return maxDamage_;
}

int Weapon::getMinRange() {
    return minRange_;
}

int Weapon::getMaxRange() {
    return maxRange_;
}

int Weapon::getShootAp() {
    return shootAp_;
}

int Weapon::getReloadAp() {
    return reloadAp_;
}

int Weapon::getClipsize() {
    return clipsize_;
}

int Weapon::getBulletsInClip(){
    return bulletsInClip_;
}

bool Weapon::reload(){
    bulletsInClip_ = clipsize_;
    return true;
}

bool Weapon::shoot(){
    if (bulletsInClip_ >= bulletsPerShot_){
        bulletsInClip_ = bulletsInClip_ - bulletsPerShot_;
        return true;
    } else {
        return false;
    }
}

bool Weapon::clipEmpty(){
    return bulletsPerShot_ > bulletsInClip_;
}


/*int Weapon::getDamage(int distance) {
#
    if (distance > maxRange_ || distance < minRange_ || \
            type_ == Weapon::MELEE && distance > 1){
        return 0;
    }

    return die_->rollDie(minDamage_, maxDamage_);
}
*/
int Weapon::getSpread() {
    return spread_;
}

Weapon::WeaponType Weapon::getType() {
    return type_;
}
