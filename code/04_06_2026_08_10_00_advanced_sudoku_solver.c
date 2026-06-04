#include <stdio.h>
#include <stdlib.h>

// Define the size of the Sudoku grid
#define SIZE 9

// Define the possible values for each cell (0-9)
typedef enum { EMPTY = 0, ONE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, SEVEN = 7, EIGHT = 8, NINE = 9 } Value;

// Define the Sudoku grid as a 2D array
typedef int Grid[SIZE][SIZE];

// Function to print the Sudoku grid
void printGrid(Grid grid) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

// Function to check if a number is valid in the given position
bool isValidPosition(int row, int col, Value num, Grid grid) {
    // Check rows
    for (int i = 0; i < SIZE; i++) {
        if (grid[row][i] == num) return false;
    }

    // Check columns
    for (int i = 0; i < SIZE; i++) {
        if (grid[i][col] == num) return false;
    }

    // Check 3x3 sub-grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] == num) return false;
        }
    }

    return true;
}

// Recursive function to solve the Sudoku puzzle
bool solveSudoku(Grid grid, int row, int col) {
    // If we've reached the end of the grid, it's solved!
    if (row >= SIZE && col >= SIZE) return true;

    // If we've reached a cell that's not empty, move on to the next one
    if (col >= SIZE) {
        row++;
        col = 0;
    }

    // Check if the current cell is already filled
    if (grid[row][col] != EMPTY) {
        return solveSudoku(grid, row, col + 1);
    }

    // Try each possible value for the current cell
    for (Value num = ONE; num <= NINE; num++) {
        if (isValidPosition(row, col, num, grid)) {
            grid[row][col] = num;
            if (solveSudoku(grid, row, col + 1)) return true;
        }
    }

    // If we've tried all possible values and none of them worked,
    // it means the puzzle is unsolvable
    grid[row][col] = EMPTY;
    return false;
}

// Main function to solve a Sudoku puzzle
int main() {
    Grid grid = {{5, 3, EMPTY, EMPTY, 7, EMPTY, EMPTY, EMPTY, EMPTY},
                 {6, EMPTY, EMPTY, 1, 9, 5, EMPTY, EMPTY, EMPTY},
                 {EMPTY, 9, 8, EMPTY, EMPTY, EMPTY, EMPTY, 6, EMPTY},
                 {1, 6, EMPTY, EMPTY, 1, EMPTY, 5, EMPTY, EMPTY},
                 {EMPTY, 1, EMPTY, EMPTY, 5, EMPTY, EMPTY, EMPTY, 9},
                 {7, EMPTY, EMPTY, 4, EMPTY, 8, EMPTY, EMPTY, EMPTY},
                 {EMPTY, 5, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 3, EMPTY},
                 {0, 7, EMPTY, EMPTY, 4, EMPTY, EMPTY, EMPTY, 2}};

    if (solveSudoku(grid, 0, 0)) {
        printGrid(grid);
    } else {
        printf("No solution found.\n");
    }

    return 0;
}