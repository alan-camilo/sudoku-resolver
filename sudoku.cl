#define BOARD_DIM 9
#define CELL_VAL_MAX 9

bool checkRow(__global char *board, char row, char value)
{
  for (char column = 0; column < 9; column++)
    if (board[column + BOARD_DIM * row] == value)
      return false;
  return true;
}

bool checkColumn(__global char *board, char column, char value)
{
  for (char row = 0; row < 9; row++)
    if (board[column + BOARD_DIM * row] == value)
      return false;
  return true;
}

bool checkBox(__global char *board, char row, char column, char value)
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

int get_empty_cells(char *empty_cell, __global char *board) {
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

bool is_cell_valid(__global char *board, int position, char value)
{
  char row = position / 9;
  char column = position % 9;
  if (checkRow(board, row, value) && checkColumn(board, column, value) && checkBox(board, row, column, value))
  {
    return true;
  }
  return false;
}

bool is_board_valid(__global char *board, int position)
{
  return (position == BOARD_DIM * BOARD_DIM) && is_cell_valid(board, position, board[position]);
}

__kernel void resolve(__global char* board, __global char* group_result) {
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
  for(int i = 0; i < BOARD_DIM * BOARD_DIM; i++) {
    group_result[i] = board[i];
  }
}

// __kernel void add_numbers(__global float4* data, 
//       __local float* local_result, __global float* group_result) {
//           uint local_addr = get_local_id(0);
// }