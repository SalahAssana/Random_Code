#include <stdio.h>
#include <stdlib.h>

// Define the Sudoku board size (9x9)
#define BOARD_SIZE 9

// Function to check if it is safe to place a number in a cell
int isValid(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, int num) {
    // Check the row and column for the given number
    for (int i = 0; i < BOARD_SIZE; i++) {
        if ((board[row][i] == num || board[i][col] == num)) return 0;
    }

    // Check the sub-grid of 3x3 for the given number
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((board[i + startRow][j + startCol] == num)) return 0;
        }
    }

    // If no conflict, return 1
    return 1;
}

// Function to solve the Sudoku board using backtracking algorithm
int solveSudoku(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) { // If the cell is empty
                for (int num = 1; num <= BOARD_SIZE; num++) {
                    if (isValid(board, i, j, num)) { // Check if it's safe to place this number
                        board[i][j] = num;
                        if (solveSudoku(board)) return 1; // Recursively solve the Sudoku board
                        board[i][j] = 0; // Backtrack by resetting the cell value
                    }
                }
                return 0; // If no valid number can be placed, backtrack
            }
        }
    }
    return 1; // If all cells are filled, the Sudoku board is solved
}

// Function to print the Sudoku board
void printSudoku(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%d ", board[i][j]);
            if ((j + 1) % 3 == 0 && j < BOARD_SIZE - 1) printf("| ");
        }
        printf("\n");
        if ((i + 1) % 3 == 0 && i < BOARD_SIZE - 1) {
            for (int k = 0; k < BOARD_SIZE * 2 + 1; k++) printf("-");
            printf("\n");
        }
    }
}

// Main function to test the Sudoku solver
int main() {
    int board[BOARD_SIZE][BOARD_SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(board)) {
        printf("Solved Sudoku board:\n");
        printSudoku(board);
    } else {
        printf("No solution exists.\n");
    }

    return 0;
}