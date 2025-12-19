#include "small_game.h"
#include <stdlib.h>

struct SmallGame
{
    Tile *tiles[3][3];
    small_result_t result;
};
