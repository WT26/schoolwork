#ifndef MAPTILE_H
#define MAPTILE_H

#include "character.h"

#include <memory>

class MapTile
{

    enum tileType {CONCRETE_FLOOR};

public:
    MapTile();
    bool addCharacter(std::shared_ptr<Character> character);
    void removeCharacter();
    std::shared_ptr<Character> getCharacter();

private:
    tileType type_;
    std::shared_ptr<Character> characterInTile_;
};

#endif // MAPTILE_H
