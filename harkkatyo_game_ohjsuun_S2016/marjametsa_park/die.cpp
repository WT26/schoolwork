#include "die.h"
#include <stdlib.h>


Die::Die()
{
}

int Die::rollDie(int minValue, int maxValue) {
    int value = rand() % maxValue-minValue + minValue;
    return value;
}
