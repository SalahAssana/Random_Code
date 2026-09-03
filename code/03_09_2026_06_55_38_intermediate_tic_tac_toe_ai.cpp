#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to check if a player has won
bool isWinner(vector<vector<char>>& board, char player) {
    // Check rows and columns for winning combinations
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }

    // Check diagonals for winning combinations
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }

    return false;
}

// Function to check if the game is a draw
bool isDraw(vector<vector<char>>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }

    return true;
}

// Function to make a computer move
void makeComputerMove(vector<vector<char>>& board, char player) {
    // Find the first empty space in the bottom row
    for (int i = 0; i < 3; ++i) {
        if (board[2][i] == ' ') {
            board[2][i] = player;
            return;
        }
    }

    // If no empty spaces are found in the bottom row, make a random move
    int x, y;
    do {
        x = rand() % 3;
        y = rand() % 3;
    } while (board[x][y] != ' ');

    board[x][y] = player;
}

int main() {
    srand(time(0));

    vector<vector<char>> board(3, vector<char>(3));
    char currentPlayer = 'X';

    cout << "Tic Tac Toe AI\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = ' ';
            cout << " " << i + 1 << " ";
        }
        cout << "\n";
    }

    while (true) {
        // Player move
        int x, y;
        do {
            cin >> x >> y;
        } while (!(x >= 1 && x <= 3 && y >= 1 && y <= 3));

        board[x - 1][y - 1] = currentPlayer;

        if (isWinner(board, currentPlayer)) {
            cout << "Player wins!\n";
            return 0;
        }

        if (isDraw(board)) {
            cout << "It's a draw!\n";
            return 0;
        }

        // Computer move
        makeComputerMove(board, 'O');

        // Print the updated board
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << " " << board[i][j] << " ";
            }
            cout << "\n";
        }

        // Switch players
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}