#include <stdio.h>
#include <stdlib.h>

// Sudoku cell type
typedef enum { EMPTY, FILLED } Cell;

// Sudoku board type
typedef struct {
    int board[9][9];
    int solved;
} Board;

// Function to check if a number is valid in the given row and column
int isValid(Board *board, int row, int col, int num) {
    // Check the row
    for (int i = 0; i < 9; i++) {
        if (board->board[row][i] == num)
            return 0;
    }
    
    // Check the column
    for (int i = 0; i < 9; i++) {
        if (board->board[i][col] == num)
            return 0;
    }
    
    // Check the 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board->board[startRow + i][startCol + j] == num)
                return 0;
        }
    }
    
    return 1;
}

// Function to solve the Sudoku board using backtracking
void solveSudoku(Board *board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board->board[row][col] == 0) { // If the cell is empty
                for (int num = 1; num <= 9; num++) { // Try each number from 1 to 9
                    if (isValid(board, row, col, num)) { // Check if the number is valid
                        board->board[row][col] = num; // Fill the cell with the number
                        solveSudoku(board); // Recursively call the function to fill the rest of the board
                        if (!board->solved) { // If the board is not solved, reset the cell and backtrack
                            board->board[row][col] = 0;
                            return; 
                        }
                    } else {
                        board->board[row][col] = 0; // Reset the cell if the number is not valid
                    }
                }
            }
        }
    }
    board->solved = 1; // Set the solved flag to 1 when the board is solved
}

// Function to print the Sudoku board
void printBoard(Board *board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", board->board[i][j]);
        }
        printf("\n");
    }
}

// Main function
int main() {
    Board sudoku;
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (row == 0 || row == 3 || row == 6) { // For the first, fourth and seventh rows
                sudoku.board[row][col] = 0; // Initialize with zeros
            } else if (col == 0 || col == 3 || col == 6) { // For the first, fourth and seventh columns
                sudoku.board[row][col] = 0; // Initialize with zeros
            } else {
                sudoku.board[row][col] = 1 + rand() % 9; // Randomly fill the rest of the board
            }
        }
    }
    
    solveSudoku(&sudoku);
    
    if (sudoku.solved) {
        printf("The solved Sudoku board:\n");
        printBoard(&sudoku);
    } else {
        printf("No solution found.\n");
    }
    
    return 0;
}