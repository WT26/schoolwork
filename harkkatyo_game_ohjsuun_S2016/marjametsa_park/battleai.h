#ifndef BATTLEAI_H
#define BATTLEAI_H

#include "character.h"
#include "battlemap.h"

class BattleAI
{
public:
    BattleAI();
    ~BattleAI();
    void setBattleMap(BattleMap* battleMap);
    void performTurn();
    void decideCharacterMove(std::shared_ptr<Character> aiCharacter,
                             int startTile);

private:
    BattleMap* map_;
};

#endif // BATTLEAI_H
