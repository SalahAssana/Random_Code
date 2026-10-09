#include <stdio.h>
#include <stdlib.h>

// Define a struct to represent a Sudoku board cell
typedef struct {
    int value;
    int isFixed;
} Cell;

// Function to check if a number can be placed in a given cell
int isValid(int row, int col, int num, Cell sudoku[9][9]) {
    // Check the row
    for (int i = 0; i < 9; i++) {
        if (sudoku[row][i].value == num) {
            return 0;
        }
    }

    // Check the column
    for (int i = 0; i < 9; i++) {
        if (sudoku[i][col].value == num) {
            return 0;
        }
    }

    // Check the box
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[startRow + i][startCol + j].value == num) {
                return 0;
            }
        }
    }

    return 1;
}

// Function to solve the Sudoku puzzle
void solveSudoku(Cell sudoku[9][9]) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (!sudoku[row][col].isFixed) {
                for (int num = 1; num <= 9; num++) {
                    if (isValid(row, col, num, sudoku)) {
                        sudoku[row][col].value = num;
                        sudoku[row][col].isFixed = 1;

                        // Recursively call the function to solve the rest of the board
                        solveSudoku(sudoku);

                        // If the Sudoku is solved, return
                        if (sudoku[0][0].value != 0) {
                            return;
                        }

                        // If the number cannot be placed in this cell, reset it and backtrack
                        sudoku[row][col].isFixed = 0;
                    }
                }

                // If no number can be placed in this cell, backtrack and reset the entire row
                if (sudoku[0][col].value == 0) {
                    for (int i = 0; i < 9; i++) {
                        sudoku[row][i].isFixed = 0;
                    }
                }
            }
        }
    }
}

// Function to print the Sudoku board
void printSudoku(Cell sudoku[9][9]) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            printf("%d ", sudoku[row][col].value);
        }
        printf("\n");
    }
}

// Function to initialize the Sudoku board with a given puzzle
void initSudoku(Cell sudoku[9][9], char puzzle[9][9]) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (puzzle[row][col] != '.') {
                sudoku[row][col].value = puzzle[row][col] - '0';
                sudoku[row][col].isFixed = 1;
            } else {
                sudoku[row][col].value = 0;
                sudoku[row][col].isFixed = 0;
            }
        }
    }
}

int main() {
    char puzzle[9][9] = {
        ".5..7....",
        "4...3.2..",
        "...6.....",
        "..8.1.4.",
        "...9.....",
        "3.......",
        "...6.5...",
        "...4.2.1",
        "........."
    };

    Cell sudoku[9][9];

    initSudoku(sudoku, puzzle);

    solveSudoku(sudoku);

    printSudoku(sudoku);

    return 0;
}