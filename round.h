#ifndef ROUND_H
#define ROUND_H

#include "big_game.h"

typedef enum
{
    PLAYER_X,
    PLAYER_O
} player_t;

typedef struct
{
    big_game_t *game;
    player_t current_player;
    int round_over;
} round_t;

/// @brief Initializes a new game round
/// @return Pointer to the created round
round_t *round_create(void);

/// @brief Destroys the round and the associated game
/// @param round Round to destroy
void round_destroy(round_t *round);

/// @brief Returns the player whose turn it is
/// @param round Current round
/// @return Current player
player_t round_get_current_player(const round_t *round);

/// @brief Plays a move in the ultimate tic-tac-toe game
/// @param round Current round
/// @param board_row Row of the small board (0-2)
/// @param board_col Column of the small board (0-2)
/// @param cell_row Row inside the small board (0-2)
/// @param cell_col Column inside the small board (0-2)
/// @return 1 if move was successful, 0 otherwise
int round_play_move(
    round_t *round,
    int board_row,
    int board_col,
    int cell_row,
    int cell_col);

#endif
