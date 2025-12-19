#ifndef BIG_GAME_H
#define BIG_GAME_H

#include "small_game.h"

typedef enum
{
    BIG_GAME_ONGOING,
    BIG_GAME_X_WON,
    BIG_GAME_O_WON,
    BIG_GAME_DRAW
} big_game_state_t;

typedef struct
{
    small_game_t *boards[3][3];
    int forced_row;
    int forced_col;
    big_game_state_t state;
} big_game_t;

/// @brief Creates a new ultimate tic-tac-toe game
/// @return Pointer to the created big game
big_game_t *big_game_create(void);

/// @brief Destroys the big game and all small boards
/// @param game Big game to destroy
void big_game_destroy(big_game_t *game);

/// @brief Returns the current state of the big game
/// @param game Big game to read
/// @return State of the big game
big_game_state_t big_game_get_state(const big_game_t *game);

#endif
