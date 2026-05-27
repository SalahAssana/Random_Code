#include <iostream>
#include <string>

using namespace std;

// Function to draw the Tic-Tac-Toe board
void drawBoard(char board[3][3]) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if the game is over
bool gameOver(char board[3][3], char player) {
    // Check rows
    for(int i = 0; i < 3; i++) {
        bool allEqual = true;
        for(int j = 0; j < 3; j++) {
            if(board[i][j] != player) {
                allEqual = false;
                break;
            }
        }
        if(allEqual) return true;
    }

    // Check columns
    for(int i = 0; i < 3; i++) {
        bool allEqual = true;
        for(int j = 0; j < 3; j++) {
            if(board[j][i] != player) {
                allEqual = false;
                break;
            }
        }
        if(allEqual) return true;
    }

    // Check diagonals
    bool allEqual1 = true, allEqual2 = true;
    for(int i = 0; i < 3; i++) {
        if(board[i][i] != player) {
            allEqual1 = false;
            break;
        }
        if(board[i][2-i] != player) {
            allEqual2 = false;
            break;
        }
    }
    return allEqual1 || allEqual2;
}

// Function to make a move for the AI
void aiMove(char board[3][3], char player, int &x, int &y) {
    // Check if the AI can win
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == ' ') {
                board[i][j] = player;
                if(gameOver(board, player)) {
                    x = i; y = j;
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // Check if the user is going to win
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == ' ') {
                board[i][j] = player;
                if(gameOver(board, 'O')) { // Assuming the user is 'O'
                    x = i; y = j;
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // Make a random move
    int r = rand() % 3;
    for(int i = 0; i < 3; i++) {
        if(board[r][i] == ' ') {
            x = r; y = i;
            return;
        }
    }
}

int main() {
    srand(time(0)); // Seed the random number generator

    char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    char player = 'O'; // Initial player is 'O'

    int x, y;

    while(true) {
        drawBoard(board);
        cout << "Enter your move (1-9): ";
        int move;
        cin >> move;
        board[move/3 - 1][move%3] = player;

        if(gameOver(board, player)) {
            drawBoard(board);
            cout << "You won! Congratulations!" << endl;
            break;
        }

        aiMove(board, 'X', x, y);
        drawBoard(board);
        board[x][y] = 'X';

        if(gameOver(board, 'X')) {
            drawBoard(board);
            cout << "AI won. Better luck next time!" << endl;
            break;
        }
    }

    return 0;
}