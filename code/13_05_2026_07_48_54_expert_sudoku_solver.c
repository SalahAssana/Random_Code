Here is the C code for the Sudoku Solver:

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the size of the board (9x9)
#define SIZE 9

// Define the possible values for a cell (1-9)
#define POSSIBLE_VALUES 9

// Function to print the Sudoku board
void printBoard(int board[SIZE][SIZE]) {
    int i, j;
    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

// Function to check if a number is already present in the row
bool isPresentInRow(int board[SIZE][SIZE], int row, int num) {
    for(int i = 0; i < SIZE; i++) {
        if(board[row][i] == num) {
            return true;
        }
    }
    return false;
}

// Function to check if a number is already present in the column
bool isPresentInCol(int board[SIZE][SIZE], int col, int num) {
    for(int i = 0; i < SIZE; i++) {
        if(board[i][col] == num) {
            return true;
        }
    }
    return false;
}

// Function to check if a number is already present in the box
bool isPresentInBox(int board[SIZE][SIZE], int row, int col, int num) {
    int startRow = row - (row % 3);
    int startCol = col - (col % 3);

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i + startRow][j + startCol] == num) {
                return true;
            }
        }
    }
    return false;
}

// Function to check if a number can be placed in the cell
bool isValidMove(int board[SIZE][SIZE], int row, int col, int num) {
    // Check if the number is already present in the row or column
    if(isPresentInRow(board, row, num) || isPresentInCol(board, col, num)) {
        return false;
    }

    // Check if the number is already present in the box
    if(isPresentInBox(board, row, col, num)) {
        return false;
    }

    return true;
}

// Function to solve the Sudoku puzzle using backtracking algorithm
bool solveSudoku(int board[SIZE][SIZE]) {
    int i, j;

    // Find an empty cell (0)
    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            if(board[i][j] == 0) {
                return solveSudokuHelper(board, i, j);
            }
        }
    }

    // If no empty cell is found, then the board is solved
    return true;
}

// Helper function to solve the Sudoku puzzle using backtracking algorithm
bool solveSudokuHelper(int board[SIZE][SIZE], int row, int col) {
    if(row == SIZE - 1 && col == 0) {
        return true;
    }

    for(int num = 1; num <= POSSIBLE_VALUES; num++) {
        if(isValidMove(board, row, col, num)) {
            board[row][col] = num;

            // Check the next cell
            if(solveSudokuHelper(board, row + (col % SIZE == 0), col % SIZE == 0 ? 1 : col % SIZE + 1)) {
                return true;
            }

            // If the number cannot be placed in the next cell, then backtrack
            board[row][col] = 0;
        }
    }

    return false;
}

// Function to solve a Sudoku puzzle given an initial board
void solveSudokuPuzzle(int board[SIZE][SIZE]) {
    if(solveSudoku(board)) {
        printBoard(board);
    } else {
        printf("No solution exists for the given Sudoku puzzle.\n");
    }
}

int main() {
    int sudokuBoard[SIZE][SIZE] = {
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

    solveSudokuPuzzle(sudokuBoard);

    return 0;
}

```