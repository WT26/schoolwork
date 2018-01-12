#include <item.h>

Item::Item()
{
}

QString Item::getName(){
    return name_;
}

int Item::getPrice(){
    return price_;
}
