#include <stdio.h>
#include <stdlib.h>

// Sudoku board structure
typedef struct {
    int board[9][9];
} Sudoku;

// Function to print Sudoku board
void printBoard(Sudoku sudoku) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", sudoku.board[i][j]);
        }
        printf("\n");
    }
}

// Function to check if number can be placed at position
int isValid(Sudoku sudoku, int row, int col, int num) {
    // Check row
    for (int i = 0; i < 9; i++) {
        if (sudoku.board[row][i] == num)
            return 0;
    }
    // Check column
    for (int i = 0; i < 9; i++) {
        if (sudoku.board[i][col] == num)
            return 0;
    }
    // Check box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku.board[startRow + i][startCol + j] == num)
                return 0;
        }
    }
    return 1;
}

// Function to solve Sudoku using backtracking
Sudoku* solveSudoku(Sudoku sudoku) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku.board[i][j] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isValid(sudoku, i, j, num)) {
                        sudoku.board[i][j] = num;
                        Sudoku* result = solveSudoku(sudoku);
                        if (result != NULL)
                            return result;
                        sudoku.board[i][j] = 0;
                    }
                }
                return NULL; // No solution
            }
        }
    }
    return &sudoku; // Solution found
}

int main() {
    Sudoku sudoku;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if ((i == 0 && j < 3) || (i > 2 && i < 6 && j < 3) || (i == 8 && j < 3))
                sudoku.board[i][j] = 5;
            else if ((i == 1 && j < 3) || (i > 4 && i < 8 && j < 3) || (i == 7 && j < 3))
                sudoku.board[i][j] = 3;
            else if ((i == 2 && j < 3) || (i > 5 && i < 9 && j < 3) || (i == 6 && j < 3))
                sudoku.board[i][j] = 7;
            else if ((i == 0 && j >= 3 && j < 6) || (i > 2 && i < 8 && j >= 3 && j < 6) || (i == 8 && j >= 3 && j < 6))
                sudoku.board[i][j] = 9;
            else if ((i == 1 && j >= 3 && j < 6) || (i > 4 && i < 9 && j >= 3 && j < 6) || (i == 7 && j >= 3 && j < 6))
                sudoku.board[i][j] = 8;
            else if ((i == 2 && j >= 3 && j < 6) || (i > 5 && i < 9 && j >= 3 && j < 6) || (i == 6 && j >= 3 && j < 6))
                sudoku.board[i][j] = 4;
            else if ((i == 0 && j >= 6) || (i > 2 && i < 8 && j >= 6) || (i == 8 && j >= 6))
                sudoku.board[i][j] = 1;
            else if ((i == 1 && j >= 6) || (i > 4 && i < 9 && j >= 6) || (i == 7 && j >= 6))
                sudoku.board[i][j] = 2;
            else if ((i == 2 && j >= 6) || (i > 5 && i < 9 && j >= 6) || (i == 6 && j >= 6))
                sudoku.board[i][j] = 6;
        }
    }
    Sudoku* result = solveSudoku(sudoku);
    if (result != NULL)
        printBoard(*result);
    else
        printf("No solution found.\n");
    return 0;
}