#include <stdio.h>
#include <stdlib.h>

// Define the Sudoku board size (9x9)
#define BOARD_SIZE 9

// Function to print the Sudoku board
void print_board(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

// Function to check if a number can be placed in the given row and column
int is_valid(int board[BOARD_SIZE][BOARD_SIZE], int num, int row, int col) {
    // Check the number in the same row
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[row][i] == num) return 0;
    }

    // Check the number in the same column
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][col] == num) return 0;
    }

    // Check the number in the same 3x3 box
    int start_row = row - row % 3;
    int start_col = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[start_row + i][start_col + j] == num) return 0;
        }
    }

    return 1;
}

// Function to solve the Sudoku puzzle using backtracking
void solve_sudoku(int board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    // If we have filled the entire board, print it and exit
    if (row == BOARD_SIZE - 1 && col == BOARD_SIZE) {
        print_board(board);
        return;
    }

    // If we have reached the end of a row without filling the entire board, move to the next row
    if (col == BOARD_SIZE) {
        row++;
        col = 0;
    }

    // If the current cell is not empty, move to the next one
    if (board[row][col] != 0) {
        solve_sudoku(board, row, col + 1);
        return;
    }

    // Try numbers from 1 to 9 in the current cell
    for (int num = 1; num <= BOARD_SIZE; num++) {
        if (is_valid(board, num, row, col)) {
            board[row][col] = num;

            // Recursively solve the Sudoku puzzle with the updated board
            solve_sudoku(board, row, col + 1);

            // If we have filled the entire board, print it and exit
            if (row == BOARD_SIZE - 1 && col == BOARD_SIZE) {
                return;
            }

            // Backtrack by resetting the current cell to 0 and moving to the next one
            board[row][col] = 0;
            row++;
            col = 0;
        }
    }
}

int main() {
    int board[BOARD_SIZE][BOARD_SIZE] = {
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

    printf("Sudoku board before solving:\n");
    print_board(board);

    solve_sudoku(board, 0, 0);

    printf("\nSudoku board after solving:\n");
    print_board(board);

    return 0;
}