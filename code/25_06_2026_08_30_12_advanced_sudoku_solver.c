#include <stdio.h>
#include <stdlib.h>

// Structure to represent a Sudoku puzzle cell
typedef struct {
    int value;
    int isFixed; // 1 if the cell has a fixed value, 0 otherwise
} Cell;

// Function to print the Sudoku puzzle
void printPuzzle(Cell** puzzle, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (puzzle[i][j].isFixed) {
                printf("%d ", puzzle[i][j].value);
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

// Function to check if a given value can be placed in the cell
int isValid(Cell** puzzle, int row, int col, int val, int size) {
    // Check row
    for (int i = 0; i < size; i++) {
        if (puzzle[row][i].value == val && puzzle[row][i].isFixed) {
            return 0;
        }
    }

    // Check column
    for (int i = 0; i < size; i++) {
        if (puzzle[i][col].value == val && puzzle[i][col].isFixed) {
            return 0;
        }
    }

    // Check box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzle[startRow + i][startCol + j].value == val && puzzle[startRow + i][startCol + j].isFixed) {
                return 0;
            }
        }
    }

    return 1;
}

// Function to solve the Sudoku puzzle using backtracking
int solvePuzzle(Cell** puzzle, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (!puzzle[i][j].isFixed) {
                for (int k = 1; k <= size; k++) {
                    if (isValid(puzzle, i, j, k, size)) {
                        puzzle[i][j].value = k;
                        puzzle[i][j].isFixed = 1;
                        if (solvePuzzle(puzzle, size)) {
                            return 1;
                        }
                        puzzle[i][j].isFixed = 0;
                        for (int l = k - 1; l >= 1; l--) {
                            puzzle[i][j].value = l;
                            if (isValid(puzzle, i, j, l, size)) {
                                puzzle[i][j].value = k;
                                puzzle[i][j].isFixed = 1;
                                return solvePuzzle(puzzle, size);
                            }
                        }
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

// Main function to test the Sudoku solver
int main() {
    // Define a sample Sudoku puzzle
    Cell** puzzle = (Cell**)malloc(9 * sizeof(Cell*));
    for (int i = 0; i < 9; i++) {
        puzzle[i] = (Cell*)malloc(9 * sizeof(Cell));
    }
    puzzle[0][0].value = 5;
    puzzle[0][1].value = 3;
    puzzle[0][2].value = 4;
    puzzle[0][3].value = 7;
    puzzle[0][4].value = 2;
    puzzle[0][5].value = 9;
    puzzle[0][6].value = 1;
    puzzle[0][7].value = 8;
    puzzle[0][8].value = 3;
    puzzle[1][0].value = 9;
    puzzle[1][1].value = 7;
    puzzle[1][2].value = 1;
    puzzle[1][3].value = 5;
    puzzle[1][4].value = 4;
    puzzle[1][5].value = 8;
    puzzle[1][6].value = 3;
    puzzle[1][7].value = 2;
    puzzle[1][8].value = 6;
    puzzle[2][0].value = 1;
    puzzle[2][1].value = 4;
    puzzle[2][2].value = 8;
    puzzle[2][3].value = 3;
    puzzle[2][4].value = 9;
    puzzle[2][5].value = 6;
    puzzle[2][6].value = 7;
    puzzle[2][7].value = 2;
    puzzle[2][8].value = 5;

    // Solve the Sudoku puzzle
    if (solvePuzzle(puzzle, 9)) {
        printPuzzle(puzzle, 9);
    } else {
        printf("No solution found.\n");
    }

    // Free memory
    for (int i = 0; i < 9; i++) {
        free(puzzle[i]);
    }
    free(puzzle);

    return 0;
}