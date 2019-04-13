#define BOARD_DIM 9
#define CELL_VAL_MAX 9

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

bool is_cell_valid(char *board, int position, char value)
{
  char row = position / 9;
  char column = position % 9;
  if (checkRow(board, row, value) 
      && checkColumn(board, column, value) 
      && checkBox(board, row, column, value))
  {
    return true;
  }
  return false;
}

int get_empty_cells(char *board, char *empty_cell) {
  int nb_empty_cells = 0;
  int empty_cell_i = 0;
  bool first_empty_cell = true;
  bool second_empty_cell = true;
  for (int i = 0; i < BOARD_DIM * BOARD_DIM; i++) {
    if (board[i] == 0) {
      /* première case vide -> group_id s'il est valide */
      if (first_empty_cell) {
        if (is_cell_valid(board, i, (char)(get_group_id(0) + 1))) {
          board[i] = get_group_id(0) + 1;
          first_empty_cell = false;
        } else {
          return -1;
        }
      /* seconde case vide -> local_id s'il est valide */
      } else if (second_empty_cell) {
        if (is_cell_valid(board, i, (char)(get_local_id(0) + 1))) {
          board[i] = get_local_id(0) + 1;
          second_empty_cell = false;
        } else {
          return -1;
        }
      } else {
        empty_cell[empty_cell_i] = i;
        empty_cell_i++;
        nb_empty_cells++;
      }
    }
  }
  return nb_empty_cells;
}

__kernel void resolve(__global char* board, __global char* group_result) {
  char local_board[BOARD_DIM * BOARD_DIM] = {0};
  /* copie la grille localement */
  for (int i = 0; i < BOARD_DIM * BOARD_DIM; i++) {
    local_board[i] = board[i];
  }
  /* récupère index et nombre de cellules vides */
  char empty_cell[BOARD_DIM * BOARD_DIM] = {0};
  int nb_empty_cells = get_empty_cells(local_board, empty_cell);

  /* parcourt cellules vides */
  int empty_cell_i = 0;
  if (nb_empty_cells > -1) {
    while ((empty_cell_i >= 0) && (empty_cell_i < nb_empty_cells)) {
      /* incrémente cellule jusqu'à valide */
      int position = empty_cell[empty_cell_i];
      bool cell_state = false;
      for (char cell_val = (local_board[position] + 1); cell_val <= CELL_VAL_MAX;
          cell_val++) {
        cell_state = is_cell_valid(local_board, position, cell_val);
        if (cell_state) {
          /* fixe la valeur de la cellule vide */
          local_board[position] = cell_val;
          /* cellule vide suivante */
          empty_cell_i++;
          break;
        }
      }
      /* BACKTRACKING */
      if (!cell_state) {
        /* réinitialise cellule courante */
        local_board[position] = 0;
        empty_cell_i--;
      }
    }
  }

  /* ce work item a trouvé la solution */
  if (empty_cell_i > 0) {
    /* copie la grille résolue dans la variable output */
    for (int i = 0; i < BOARD_DIM * BOARD_DIM; i++) {
        group_result[i] = local_board[i];
    }
  }
}
