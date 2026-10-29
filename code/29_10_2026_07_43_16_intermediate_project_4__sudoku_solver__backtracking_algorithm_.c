#include <stdio.h>
#include <stdbool.h>

// Function to check if it's safe to place number in the given position
bool isValid(int board[9][9], int row, int col, int num) {
    // Check this row on this column
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num) return false;
    }
    
    // Check this column on this row
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == num) return false;
    }
    
    // Check the box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[startRow + i][startCol + j] == num) return false;
        }
    }
    
    return true;
}

// Function to solve Sudoku
bool solveSudoku(int board[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isValid(board, i, j, num)) {
                        board[i][j] = num;
                        if (solveSudoku(board)) return true;
                        else board[i][j] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// Function to print Sudoku
void printSudoku(int board[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", board[i][j]);
            if ((j + 1) % 3 == 0 && j != 8) printf("| ");
        }
        printf("\n");
        if ((i + 1) % 3 == 0 && i != 8) printf("--------------------\n");
    }
}

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
        printSudoku(board);
    } else {
        printf("No solution exists\n");
    }
    
    return 0;
}