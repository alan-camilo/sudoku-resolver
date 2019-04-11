#include "sudoku-iterative.h"
#include <stdbool.h>
#include <stdio.h>

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
  }
  puts("\n");
}

bool checkRow(char *board, char row, char value)
{
  printf("function checkRow\n\n");
  for (char column = 0; column < 9; column++)
    if (board[column + BOARD_DIM * row] == value)
      return false;
  return true;
}

bool checkColumn(char *board, char column, char value)
{
  printf("function checkColumn\n\n");
  for (char row = 0; row < 9; row++)
    if (board[column + BOARD_DIM * row] == value)
      return false;
  return true;
}

bool checkBox(char *board, char row, char column, char value)
{
  char _row = row - (row % 3);
  char _column = column - (column % 3);
  printf("function checkBox\n_row = %d\n_column = %d\n\n", _row, _column);
  for (row = _row; row < _row + 3; row++)
  {
    for (column = _column; column < _column + 3; column++)
    {
      printf("boucle for\nrow = %d\ncolumn = %d\n\n", row, column);
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
  return nb_empty_cells;
}

bool is_cell_valid(char *board, int position, char value)
{
  char row = position / 9;
  char column = position % 9;
  //printf("function is_cell_valid\nposition = %d\nrow = %d\ncolumn = %d\nvalue = %d\n\n", position, row, column, value);
  if (checkRow(board, row, value) && checkColumn(board, position, value) && checkBox(board, row, column, value))
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

void resolve(char *board)
{
  /* récupère index et nombre de cellules vides */
  char empty_cell[BOARD_DIM * BOARD_DIM] = 0;
  int nb_empty_cells = get_empty_cells(empty_cell, board);

  /* parcourt cellules vides */
  int i = 0;
  while (!is_board_valid(board, i) && stack_i >= 0)
  {
    //printf("%d\n", i);
    if (board[i] == 0)
    {
      /* incrémente cellule jusqu'à valide */
      bool cell_state = false;
      for (char cell_val = 1; cell_val <= CELL_VAL_MAX; cell_val++)
      {
        cell_state = is_cell_valid(board, i, cell_val);
        if (cell_state)
        {
          board[i] = cell_val;
          /* ajout stack */
          stack[stack_i] = i;
          stack_i++;
          /* cellule suivante */
          i++;
          printf("ajout stack\n");
          break;
        }
        else
        {
          /* pop stack */
          stack_i--;
          i = stack[stack_i];
          board[i]++;
          i++;
          /* réinitialise cellule courante */
          board[i] = 0;
        }
      }
    }
    else
    {
      /* */
      i++;
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
