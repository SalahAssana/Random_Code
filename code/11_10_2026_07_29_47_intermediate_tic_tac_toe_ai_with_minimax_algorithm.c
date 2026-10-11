#include <stdio.h>
#include <stdlib.h>

// Define the game board as a 2D array
char gameBoard[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

// Function to draw the game board
void drawGameBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c | ", gameBoard[i][j]);
        }
        printf("\n");
        if (i < 2) {
            printf("---------\n");
        }
    }
}

// Function to handle user move
void makeUserMove(int position) {
    int row = position / 3;
    int col = position % 3;

    // Check if the position is empty
    if (gameBoard[row][col] != 'X' && gameBoard[row][col] != 'O') {
        gameBoard[row][col] = 'O';
    } else {
        printf("Invalid move, try again.\n");
        return;
    }
}

// Function to handle AI move using minimax algorithm
void makeAIMove() {
    int bestScore = -1000;
    int bestMove = 0;

    for (int i = 0; i < 9; i++) {
        int row = i / 3;
        int col = i % 3;

        // Check if the position is empty
        if (gameBoard[row][col] != 'X' && gameBoard[row][col] != 'O') {
            gameBoard[row][col] = 'X';

            int score = minimax(0, false);
            gameBoard[row][col] = 'O';

            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }

    makeUserMove(bestMove);
}

// Function to evaluate the game state using minimax algorithm
int minimax(int depth, bool isMaximizing) {
    int score;

    // Check for a win or draw
    if (hasWon('O')) {
        return -10 + depth;
    } else if (hasWon('X')) {
        return 10 - depth;
    } else if (isBoardFull()) {
        return 0;
    }

    if (isMaximizing) {
        score = -1000;

        for (int i = 0; i < 9; i++) {
            int row = i / 3;
            int col = i % 3;

            // Check if the position is empty
            if (gameBoard[row][col] != 'X' && gameBoard[row][col] != 'O') {
                gameBoard[row][col] = 'X';

                score = maximizedMinimax(0, false);
                gameBoard[row][col] = 'O';
            }
        }

        return score;
    } else {
        score = 1000;

        for (int i = 0; i < 9; i++) {
            int row = i / 3;
            int col = i % 3;

            // Check if the position is empty
            if (gameBoard[row][col] != 'X' && gameBoard[row][col] != 'O') {
                gameBoard[row][col] = 'O';

                score = minimizedMinimax(0, true);
                gameBoard[row][col] = 'X';
            }
        }

        return score;
    }
}

// Function to maximize the minimax algorithm
int maximizedMinimax(int depth, bool isMaximizing) {
    int score;

    // Check for a win or draw
    if (hasWon('O')) {
        return -10 + depth;
    } else if (hasWon('X')) {
        return 10 - depth;
    } else if (isBoardFull()) {
        return 0;
    }

    if (isMaximizing) {
        score = -1000;

        for (int i = 0; i < 9; i++) {
            int row = i / 3;
            int col = i % 3;

            // Check if the position is empty
            if (gameBoard[row][col] != 'X' && gameBoard[row][col] != 'O') {
                gameBoard[row][col] = 'X';

                score = maximizedMinimax(0, false);
                gameBoard[row][col] = 'O';
            }
        }

        return score;
    } else {
        score = 1000;

        for (int i = 0; i < 9; i++) {
            int row = i / 3;
            int col = i % 3;

            // Check if the position is empty
            if (gameBoard[row][col] != 'X' && gameBoard[row][col] != 'O') {
                gameBoard[row][col] = 'O';

                score = minimizedMinimax(0, true);
                gameBoard[row][col] = 'X';
            }
        }

        return score;
    }
}

// Function to minimize the minimax algorithm
int minimizedMinimax(int depth, bool isMaximizing) {
    int score;

    // Check for a win or draw
    if (hasWon('O')) {
        return -10 + depth;
    } else if (hasWon('X')) {
        return 10 - depth;
    } else if (isBoardFull()) {
        return 0;
    }

    if (!isMaximizing) {
        score = -1000;

        for (int i = 0; i < 9; i++) {
            int row = i / 3;
            int col = i % 3;

            // Check if the position is empty
            if (gameBoard[row][col] != 'X' && gameBoard[row][col] != 'O') {
                gameBoard[row][col] = 'O';

                score = minimizedMinimax(0, false);
                gameBoard[row][col] = 'X';
            }
        }

        return score;
    } else {
        score = 1000;

        for (int i = 0; i < 9; i++) {
            int row = i / 3;
            int col = i % 3;

            // Check if the position is empty
            if (gameBoard[row][col] != 'X' && gameBoard[row][col] != 'O') {
                gameBoard[row][col] = 'X';

                score = maximizedMinimax(0, true);
                gameBoard[row][col] = 'O';
            }
        }

        return score;
    }
}

// Function to check if the player has won
bool hasWon(char player) {
    // Check rows and columns for a win
    for (int i = 0; i < 3; i++) {
        if (gameBoard[i][0] == player && gameBoard[i][1] == player && gameBoard[i][2] == player) {
            return true;
        }
        if (gameBoard[0][i] == player && gameBoard[1][i] == player && gameBoard[2][i] == player) {
            return true;
        }
    }

    // Check diagonals for a win
    if (gameBoard[0][0] == player && gameBoard[1][1] == player && gameBoard[2][2] == player) {
        return true;
    }
    if (gameBoard[0][2] == player && gameBoard[1][1] == player && gameBoard[2][0] == player) {
        return true;
    }

    return false;
}

// Function to check if the board is full
bool isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (gameBoard[i][j] != 'O' && gameBoard[i][j] != 'X') {
                return false;
            }
        }
    }

    return true;
}

// Main function
int main() {
    int position;

    while (1) {
        drawGameBoard();

        printf("Enter your move (1-9): ");
        scanf("%d", &position);

        makeUserMove(position - 1);

        if (hasWon('O')) {
            printf("You won!\n");
            break;
        }

        makeAIMove();

        if (hasWon('X')) {
            printf("Computer won!\n");
            break;
        }
    }

    return 0;
}