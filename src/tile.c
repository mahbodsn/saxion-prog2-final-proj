#include <stdlib.h>
#include "tile.h"

struct tile
{
    tile_state_t state;
};

tile_t *tile_create(void)
{
    tile_t *t = malloc(sizeof(tile_t));
    if (!t)
        return NULL;
    t->state = TILE_EMPTY;
    return t;
}

void tile_destroy(tile_t *tile)
{
    if (tile)
        free(tile);
}

void tile_set_state(tile_t *tile, tile_state_t state)
{
    if (tile)
        tile->state = state;
}

tile_state_t tile_get_state(const tile_t *tile)
{
    return tile ? tile->state : TILE_EMPTY;
}
