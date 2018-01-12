#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

#include <QObject>
#include <QString>

class Weapon : public Item
{

public:
    enum WeaponType {MELEE, RANGED, ANTI_ARMOR};

    Weapon(QString name, int price, WeaponType type, int minDamage, int maxDamage,
           int minRange, int maxRange, int shootAp,
           int reloadAp, int spread, int clipsize, int bulletsPerShot);
    ~Weapon();

    QString getName();
    int getPrice();
    int getMinDamage();
    int getMaxDamage();
    int getMinRange();
    int getMaxRange();
    int getShootAp();
    int getReloadAp();
    int getClipsize();
    int getBulletsInClip();
    int getSpread();
    bool clipEmpty();
    bool reload();
    bool shoot();
    WeaponType getType();


private:
    WeaponType type_;

    int minDamage_;
    int maxDamage_;
    int minRange_;
    int maxRange_;
    int shootAp_;
    int reloadAp_;
    int spread_;

    int clipsize_;
    int bulletsInClip_;
    int bulletsPerShot_;






};

#endif // WEAPON_H
