#include <stdio.h>
#include <stdbool.h>

#define BOARD_SIZE 9
#define EMPTY_CELL 0

// Function to check if a number is valid in a given cell
bool isValid(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, int num) {
    // Check the row
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[row][i] == num) {
            return false;
        }
    }

    // Check the column
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][col] == num) {
            return false;
        }
    }

    // Check the box
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY_CELL) {
                for (int num = 1; num <= BOARD_SIZE; num++) {
                    if (isValid(board, i, j, num)) {
                        board[i][j] = num;
                        if (solveSudoku(board)) {
                            return true;
                        }
                        board[i][j] = EMPTY_CELL;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// Function to print the Sudoku board
void printBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

// Main function
int main() {
    int board[BOARD_SIZE][BOARD_SIZE] = {
        {5, 3, EMPTY_CELL, EMPTY_CELL, 7, EMPTY_CELL, EMPTY_CELL, EMPTY CELL, EMPTY_CELL},
        {6, EMPTY CELL, EMPTY CELL, 1, 9, 5, EMPTY_CELL, EMPTY CELL, EMPTY CELL},
        {EMPTY_CELL, 9, 8, EMPTY_CELL, EMPTY Cell, EMPTY CELL, EMPTY CELL, 6, EMPTY CELL},
        {1, 6, EMPTY CELL, EMPTY CELL, EMPTY CELL, EMPTY Cell, 2, 8, EMPTY CELL},
        {EMPTY CELL, 5, EMPTY Cell, EMPTY CELL, 3, 4, EMPTY Cell, EMPTY Cell, 1},
        {9, 7, EMPTY_CELL, EMPTY CELL, 2, EMPTY Cell, EMPTY Cell, EMPTY Cell, 6},
        {4, 2, 6, EMPTY Cell, EMPTY Cell, 3, 1, EMPTY Cell, 5},
        {EMPTY Cell, 1, EMPTY Cell, 4, 8, EMPTY Cell, EMPTY Cell, EMPTY Cell, 3},
        {7, 8, 3, EMPTY Cell, EMPTY Cell, 2, EMPTY Cell, EMPTY CELL, 9}
    };

    if (solveSudoku(board)) {
        printf("Solution found:\n");
        printBoard(board);
    } else {
        printf("No solution found.\n");
    }

    return 0;
}