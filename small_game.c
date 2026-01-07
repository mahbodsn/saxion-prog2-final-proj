#include <stdlib.h>
#include "small_game.h"

static int check_full(const small_game_t *g)
{
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (tile_get_state(g->tiles[r][c]) == TILE_EMPTY)
                return 0;
    return 1;
}

static small_game_state_t check_winner(const small_game_t *g)
{
    for (int i = 0; i < 3; i++)
    {
        tile_state_t r = tile_get_state(g->tiles[i][0]);
        if (r != TILE_EMPTY &&
            r == tile_get_state(g->tiles[i][1]) &&
            r == tile_get_state(g->tiles[i][2]))
            return r == TILE_X ? SMALL_GAME_X_WON : SMALL_GAME_O_WON;

        tile_state_t c = tile_get_state(g->tiles[0][i]);
        if (c != TILE_EMPTY &&
            c == tile_get_state(g->tiles[1][i]) &&
            c == tile_get_state(g->tiles[2][i]))
            return c == TILE_X ? SMALL_GAME_X_WON : SMALL_GAME_O_WON;
    }

    tile_state_t d = tile_get_state(g->tiles[0][0]);
    if (d != TILE_EMPTY &&
        d == tile_get_state(g->tiles[1][1]) &&
        d == tile_get_state(g->tiles[2][2]))
        return d == TILE_X ? SMALL_GAME_X_WON : SMALL_GAME_O_WON;

    d = tile_get_state(g->tiles[0][2]);
    if (d != TILE_EMPTY &&
        d == tile_get_state(g->tiles[1][1]) &&
        d == tile_get_state(g->tiles[2][0]))
        return d == TILE_X ? SMALL_GAME_X_WON : SMALL_GAME_O_WON;

    return check_full(g) ? SMALL_GAME_DRAW : SMALL_GAME_ONGOING;
}

small_game_t *small_game_create(void)
{
    small_game_t *g = malloc(sizeof(small_game_t));
    if (!g)
        return NULL;

    g->state = SMALL_GAME_ONGOING;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            g->tiles[r][c] = tile_create();

    return g;
}

void small_game_destroy(small_game_t *game)
{
    if (!game)
        return;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            tile_destroy(game->tiles[r][c]);

    free(game);
}

small_game_state_t small_game_get_state(const small_game_t *game)
{
    return game->state;
}

/* internal helper */
void small_game_update_state(small_game_t *game)
{
    game->state = check_winner(game);
}
