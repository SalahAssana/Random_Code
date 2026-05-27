#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define Sudoku puzzle size (3x3 grid)
#define SUDOKU_SIZE 9

// Function to check if a number can be placed in a given cell
bool isValid(int board[SUDOKU_SIZE][SUDOKU_SIZE], int row, int col, int num) {
    // Check the row
    for (int i = 0; i < SUDOKU_SIZE; i++) {
        if (board[row][i] == num) {
            return false;
        }
    }

    // Check the column
    for (int i = 0; i < SUDOKU_SIZE; i++) {
        if (board[i][col] == num) {
            return false;
        }
    }

    // Check the box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve Sudoku puzzle
bool solveSudoku(int board[SUDOKU_SIZE][SUDOKU_SIZE]) {
    for (int row = 0; row < SUDOKU_SIZE; row++) {
        for (int col = 0; col < SUDOKU_SIZE; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= SUDOKU_SIZE; num++) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;
                        if (solveSudoku(board)) {
                            return true;
                        }
                        board[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// Function to print Sudoku puzzle
void printSudoku(int board[SUDOKU_SIZE][SUDOKU_SIZE]) {
    for (int row = 0; row < SUDOKU_SIZE; row++) {
        for (int col = 0; col < SUDOKU_SIZE; col++) {
            printf("%d ", board[row][col]);
            if ((col + 1) % 3 == 0 && col < SUDOKU_SIZE - 1) {
                printf("| ");
            }
        }
        printf("\n");
        if (row < SUDOKU_SIZE - 2) {
            for (int i = 0; i < 9; i++) {
                printf("---");
                if ((i + 1) % 3 == 0 && i < 8) {
                    printf("| ");
                }
            }
            printf("\n");
        }
    }
}

// Main function
int main() {
    int board[SUDOKU_SIZE][SUDOKU_SIZE] = {
        {5, 3, 0, 7, 0, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 8, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 7, 4},
        {3, 0, 2, 0, 8, 5, 0, 0, 9},
        {7, 1, 0, 0, 6, 0, 2, 8, 0},
        {0, 6, 0, 0, 3, 4, 0, 0, 1},
        {0, 0, 0, 9, 7, 5, 0, 0, 0},
        {0, 0, 0, 0, 2, 0, 0, 3, 8},
        {0, 0, 0, 1, 0, 0, 9, 6, 4}
    };

    if (solveSudoku(board)) {
        printf("Solved Sudoku:\n");
        printSudoku(board);
    } else {
        printf("No solution exists.\n");
    }

    return 0;
}
