#include <stdio.h>
#include <stdlib.h>

// Function to check if a number can be placed in a given position
int isSafe(int board[9][9], int row, int col, int num) {
    // Check the number in the row
    for (int x = 0; x < 9; x++) {
        if (board[row][x] == num)
            return 0;
    }
    // Check the number in the column
    for (int x = 0; x < 9; x++) {
        if (board[x][col] == num)
            return 0;
    }
    // Check the number in the box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num)
                return 0;
        }
    }
    return 1;
}

// Function to solve the Sudoku puzzle
void solveSudoku(int board[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(board, i, j, num)) {
                        board[i][j] = num;
                        solveSudoku(board);
                        if (!boardIsFull(board))
                            return;
                        board[i][j] = 0;
                    }
                }
                return;
            }
        }
    }
}

// Function to check if the Sudoku puzzle is full
int boardIsFull(int board[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0)
                return 0;
        }
    }
    return 1;
}

// Function to print the Sudoku puzzle
void printSudoku(int board[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
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
    solveSudoku(board);
    printSudoku(board);
    return 0;
}