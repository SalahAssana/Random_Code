#include <stdio.h>
#include <stdlib.h>

// Sudoku grid structure
typedef struct {
    int grid[9][9];
} SudokuGrid;

// Function to check if a number can be placed in a given position
int isValidPosition(SudokuGrid* grid, int row, int col, int num) {
    // Check the row
    for (int i = 0; i < 9; i++) {
        if (grid->grid[row][i] == num) return 0;
    }

    // Check the column
    for (int i = 0; i < 9; i++) {
        if (grid->grid[i][col] == num) return 0;
    }

    // Check the box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid->grid[startRow + i][startCol + j] == num) return 0;
        }
    }

    return 1;
}

// Function to solve the Sudoku puzzle using backtracking
void solveSudoku(SudokuGrid* grid, int row, int col) {
    // If we've reached the end of the grid and it's solved, print the solution
    if (row == 9 - 1 && col == 0) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                printf("%d ", grid->grid[i][j]);
            }
            printf("\n");
        }
        exit(0);
    }

    // If we've reached the end of a row and there are no more numbers to place, backtrack
    if (col == 9) {
        row++;
        col = 0;
    }

    // Try each possible number in the current position
    for (int num = 1; num <= 9; num++) {
        if (isValidPosition(grid, row, col, num)) {
            grid->grid[row][col] = num;

            // Recursively try to solve the rest of the puzzle
            solveSudoku(grid, row, col + 1);

            // If we couldn't place any numbers in this position, backtrack and reset it
            if (row < 9) {
                for (int i = 0; i < 9; i++) {
                    grid->grid[row][i] = 0;
                }
                row++;
                col = 0;
            }
        }
    }
}

// Main function to solve a Sudoku puzzle
int main() {
    // Initialize the Sudoku grid with some example values (0 means empty)
    SudokuGrid sudokuGrid = {
        {{5, 3, 0, 7, 8, 6, 0, 0, 0},
         {6, 0, 0, 1, 9, 5, 0, 0, 0},
         {8, 9, 4, 0, 0, 0, 7, 0, 0},
         {0, 2, 0, 3, 0, 6, 0, 1, 0},
         {0, 0, 0, 8, 5, 0, 4, 0, 0},
         {7, 1, 3, 9, 2, 0, 6, 0, 0},
         {0, 6, 0, 0, 0, 0, 2, 8, 0},
         {0, 0, 0, 4, 3, 0, 9, 5, 0},
         {0, 0, 0, 0, 1, 0, 0, 7, 8}}
    };

    // Solve the Sudoku puzzle
    solveSudoku(&sudokuGrid, 0, 0);

    return 0;
}