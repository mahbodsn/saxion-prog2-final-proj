#ifndef TILE_H
#define TILE_H

typedef enum
{
    TILE_EMPTY,
    TILE_X,
    TILE_O
} tile_state_t;

typedef struct
{
    tile_state_t state;
} tile_t;

/// @brief Creates a new empty tile
/// @return Pointer to the created tile
tile_t *tile_create(void);

/// @brief Frees a tile from memory
/// @param tile Tile to destroy
void tile_destroy(tile_t *tile);

/// @brief Sets the state of a tile
/// @param tile Tile to modify
/// @param state New state of the tile
void tile_set_state(tile_t *tile, tile_state_t state);

/// @brief Returns the current state of a tile
/// @param tile Tile to read
/// @return State of the tile
tile_state_t tile_get_state(const tile_t *tile);

#endif
