#include <stdbool.h>

#define BOARD_DIM 9

typedef enum {
    NO_SOLUTION,
    SOLVED
} state_t;

typedef struct cell_t cell_t;
struct cell_t {
    int val;
    int x;
    int y;
    cell_t* previous;
    cell_t* next;
};

state_t simple_solve(int [BOARD_DIM][BOARD_DIM]);
int init_empty_cells(int [BOARD_DIM][BOARD_DIM], cell_t*);
void increment_cell(cell_t*);
bool is_board_valid(int [BOARD_DIM][BOARD_DIM], cell_t);
bool check_row(int [BOARD_DIM][BOARD_DIM], int, int);
bool check_column(int [BOARD_DIM][BOARD_DIM], int, int);
bool check_box(int [BOARD_DIM][BOARD_DIM], int, int, int);
