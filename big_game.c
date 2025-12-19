#include "big_game.h"
#include <stdlib.h>

struct BigGame
{
    SmallGame *boards[3][3];
    int forced_board_row;
    int forced_board_col;
    big_result_t result;
};
