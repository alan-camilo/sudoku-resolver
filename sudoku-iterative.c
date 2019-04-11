#include "sudoku-iterative.h"
#include <stdbool.h>
#include <stdio.h>

static int stack[BOARD_DIM * BOARD_DIM];
static int stack_i = 0;

void printBoard(char *board);
bool checkRow(char *board, char row, char value);
bool checkColumn(char *board, char column, char value);
bool checkBox(char *board, char row, char column, char value);
bool is_cell_valid(char *board, int position);
bool is_board_valid(char *board, int position);

void printBoard(char *board)
{
  for (int i = 0; i < BOARD_DIM * BOARD_DIM; i++) {
    printf(((i + 1) % 3) ? "%d " : "%d|", board[i]);
    if ((i + 1) % BOARD_DIM == 0) {
      printf("\n");
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
    for (column = _column; column < _column + 3; column++)
      if (board[column + BOARD_DIM * row] == value)
        return false;
  return true;
}

bool is_cell_valid(char *board, int position)
{
  char row = position / 9;
  char column = position % 9;
  char value = board[position];
  if (checkRow(board, row, value) && checkColumn(board, position, value) && checkBox(board, row, column, value))
  {
    return true;
  }
  return false;
}

bool is_board_valid(char *board, int position)
{
  return (position == BOARD_DIM * BOARD_DIM) && is_cell_valid(board, position);
}

/* TODO: tester */

void resolve(char *board)
{
  /* parcourt cellules vides */
  int i = 0;
  while (!is_board_valid(board, i) && stack_i >= 0)
  {
    printf("%d\n", i);
    if (board[i] == 0)
    {
      /* incrémente cellule jusqu'à valide */
      bool cell_state = false;
      while ((board[i] <= CELL_VAL_MAX) && !cell_state)
      {
        board[i]++;
        cell_state = is_cell_valid(board, i);
      }
      if (cell_state)
      {
        /* ajout stack */
        stack[stack_i] = i;
        stack_i++;
        /* cellule suivante */
        i++;
      }
      else
      {
        /* pop stack */
        stack_i--;
        i = stack[stack_i];
        /* réinitialise cellule courante */
        board[i] = 0;
      }
    } /* fin traitement cellule vide */
  }   /* fin parcourt cellules vides */
}

int main(int argc, const char *argv[])
{
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

  printBoard(board);
  resolve(board);
  printBoard(board);
}
