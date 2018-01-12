#include "maptile.h"
#include <QDebug>
MapTile::MapTile()
{
    type_ = tileType::CONCRETE_FLOOR;
}

bool MapTile::addCharacter(std::shared_ptr<Character> character){
    if (type_ == tileType::CONCRETE_FLOOR & characterInTile_ == nullptr){
        characterInTile_ = character;
        qDebug() << "Hahmo lisätty ruutuun";
        return true;
    } else {
        return false;
    }
}

void MapTile::removeCharacter(){
    characterInTile_ = nullptr;
}

std::shared_ptr<Character> MapTile::getCharacter(){
    return characterInTile_;
}
