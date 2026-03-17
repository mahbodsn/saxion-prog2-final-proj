#ifndef SMALL_GAME_H
#define SMALL_GAME_H

#include "tile.h"

typedef enum
{
    SMALL_GAME_ONGOING,
    SMALL_GAME_X_WON,
    SMALL_GAME_O_WON,
    SMALL_GAME_DRAW
} small_game_state_t;

typedef struct
{
    tile_t *tiles[3][3];
    small_game_state_t state;
} small_game_t;

/// @brief Creates a new 3x3 small game
/// @return Pointer to the created small game
small_game_t *small_game_create(void);

/// @brief Destroys a small game and its tiles
/// @param game Small game to destroy
void small_game_destroy(small_game_t *game);

/// @brief Returns the current state of the small game
/// @param game Small game to read
/// @return State of the small game
small_game_state_t small_game_get_state(const small_game_t *game);

#endif
