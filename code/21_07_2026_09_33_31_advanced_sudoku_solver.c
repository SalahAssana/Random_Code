#include <stdio.h>
#include <stdbool.h>

// Sudoku grid size (9x9)
#define SIZE 9

// Function to check if a number is valid in the given row and column
bool isValid(int board[SIZE][SIZE], int num, int row, int col) {
    // Check the row
    for (int i = 0; i < SIZE; i++) {
        if (board[row][i] == num) return false;
    }

    // Check the column
    for (int i = 0; i < SIZE; i++) {
        if (board[i][col] == num) return false;
    }

    // Check the box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[startRow + i][startCol + j] == num) return false;
        }
    }

    // If no conflicts, then the number is valid
    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) { // Found an empty cell
                for (int num = 1; num <= SIZE; num++) {
                    if (isValid(board, num, row, col)) {
                        board[row][col] = num;
                        if (solveSudoku(board)) return true;
                        else {
                            board[row][col] = 0; // Backtrack
                        }
                    }
                }
                return false; // No valid number found, backtrack
            }
        }
    }
    return true; // Puzzle solved
}

// Function to print the Sudoku grid
void printSudoku(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

// Main function to test the Sudoku solver
int main() {
    int sudoku[SIZE][SIZE] = {
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

    if (solveSudoku(sudoku)) {
        printf("Solution found:\n");
        printSudoku(sudoku);
    } else {
        printf("No solution found.\n");
    }

    return 0;
}