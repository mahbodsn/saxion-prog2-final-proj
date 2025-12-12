#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    X,
    O,
    EMPTY
} choice_t;

typedef struct
{
    int x;
    int y;
    choice_t choice;
} cell_t;

typedef struct
{
    cell_t *cells[3][3];
} table_t;

int main()
{
}