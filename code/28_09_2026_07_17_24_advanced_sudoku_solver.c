#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Sudoku board as a 2D array of integers
#define BOARD_SIZE 9
int board[BOARD_SIZE][BOARD_SIZE];

// Function to print the Sudoku board
void printBoard() {
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

// Function to check if a number can be placed in the given position
int isValid(int row, int col, int num) {
    // Check the row and column for the number
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[row][i] == num || board[i][col] == num)
            return 0;
    }
    // Check the box for the number
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[startRow + i][startCol + j] == num)
                return 0;
        }
    }
    return 1;
}

// Function to solve the Sudoku puzzle
void solveSudoku() {
    int row, col;
    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= BOARD_SIZE; num++) {
                    if (isValid(row, col, num)) {
                        board[row][col] = num;
                        solveSudoku();
                        if (board[row][col] != num)
                            return;
                    }
                }
                board[row][col] = 0;
                return;
            }
        }
    }
    printBoard();
}

int main() {
    // Initialize the Sudoku board with some values
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (i == 0 || i == 3 || i == 6) {
                if (j == 0 || j == 3 || j == 6)
                    board[i][j] = 0;
                else
                    board[i][j] = i + 1;
            } else if (i == 8) {
                if (j == 4)
                    board[i][j] = 5;
                else
                    board[i][j] = 0;
            } else
                board[i][j] = 0;
        }
    }

    // Solve the Sudoku puzzle
    solveSudoku();

    return 0;
}