#include <stdio.h>
#include "round.h"
#include "small_game.h"
#include "tile.h"

/* Returns a single character representing the cell in a small board.
   If the board is already won/drawn, every cell shows the board's winner. */
static char cell_char(const small_game_t *sg, int row, int col)
{
    small_game_state_t s = small_game_get_state(sg);
    if (s == SMALL_GAME_X_WON) return 'X';
    if (s == SMALL_GAME_O_WON) return 'O';
    if (s == SMALL_GAME_DRAW)  return '#';

    tile_state_t t = tile_get_state(sg->tiles[row][col]);
    return (t == TILE_X) ? 'X' : (t == TILE_O) ? 'O' : '.';
}

static void print_big(const big_game_t *bg)
{
    int fr = bg->forced_row;
    int fc = bg->forced_col;

    for (int br = 0; br < 3; br++)
    {
        for (int row = 0; row < 3; row++)
        {
            for (int bc = 0; bc < 3; bc++)
            {
                /* highlight the forced (active) board with brackets */
                int is_forced = (fr == -1) || (br == fr && bc == fc);
                if (row == 0 && is_forced)
                    printf("[");
                else
                    printf(" ");

                for (int col = 0; col < 3; col++)
                    printf("%c ", cell_char(bg->boards[br][bc], row, col));

                if (row == 0 && is_forced)
                    printf("]");
                else
                    printf(" ");

                if (bc < 2) printf("| ");
            }
            printf("\n");
        }
        if (br < 2) printf("  ---------++---------++---------\n");
    }
}

int main(void)
{
    round_t *round = round_create();
    if (!round)
        return 1;

    while (1)
    {
        printf("\n");
        print_big(round->game);

        big_game_t *bg = round->game;
        if (bg->forced_row == -1)
            printf("\n(Free choice — you may play in any open board)\n");
        else
            printf("\nForced board: row %d, col %d\n",
                   bg->forced_row, bg->forced_col);

        player_t p = round_get_current_player(round);
        printf("Player %c's turn\n", p == PLAYER_X ? 'X' : 'O');

        int br, bc, cr, cc;
        printf("Enter board_row board_col cell_row cell_col (0-based): ");
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
            printf("\n");
            print_big(round->game);
            if (state == BIG_GAME_X_WON)
                printf("\nPlayer X wins the game!\n");
            else if (state == BIG_GAME_O_WON)
                printf("\nPlayer O wins the game!\n");
            else
                printf("\nIt's a draw!\n");
            break;
        }
    }

    round_destroy(round);
    return 0;
}
