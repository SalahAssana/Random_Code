#include <stdio.h>
#include <stdlib.h>

#define SIZE 9
#define EMPTY -1

// Function to check if a number can be placed in given row and column
int isSafe(int board[SIZE][SIZE], int num, int row, int col) {
    // Check this row on this column
    for (int i = 0; i < SIZE; i++) {
        if (board[i][col] == num)
            return 0;
    }

    // Check this column on this row
    for (int i = 0; i < SIZE; i++) {
        if (board[row][i] == num)
            return 0;
    }

    // Check the box
    int startRow, startCol;

    if (row < 3)
        startRow = 0;
    else if (row < 6)
        startRow = 3;
    else
        startRow = 6;

    if (col < 3)
        startCol = 0;
    else if (col < 6)
        startCol = 3;
    else
        startCol = 6;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[startRow + i][startCol + j] == num)
                return 0;
        }
    }

    // If no conflict found, return 1
    return 1;
}

// Function to solve Sudoku using backtracking algorithm
int solveSudoku(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY) {
                for (int num = 1; num <= SIZE; num++) {
                    if (isSafe(board, num, i, j)) {
                        board[i][j] = num;
                        if (solveSudoku(board))
                            return 1;
                        else
                            board[i][j] = EMPTY;
                    }
                }
                return 0;
            }
        }
    }
    // If no empty cell is found, puzzle is solved
    return 1;
}

int main() {
    int board[SIZE][SIZE] = {
        {5,3,0,7,9,8,6,4,2},
        {6,7,0,1,5,4,3,9,8},
        {1,9,8,3,0,6,5,7,4},
        {8,5,0,6,1,3,4,2,9},
        {4,2,6,8,5,7,9,1,3},
        {7,1,3,9,6,8,2,4,5},
        {9,6,1,5,3,4,7,8,2},
        {3,4,8,2,1,5,6,9,7},
        {2,5,7,4,9,6,1,3,8}
    };

    if (solveSudoku(board)) {
        printf("Solved Sudoku:\n");
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                printf("%d ", board[i][j]);
            }
            printf("\n");
        }
    } else
        printf("No solution exists.\n");

    return 0;
}