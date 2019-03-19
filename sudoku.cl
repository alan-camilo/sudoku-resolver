// Fonction d'affichage
void printBoard(char board[9][9]) {
    for (char i=0; i<9; i++) {
        for (char j=0; j<9; j++) {
            prcharf( ((j+1)%3) ? "%d " : "%d|", board[i][j]);
        }
        putchar('\n');
        if (!((i+1)%3))
            puts("------------------");
    }
    puts("\n\n");
}

bool checkRow(char k, char board[9][9], char i) {
    for (char j=0; j < 9; j++)
        if (board[i][j] == k)
            return false;
    return true;
}

bool checkColumn(char k, char board[9][9], char j) {
    for (char i=0; i < 9; i++)
        if (board[i][j] == k)
            return false;
    return true;
}

bool checkBox(char k, char board[9][9], char i, char j) {
    char _i = i-(i%3), _j = j-(j%3);
    for (i=_i; i < _i+3; i++)
        for (j=_j; j < _j+3; j++)
            if (board[i][j] == k)
                return false;
    return true;
}

bool isValid(char board[9][9], char position) {
    if (position == 9*9)
        return true;

    char i = position/9, j = position%9; /* i: row, j: column */

    if (board[i][j] != 0)
        return isValid(board, position+1); 
    for (char k=1; k <= 9; k++) {
        if (checkRow(k,board,i) && checkColumn(k,board,j) && checkBox(k,board,i,j)) {
            board[i][j] = k;

            if (isValid(board, position+1))
                return true;
        }
    }
    board[i][j] = 0;

    return false;
}

__kernel void add_numbers(__global float4* data, 
      __local float* local_result, __global float* group_result) { 
          uint local_addr = get_local_id(0);
      }