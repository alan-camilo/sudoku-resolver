#include "sudoku.h"
#include <stddef.h>

int init_empty_cells(int board[BOARD_DIM][BOARD_DIM], cell_t* empty_cells) {
    int nb_empty_cells = 0;
    cell_t* current_cell = empty_cells;
    cell_t* previous_cell = NULL;

    for (int y = 0; y < BOARD_DIM; y++) {
        for (int x = 0; x < BOARD_DIM; x++) {
            if (board[y][x] == 0) {
                nb_empty_cells++;
                if (previous_cell != NULL) {
                    previous_cell->next = current_cell;
                }
                current_cell->val = 0;
                current_cell->x = x;
                current_cell->y = y;
                current_cell->previous = previous_cell;
                current_cell->next = NULL;
                previous_cell = current_cell;
            }
        }
    }

    return nb_empty_cells;
}

state_t simple_solve(int board[BOARD_DIM][BOARD_DIM]) {
    cell_t empty_cells;
    int nb_empty_cells = init_empty_cells(board, &empty_cells);

    /* TODO: vérifier nb_empty_cells*/

    cell_t current_cell;
    cell_t previous_cell;

    while (empty_cells.next != NULL) {
        previous_cell = current_cell;
        current_cell = empty_cells;

        while (!is_board_valid(board, current_cell)) {
            increment_cell(&current_cell);

            if (current_cell.val == 9) {
               if (current_cell.previous == NULL) {
                   return NO_SOLUTION;
               }

               /* Clear current cell and backtrack */
               current_cell.val = 0;
               current_cell = previous_cell;
               break;
            }
        }
    }

    return SOLVED;
}

void increment_cell(cell_t* cell) {
    if (cell->val < 9) {
        (cell->val)++;
    }
}

bool is_board_valid(int board[BOARD_DIM][BOARD_DIM], cell_t cell) {
    if (cell.val == 0) {
        return false;
    }

    return (check_row(board, cell.val, cell.y) &&
            check_column(board, cell.val, cell. x) &&
            check_box(board, cell.val, cell.y, cell.x));
}

bool check_row(int board[BOARD_DIM][BOARD_DIM], int val, int row) {
    for (int x = 0; x < BOARD_DIM; x++) {
        if (board[row][x] == val) {
            return false;
        }
    }
    return true;
}

bool check_column(int board[BOARD_DIM][BOARD_DIM], int val, int column) {
    for (int y = 0; y < BOARD_DIM; y++) {
        if (board[y][column] == val) {
            return false;
        }
    }

    return true;
}

bool check_box(int board[BOARD_DIM][BOARD_DIM], int val, int y, int x) {
    int _y = y - (y % 3);
    int _x = x - (x % 3);    // ou encore : _y = 3 * (y / 3), _x = 3 * (x / 3);
    for (y = _y; y < (_y + 3); y++) {
        for (x = _x; x < (_x + 3); x++) {
            if (board[y][x] == val) {
                return false;
            }
        }
    }
    return true;
}
