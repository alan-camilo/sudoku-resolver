#define BOARD_DIM 9
#define CELL_VAL_MAX 9

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
      printf("------------------");
    }
  }
  printf("\n");
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
  return nb_empty_cells;
}

bool is_cell_valid(char *board, int position, char value)
{
  char row = position / 9;
  char column = position % 9;
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

__kernel void resolve(__global float4* data, 
      __local float* local_result, __global float* group_result) {
          uint local_addr = get_local_id(0);
}

// __kernel void add_numbers(__global float4* data, 
//       __local float* local_result, __global float* group_result) {
//           uint local_addr = get_local_id(0);
// }