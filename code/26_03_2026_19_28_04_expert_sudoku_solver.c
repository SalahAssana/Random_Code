#include <stdio.h>
#include <stdlib.h>

// Sudoku cell values
#define EMPTY 0
#define POSSIBLE 1
#define FIXED 2

// Function to print the Sudoku grid
void printGrid(int **grid) {
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

// Function to check if a number is possible in the Sudoku cell
int isValid(int **grid, int row, int col, int num) {
    // Check rows
    for (int i = 0; i < 9; i++) {
        if (grid[row][i] == num) return 0;
    }

    // Check columns
    for (int i = 0; i < 9; i++) {
        if (grid[i][col] == num) return 0;
    }

    // Check box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] == num) return 0;
        }
    }

    return 1;
}

// Function to solve the Sudoku puzzle
void solveSudoku(int **grid) {
    int row, col;
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (grid[row][col] == EMPTY) {
                for (int num = 1; num <= 9; num++) {
                    if (isValid(grid, row, col, num)) {
                        grid[row][col] = num;
                        solveSudoku(grid);
                        if (!grid[row][col]) break;
                    }
                }
                return;
            }
        }
    }
}

// Function to clear the Sudoku grid
void clearGrid(int **grid) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            grid[i][j] = EMPTY;
        }
    }
}

// Main function
int main() {
    int **grid = (int **)malloc(9 * sizeof(int *));
    for (int i = 0; i < 9; i++) {
        grid[i] = (int *)malloc(9 * sizeof(int));
    }

    // Initialize the Sudoku grid with a puzzle
    clearGrid(grid);
    grid[0][1] = FIXED;
    grid[0][2] = FIXED;
    grid[0][3] = FIXED;
    grid[1][4] = FIXED;
    grid[2][5] = FIXED;
    grid[3][6] = FIXED;
    grid[4][7] = FIXED;
    grid[5][8] = FIXED;

    // Solve the Sudoku puzzle
    solveSudoku(grid);

    // Print the solved Sudoku grid
    printGrid(grid);

    for (int i = 0; i < 9; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}