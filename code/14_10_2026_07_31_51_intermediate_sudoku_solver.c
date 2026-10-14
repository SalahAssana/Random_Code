#include <stdio.h>
#include <stdlib.h>

#define SUDOKU_SIZE 9
#define EMPTY_CELL -1

typedef struct {
    int board[SUDOKU_SIZE][SUDOKU_SIZE];
    int solved;
} Sudoku;

void print_board(Sudoku sudoku) {
    for (int i = 0; i < SUDOKU_SIZE; i++) {
        for (int j = 0; j < SUDOKU_SIZE; j++) {
            printf("%d ", sudoku.board[i][j]);
        }
        printf("\n");
    }
}

Sudoku solve_sudoku(Sudoku sudoku) {
    if (is_board_solved(sudoku)) {
        return sudoku;
    }

    for (int i = 0; i < SUDOKU_SIZE; i++) {
        for (int j = 0; j < SUDOKU_SIZE; j++) {
            if (sudoku.board[i][j] == EMPTY_CELL) {
                for (int num = 1; num <= SUDOKU_SIZE; num++) {
                    if (is_valid_number(sudoku, i, j, num)) {
                        sudoku.board[i][j] = num;
                        Sudoku new_sudoku = solve_sudoku(sudoku);
                        if (new_sudoku.solved) {
                            return new_sudoku;
                        }
                        sudoku.board[i][j] = EMPTY_CELL;
                    }
                }
            }
        }
    }

    // If no solution found, return the original board
    sudoku.solved = 0;
    return sudoku;
}

int is_board_solved(Sudoku sudoku) {
    for (int i = 0; i < SUDOKU_SIZE; i++) {
        for (int j = 0; j < SUDOKU_SIZE; j++) {
            if (sudoku.board[i][j] == EMPTY_CELL) {
                return 0;
            }
        }
    }
    return 1;
}

int is_valid_number(Sudoku sudoku, int row, int col, int num) {
    // Check the row
    for (int i = 0; i < SUDOKU_SIZE; i++) {
        if (sudoku.board[row][i] == num) {
            return 0;
        }
    }

    // Check the column
    for (int i = 0; i < SUDOKU_SIZE; i++) {
        if (sudoku.board[i][col] == num) {
            return 0;
        }
    }

    // Check the box
    int start_row = row - row % 3;
    int start_col = col - col % 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku.board[start_row + i][start_col + j] == num) {
                return 0;
            }
        }
    }

    return 1;
}

int main() {
    Sudoku sudoku = {{5, 3, EMPTY_CELL, EMPTY_CELL, 7, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL},
                     {6, EMPTY_CELL, EMPTY_CELL, 1, 9, 8, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL},
                     {EMPTY_CELL, 9, 8, EMPTY_CELL, EMPTY_CELL, 6, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL},
                     {1, 6, 7, EMPTY_Cell, 2, 5, EMPTY_Cell, EMPTY_Cell, EMPTY_Cell},
                     {3, EMPTY_Cell, EMPTY_Cell, 4, 5, 9, 8, EMPTY_Cell, EMPTY_Cell},
                     {4, 8, 5, EMPTY_Cell, EMPTY_Cell, EMPTY_Cell, 6, EMPTY_Cell, EMPTY_Cell},
                     {7, EMPTY_Cell, EMPTY_Cell, 3, 1, 2, EMPTY_Cell, EMPTY_Cell, EMPTY_Cell},
                     {9, EMPTY_Cell, EMPTY_Cell, 4, 8, 5, EMPTY_Cell, EMPTY_Cell, EMPTY_Cell},
                     {6, EMPTY_Cell, EMPTY_Cell, 7, 9, 1, EMPTY_Cell, EMPTY_Cell, EMPTY_Cell}};

    sudoku = solve_sudoku(sudoku);

    if (sudoku.solved) {
        printf("Sudoku solved:\n");
        print_board(sudoku);
    } else {
        printf("No solution found.\n");
    }

    return 0;
}