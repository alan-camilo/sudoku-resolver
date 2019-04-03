#include "sudoku-iterative.h"
#include <stdbool.h>

static int[BOARD_DIM * BOARD_DIM] stack;
static int stack_i = 0;

bool is_cell_valid(int);
bool is_board_valid(int i);

bool is_cell_valid(int i) {
  /* TODO: implémenter et tester */
  return false;
}

bool is_board_valid(int i) {
  return (i == BOARD_DIM * BOARD_DIM) && is_cell_valid(i);
}

/* TODO: tester */

void resolve(char *board) {
  /* parcourt cellules vides */
  int i = 0;
  while (is_board_valid(i) && stack_i >= 0) {
    if (board[i] == 0) {
      /* incrémente cellule jusqu'à valide */
      bool cell_state = false;
      while ((board[i] <= CELL_VAL_MAX) && !cell_state) {
        board[i]++;
        cell_state = is_cell_valid(i);
      }
      if (cell_state) {
        /* ajout stack */
        stack[stack_i] = i;
        stack_i++;
        /* cellule suivante */
        i++;
      } else {
        /* pop stack */
        stack_i--;
        i = stack[stack_i];
        /* réinitialise cellule courante */
        board[i] = 0;
      }
    } /* fin traitement cellule vide */
  }   /* fin parcourt cellules vides */
}

int main(int argc, const char *argv[]) {
  int board[BOARD_DIM] = {
    0, 9, 3, 0, 5, 0, 0, 0, 4,
    0, 0, 7, 0, 0, 0, 0, 8, 0,
    5, 6, 0, 9, 0, 0, 0, 0, 7,
    0, 8, 0, 0, 3, 9, 4, 2, 0,
    0, 4, 0, 8, 2, 7, 0, 3, 0,
    0, 3, 5, 6, 1, 0, 0, 9, 0,
    9, 0, 0, 0, 0, 5, 0, 4, 2,
    0, 7, 0, 0, 0, 0, 1, 0, 0,
    3, 0, 0, 0, 4, 0, 8, 7, 0
  };

  return 0;
}
