#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// The game board
char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

// Function to draw the game board
void drawBoard() {
    cout << "  " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "  ---+---+---" << endl;
    cout << "  " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "  ---+---+---" << endl;
    cout << "  " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

// Function to check if the game is won
bool isWon(char player) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }

    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }

    return false;
}

// Function to check if the game is drawn
bool isDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] >= '1' && board[i][j] <= '9') {
                return false;
            }
        }
    }

    return true;
}

// Function to get the best move using minimax algorithm
int minimax(int depth, char player) {
    int bestMove = -1;

    // Check if the game is won or drawn
    if (isWon(player)) {
        return depth * 2 - 1; // Player has won, so return a high score
    } else if (isDraw()) {
        return 0; // Game is drawn, so return 0

    } else {
        int bestScore = -10000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] >= '1' && board[i][j] <= '9') {
                    // Make the move
                    board[i][j] = player == 'X' ? 'O' : 'X';
                    int score = minimax(depth + 1, player == 'X' ? 'O' : 'X');
                    if (player == 'X') { // If it's X's turn, check the best score
                        if (score > bestScore) {
                            bestScore = score;
                            bestMove = i * 3 + j; // Store the best move
                        }
                    } else { // If it's O's turn, check the worst score
                        if (score < bestScore) {
                            bestScore = score;
                            bestMove = i * 3 + j; // Store the best move
                        }
                    }

                    // Undo the move
                    board[i][j] = '1' + (i * 3 + j);
                }
            }
        }

        return bestScore;
    }
}

// Function to make the AI's move
void aiMove() {
    int move = minimax(0, 'X');
    cout << "AI moves: " << move << endl;
    board[move / 3][move % 3] = 'X';
}

int main() {
    char player;

    // Ask for the player's choice
    cout << "Do you want to play as X (1) or O (2)? ";
    cin >> player;

    while (!isDraw()) {
        drawBoard();
        if (player == '1') { // If it's X's turn
            int move;
            cout << "Enter your move: ";
            cin >> move;
            board[(move - 1) / 3][(move - 1) % 3] = player == '1' ? 'X' : 'O';
        } else { // If it's O's turn
            aiMove();
        }

        if (isWon(player)) {
            drawBoard();
            cout << "Player " << (player == '1' ? "X" : "O") << " wins!" << endl;
            break;
        }
    }

    drawBoard();
    if (!isDraw()) {
        cout << "It's a draw!" << endl;
    } else {
        cout << "The game is over." << endl;
    }

    return 0;
}