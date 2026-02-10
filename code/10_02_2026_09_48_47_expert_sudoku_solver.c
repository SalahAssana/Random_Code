#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 9
#define EMPTY -1

// Sudoku board representation as an array of arrays
int board[SIZE][SIZE];

// Function to check if a number is valid in a given position
bool isValid(int row, int col, int num) {
    // Check the number in the current row
    for (int i = 0; i < SIZE; i++) {
        if (board[row][i] == num)
            return false;
    }

    // Check the number in the current column
    for (int i = 0; i < SIZE; i++) {
        if (board[i][col] == num)
            return false;
    }

    // Check the number in the current box
    int startRow = row - row % 3,
        startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num)
                return false;
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int row, int col) {
    // If we've filled in the entire board, we're done!
    if (row == SIZE - 1 && col == SIZE) {
        return true;
    }

    // If we've reached the end of a row and haven't filled it in, move to the next row
    if (col == SIZE) {
        row++;
        col = 0;
    }

    // If this spot is empty, try filling it with a number from 1-9
    if (board[row][col] == EMPTY) {
        for (int num = 1; num <= SIZE; num++) {
            if (isValid(row, col, num)) {
                board[row][col] = num;
                // Recursively fill in the rest of the board
                if (solveSudoku(row, col + 1))
                    return true;

                // If that didn't work, backtrack and try a different number
                board[row][col] = EMPTY;
            }
        }

        return false;
    }

    // If this spot is already filled in, move to the next one
    return solveSudoku(row, col + 1);
}

// Function to print the Sudoku board
void printBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

// Main function to solve and print the Sudoku puzzle
int main() {
    // Initialize an empty board
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }

    // Fill in some sample data to test the puzzle
    board[0][0] = 5;
    board[0][1] = 3;
    board[0][2] = 4;
    board[1][0] = 6;
    board[1][1] = 7;
    board[1][2] = 8;
    board[2][0] = EMPTY;
    board[2][1] = 9;
    board[2][2] = EMPTY;

    // Solve the Sudoku puzzle
    if (solveSudoku(0, 0)) {
        printBoard();
    } else {
        printf("No solution found.\n");
    }

    return 0;
}