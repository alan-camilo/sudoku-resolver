#include "sudoku-iterative.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

static int stack[BOARD_DIM * BOARD_DIM];
static int stack_i = 0;

void printBoard(char *board);
bool checkRow(char *board, char row, char value);
bool checkColumn(char *board, char column, char value);
bool checkBox(char *board, char row, char column, char value);
int get_empty_cells(char *empty_cell, char *board);
bool is_cell_valid(char *board, int position, char value);
bool is_board_valid(char *board, int position);

void printBoard(char *board)
{
  for (int i = 0; i < BOARD_DIM * BOARD_DIM; i++)
  {
    printf(((i + 1) % 3) ? "%d " : "%d|", board[i]);
    if ((i + 1) % BOARD_DIM == 0)
    {
      printf("\n");
    }
    if (!((i + 1) % 27)) {
      puts("------------------");
    }
  }
  puts("\n");
}

bool checkRow(char *board, char row, char value)
{
  for (char column = 0; column < 9; column++)
    if (board[column + BOARD_DIM * row] == value)
      return false;
  return true;
}

bool checkColumn(char *board, char column, char value)
{
  for (char row = 0; row < 9; row++)
    if (board[column + BOARD_DIM * row] == value)
      return false;
  return true;
}

bool checkBox(char *board, char row, char column, char value)
{
  char _row = row - (row % 3);
  char _column = column - (column % 3);
  for (row = _row; row < _row + 3; row++)
  {
    for (column = _column; column < _column + 3; column++)
    {
      if (board[column + BOARD_DIM * row] == value)
        return false;
    }
  }

  return true;
}

int get_empty_cells(char *empty_cell, char *board) {
  int nb_empty_cells = 0;
  int empty_cell_i = 0;
  for (int i = 0; i < BOARD_DIM * BOARD_DIM; i++) {
    if (board[i] == 0) {
      empty_cell[empty_cell_i] = i;
      empty_cell_i++;
      nb_empty_cells++;
    }
  }

  // puts("EMPTY CELL");
  // for (int i = 0; i < nb_empty_cells; i++) {
  //   printf("%d ", empty_cell[i]);
  // }
  // puts("\n");

  return nb_empty_cells;
}

bool is_cell_valid(char *board, int position, char value)
{
  char row = position / 9;
  char column = position % 9;
  //printf("function is_cell_valid\nposition = %d\nrow = %d\ncolumn = %d\nvalue = %d\n\n", position, row, column, value);
  if (checkRow(board, row, value) && checkColumn(board, column, value) && checkBox(board, row, column, value))
  {
    return true;
  }
  return false;
}

bool is_board_valid(char *board, int position)
{
  return (position == BOARD_DIM * BOARD_DIM) && is_cell_valid(board, position, board[position]);
}

/* TODO: tester */

void resolve(char *board) {
  /* récupère index et nombre de cellules vides */
  char empty_cell[BOARD_DIM * BOARD_DIM] = {0};
  int nb_empty_cells = get_empty_cells(empty_cell, board);

  /* parcourt cellules vides */
  int empty_cell_i = 0;
  while ((empty_cell_i >= 0) && (empty_cell_i < nb_empty_cells)) {
    /* incrémente cellule jusqu'à valide */
    int position = empty_cell[empty_cell_i];
    bool cell_state = false;
    for (char cell_val = board[position] + 1; cell_val <= CELL_VAL_MAX;
         cell_val++) {
      cell_state = is_cell_valid(board, position, cell_val);
      if (cell_state) {
        /* fixe la valeur de la cellule vide */
        board[position] = cell_val;
        /* cellule vide suivante */
        empty_cell_i++;
        break;
      }
    }
    /* BACKTRACKING */
    /* if ((cell_val > CELL_VAL_MAX) && (!cell_state)) */
    if (!cell_state) {
      /* réinitialise cellule courante */
      board[position] = 0;
      empty_cell_i--;
    }
  }
}

int main(int argc, const char *argv[])
{
  /* chrono */
  clock_t begin = clock();
  char board[BOARD_DIM * BOARD_DIM] = {
      0, 9, 3, 0, 5, 0, 0, 0, 4,
      0, 0, 7, 0, 0, 0, 0, 8, 0,
      5, 6, 0, 9, 0, 0, 0, 0, 7,
      0, 8, 0, 0, 3, 9, 4, 2, 0,
      0, 4, 0, 8, 2, 7, 0, 3, 0,
      0, 3, 5, 6, 1, 0, 0, 9, 0,
      9, 0, 0, 0, 0, 5, 0, 4, 2,
      0, 7, 0, 0, 0, 0, 1, 0, 0,
      3, 0, 0, 0, 4, 0, 8, 7, 0};

  char board_diff[BOARD_DIM * BOARD_DIM] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 3, 0, 8, 5,
      0, 0, 1, 0, 2, 0, 0, 0, 0,
      0, 0, 0, 5, 0, 7, 0, 0, 0,
      0, 0, 4, 0, 0, 0, 1, 0, 0,
      0, 9, 0, 0, 0, 0, 0, 0, 0,
      5, 0, 0, 0, 0, 0, 0, 7, 3,
      0, 0, 2, 0, 1, 0, 0, 0, 0,
      0, 0, 0, 0, 4, 0, 0, 0, 9};

  printBoard(board_diff);
  resolve(board_diff);

  /* chrono */
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time: %f\nbacktracking=%ld\nGrille apres\n", time_spent);

  printBoard(board_diff);
}
