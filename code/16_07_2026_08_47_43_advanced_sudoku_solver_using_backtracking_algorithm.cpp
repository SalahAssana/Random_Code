#include <iostream>
#include <vector>

using namespace std;

class Sudoku {
public:
    vector<vector<int>> board;
    int size;

    Sudoku(int n) : size(n), board(n, vector<int>(n)) {}

    bool isSafe(int row, int col, int num) {
        for (int i = 0; i < size; i++) {
            if (board[row][i] == num)
                return false;
        }
        for (int i = 0; i < size; i++) {
            if (board[i][col] == num)
                return false;
        }
        int startRow = row - row % 3, startCol = col - col % 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[startRow + i][startCol + j] == num)
                    return false;
            }
        }
        return true;
    }

    bool solve() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] == 0) {
                    for (int num = 1; num <= size; num++) {
                        if (isSafe(i, j, num)) {
                            board[i][j] = num;
                            if (solve())
                                return true;
                            else
                                board[i][j] = 0;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Sudoku sudoku(9);
    // Add your puzzle here
    sudoku.board[0][0] = 5;
    sudoku.board[1][2] = 3;
    sudoku.board[4][5] = 7;
    sudoku.board[8][6] = 9;
    sudoku.board[4][3] = 4;
    sudoku.board[3][1] = 8;
    sudoku.board[0][8] = 6;
    sudoku.board[9][0] = 2;
    sudoku.board[7][5] = 1;
    sudoku.board[5][3] = 9;
    sudoku.board[6][1] = 4;
    sudoku.board[8][2] = 3;

    if (sudoku.solve()) {
        sudoku.print();
    } else {
        cout << "No solution exists" << endl;
    }
    return 0;
}