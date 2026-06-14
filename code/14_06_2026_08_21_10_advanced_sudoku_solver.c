#include <stdio.h>
#include <stdlib.h>

// Define the board size (9x9)
#define BOARD_SIZE 81

// Function to print the board
void printBoard(int board[BOARD_SIZE]) {
    int i;
    for(i = 0; i < 9; i++) {
        if(i % 3 == 0 && i != 0) printf("\n---------------------\n");
        for(int j = 0; j < 9; j++) {
            if(j % 3 == 0 && j != 0) printf(" | ");
            printf("%d ", board[i*9 + j]);
        }
        printf("\n");
    }
}

// Function to check if a number can be placed at a given position
int isValid(int board[BOARD_SIZE], int row, int col, int num) {
    // Check the row
    for(int i = 0; i < 9; i++) {
        if(board[i*9 + col] == num) return 0;
    }
    // Check the column
    for(int i = 0; i < 9; i++) {
        if(board[row*9 + i] == num) return 0;
    }
    // Check the box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[(startRow + i)*9 + (startCol + j)] == num) return 0;
        }
    }
    return 1;
}

// Function to solve the Sudoku puzzle using backtracking
int solveSudoku(int board[BOARD_SIZE]) {
    for(int i = 0; i < BOARD_SIZE; i++) {
        if(board[i] == 0) {
            for(int num = 1; num <= 9; num++) {
                if(isValid(board, i / 9, i % 9, num)) {
                    board[i] = num;
                    if(solveSudoku(board)) return 1;
                    else {
                        board[i] = 0;
                    }
                }
            }
            return 0;
        }
    }
    return 1;
}

int main() {
    int board[BOARD_SIZE] = {5,3,0,7,0,9,2,8,0,
                             6,0,0,1,9,5,0,0,0,
                             8,0,0,4,0,0,7,0,0,
                             0,6,0,2,0,0,0,9,0,
                             3,8,0,0,0,6,0,7,0,
                             0,2,0,0,0,0,4,0,9,
                             1,0,0,3,0,0,5,0,0,
                             0,9,0,0,8,0,0,6,0,
                             0,0,8,0,0,0,0,3,1};
    if(solveSudoku(board)) {
        printBoard(board);
    } else {
        printf("No solution exists.\n");
    }
    return 0;
}