#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Sudoku board class representation
class SudokuBoard {
public:
    vector<vector<int>> grid;
    int size;

    // Constructor to initialize Sudoku board
    SudokuBoard(int n) : size(n), grid(n, vector<int>(n)) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                grid[i][j] = 0;
    }

    // Function to print Sudoku board
    void printBoard() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j)
                cout << grid[i][j] << " ";
            cout << endl;
        }
    }

    // Function to check if Sudoku board is solved
    bool isSolved() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j)
                if (grid[i][j] == 0)
                    return false;
        }
        return true;
    }

    // Function to solve Sudoku board using backtracking algorithm
    bool solveSudoku() {
        int emptyCellCount = 0;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j)
                if (grid[i][j] == 0)
                    emptyCellCount++;
        }

        if (emptyCellCount == 0)
            return true;

        int row, col;
        // Find the first empty cell
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (grid[i][j] == 0) {
                    row = i;
                    col = j;
                    break;
                }
            }
            if (col != 0)
                break;
        }

        // Try numbers from 1 to n for the empty cell
        for (int num = 1; num <= size; ++num) {
            if (isValidMove(row, col, num)) {
                grid[row][col] = num;

                if (solveSudoku())
                    return true;

                grid[row][col] = 0;
            }
        }

        return false;
    }

    // Function to check if a number can be placed at the given position
    bool isValidMove(int row, int col, int num) {
        for (int i = 0; i < size; ++i)
            if (grid[i][col] == num || grid[row][i] == num)
                return false;

        int startRow = row - (row % 3), startCol = col - (col % 3);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (grid[startRow + i][startCol + j] == num)
                    return false;
            }
        }

        return true;
    }
};

// Function to generate Sudoku board
SudokuBoard generateBoard(int n) {
    SudokuBoard sudoku(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (rand() % 2 == 1)
                sudoku.grid[i][j] = rand() % (n - 1) + 1;

    return sudoku;
}

// Main function
int main() {
    srand(time(0)); // Initialize random seed

    int n = 9; // Size of Sudoku board
    SudokuBoard sudoku = generateBoard(n);

    if (!sudoku.solveSudoku()) {
        cout << "No solution exists for this Sudoku puzzle." << endl;
    } else {
        sudoku.printBoard();
    }

    return 0;
}