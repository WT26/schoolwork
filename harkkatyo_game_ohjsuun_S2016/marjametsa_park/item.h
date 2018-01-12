#ifndef ITEM_H
#define ITEM_H

#include <QString>

// Tavaraluokka, josta periytetään esim. Implantit, Weaponit sekä Armorit.
class Item
{
public:
    Item();
    virtual ~Item(){}

    QString getName();
    int getPrice();

protected:
    QString name_;
    int price_;
};

#endif // ITEM_H
