#include <iostream>
#include <cstdlib>
using namespace std;

const int SIZE = 3; // Size of Tic Tac Toe board
char board[SIZE][SIZE]; // Game board
bool gameOver = false; // Flag to check if game is over
int currentPlayer = 1; // Current player (1 for human, 2 for computer)

void printBoard() {
    cout << "  0 1 2" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << i << " ";
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isValidMove(int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        return false;
    }
    if (board[row][col] != ' ') {
        return false;
    }
    return true;
}

int computerMove() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                return 1;
            }
        }
    }
    return -1;
}

void playGame() {
    while (!gameOver) {
        printBoard();
        int row, col;
        cout << "Enter your move (row and column): ";
        cin >> row >> col;
        if (!isValidMove(row, col)) {
            cout << "Invalid move. Try again." << endl;
            continue;
        }
        board[row][col] = 'X';
        if (checkWin()) {
            gameOver = true;
            printBoard();
            cout << "You won!" << endl;
        } else if (!hasEmptySpace()) {
            int result = computerMove();
            if (result == -1) {
                gameOver = true;
                printBoard();
                cout << "Computer won. Better luck next time!" << endl;
            }
        }
    }
}

bool hasEmptySpace() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                return true;
            }
        }
    }
    return false;
}

bool checkWin() {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return true;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0])) {
        return true;
    }
    return false;
}

int main() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
    playGame();
    return 0;
}