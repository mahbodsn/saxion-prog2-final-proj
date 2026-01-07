#include <stdio.h>
#include "round.h"
#include "tile.h"

static void print_small(const small_game_t *g)
{
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            tile_state_t t = tile_get_state(g->tiles[r][c]);
            char ch = (t == TILE_X) ? 'X' : (t == TILE_O) ? 'O'
                                                          : '.';
            printf("%c ", ch);
        }
        printf("\n");
    }
}

static void print_big(const big_game_t *bg)
{
    for (int br = 0; br < 3; br++)
    {
        for (int row = 0; row < 3; row++)
        {
            for (int bc = 0; bc < 3; bc++)
            {
                for (int col = 0; col < 3; col++)
                {
                    tile_state_t t =
                        tile_get_state(bg->boards[br][bc]->tiles[row][col]);
                    char ch = (t == TILE_X) ? 'X' : (t == TILE_O) ? 'O'
                                                                  : '.';
                    printf("%c ", ch);
                }
                printf("| ");
            }
            printf("\n");
        }
        printf("-----------------------\n");
    }
}

int main(void)
{
    round_t *round = round_create();
    if (!round)
        return 1;

    while (1)
    {
        print_big(round->game);

        player_t p = round_get_current_player(round);
        printf("Player %c turn\n", p == PLAYER_X ? 'X' : 'O');

        int br, bc, cr, cc;
        printf("Enter board_row board_col cell_row cell_col: ");
        if (scanf("%d %d %d %d", &br, &bc, &cr, &cc) != 4)
            break;

        if (round_play_move(round, br, bc, cr, cc) != 0)
        {
            printf("Invalid move, try again.\n");
            continue;
        }

        big_game_state_t state = big_game_get_state(round->game);
        if (state != BIG_GAME_ONGOING)
        {
            print_big(round->game);
            if (state == BIG_GAME_X_WON)
                printf("Player X wins!\n");
            else if (state == BIG_GAME_O_WON)
                printf("Player O wins!\n");
            else
                printf("Draw!\n");
            break;
        }
    }

    round_destroy(round);
    return 0;
}
