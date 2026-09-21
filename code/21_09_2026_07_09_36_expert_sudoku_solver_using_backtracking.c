Here is the C code for the Sudoku Solver using Backtracking:

```c
#include <stdio.h>
#include <stdbool.h>

// Function to check if a number can be placed at a given position
bool isValid(int board[9][9], int row, int col, int num) {
    // Check the row
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num)
            return false;
    }

    // Check the column
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == num)
            return false;
    }

    // Check the box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num)
                return false;
        }
    }

    return true;
}

// Function to solve the Sudoku board
bool solveSudoku(int board[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0) { // Found an empty cell
                for (int num = 1; num <= 9; num++) {
                    if (isValid(board, i, j, num)) { // Check if the number can be placed here
                        board[i][j] = num;
                        if (solveSudoku(board)) // Recursively call solveSudoku to fill in the rest of the board
                            return true;
                        else
                            board[i][j] = 0; // Backtrack and try another number
                    }
                }
                return false; // No number can be placed here, so backtrack
            }
        }
    }
    return true; // The board is completely filled in
}

// Function to print the Sudoku board
void printSudoku(int board[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", board[i][j]);
            if ((j + 1) % 3 == 0 && j < 8)
                printf("| ");
        }
        printf("\n");
        if ((i + 1) % 3 == 0 && i < 8)
            for (int j = 0; j < 9; j++) {
                printf("---");
                if (j == 8)
                    printf("\n");
                else
                    printf("--- ");
            }
    }
}

// Main function to test the Sudoku solver
int main() {
    int board[9][9] = {
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
        printf("Solution:\n");
        printSudoku(board);
    } else
        printf("No solution exists.\n");

    return 0;
}

```