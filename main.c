#include "sudoku.h"
#include <stdio.h>

int main(void) {
    int board[BOARD_DIM * BOARD_DIM] = {
        1, 1, 1, 1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    cell_t empty_cells;
    printf("nb_empty_cells %d\n", init_empty_cells(board, &empty_cells));
    cell_t test_cell = {2, 2, 0, NULL, NULL};
    printf("check row %d\n", check_row(board, 2, 0));
    printf("check column %d\n", check_column(board, 1, 0));
    printf("check box %d\n", check_box(board, 1, 7, 7));
    printf("check board %d\n", is_board_valid(board, test_cell));
    return 0;
}