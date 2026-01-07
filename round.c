#include <stdlib.h>
#include "round.h"
#include "big_game.h"

extern void small_game_update_state(small_game_t *);

round_t *round_create(void)
{
    round_t *r = malloc(sizeof(round_t));
    if (!r)
        return NULL;

    r->game = big_game_create();
    r->current_player = PLAYER_X;
    r->round_over = 0;
    return r;
}

void round_destroy(round_t *round)
{
    if (!round)
        return;
    big_game_destroy(round->game);
    free(round);
}

player_t round_get_current_player(const round_t *round)
{
    return round->current_player;
}

int round_play_move(
    round_t *round,
    int br, int bc,
    int cr, int cc)
{
    if (round->round_over)
        return -1;

    big_game_t *bg = round->game;

    if ((bg->forced_row != -1 &&
         (br != bg->forced_row || bc != bg->forced_col)))
        return -1;

    small_game_t *sg = bg->boards[br][bc];
    if (sg->state != SMALL_GAME_ONGOING)
        return -1;

    tile_t *t = sg->tiles[cr][cc];
    if (tile_get_state(t) != TILE_EMPTY)
        return -1;

    tile_set_state(t, round->current_player == PLAYER_X ? TILE_X : TILE_O);

    small_game_update_state(sg);

    bg->forced_row = cr;
    bg->forced_col = cc;
    if (bg->boards[cr][cc]->state != SMALL_GAME_ONGOING)
    {
        bg->forced_row = -1;
        bg->forced_col = -1;
    }

    big_game_update_state(bg);
    if (bg->state != BIG_GAME_ONGOING)
        round->round_over = 1;

    round->current_player =
        (round->current_player == PLAYER_X) ? PLAYER_O : PLAYER_X;

    return 0;
}
