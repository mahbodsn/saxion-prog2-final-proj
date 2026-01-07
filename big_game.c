#include <stdlib.h>
#include "big_game.h"

static int valid_small(const small_game_t *g)
{
    small_game_state_t s = small_game_get_state(g);
    return s == SMALL_GAME_ONGOING;
}

static big_game_state_t check_big(const big_game_t *g)
{
    for (int i = 0; i < 3; i++)
    {
        if (g->boards[i][0]->state == g->boards[i][1]->state &&
            g->boards[i][1]->state == g->boards[i][2]->state)
        {
            if (g->boards[i][0]->state == SMALL_GAME_X_WON)
                return BIG_GAME_X_WON;
            if (g->boards[i][0]->state == SMALL_GAME_O_WON)
                return BIG_GAME_O_WON;
        }

        if (g->boards[0][i]->state == g->boards[1][i]->state &&
            g->boards[1][i]->state == g->boards[2][i]->state)
        {
            if (g->boards[0][i]->state == SMALL_GAME_X_WON)
                return BIG_GAME_X_WON;
            if (g->boards[0][i]->state == SMALL_GAME_O_WON)
                return BIG_GAME_O_WON;
        }
    }

    return BIG_GAME_ONGOING;
}

void big_game_update_state(big_game_t *game)
{
    game->state = check_big(game);
}

// static big_game_state_t check_big(const big_game_t *g)
// {
//     for (int i = 0; i < 3; i++)
//     {
//         if (g->boards[i][0]->state == g->boards[i][1]->state &&
//             g->boards[i][1]->state == g->boards[i][2]->state)
//         {
//             if (g->boards[i][0]->state == SMALL_GAME_X_WON)
//                 return BIG_GAME_X_WON;
//             if (g->boards[i][0]->state == SMALL_GAME_O_WON)
//                 return BIG_GAME_O_WON;
//         }

//         if (g->boards[0][i]->state == g->boards[1][i]->state &&
//             g->boards[1][i]->state == g->boards[2][i]->state)
//         {
//             if (g->boards[0][i]->state == SMALL_GAME_X_WON)
//                 return BIG_GAME_X_WON;
//             if (g->boards[0][i]->state == SMALL_GAME_O_WON)
//                 return BIG_GAME_O_WON;
//         }
//     }

//     return BIG_GAME_ONGOING;
// }

big_game_t *big_game_create(void)
{
    big_game_t *g = malloc(sizeof(big_game_t));
    if (!g)
        return NULL;

    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            g->boards[r][c] = small_game_create();

    g->forced_row = -1;
    g->forced_col = -1;
    g->state = BIG_GAME_ONGOING;
    return g;
}

void big_game_destroy(big_game_t *game)
{
    if (!game)
        return;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            small_game_destroy(game->boards[r][c]);
    free(game);
}

big_game_state_t big_game_get_state(const big_game_t *game)
{
    return game->state;
}
