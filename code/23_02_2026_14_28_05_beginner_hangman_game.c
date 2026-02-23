#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_WORD_LENGTH 10
#define MAX_GUESSES 6

// Function to generate random word
char* generateRandomWord() {
    char* words[] = {"apple", "banana", "cherry", "date", "elderberry"};
    srand(time(NULL));
    int index = rand() % (sizeof(words) / sizeof(words[0]));
    return words[index];
}

// Function to draw hangman diagram
void drawHangman(int guesses) {
    if (guesses == 1) {
        printf(" _ \n");
        printf("| | \n");
        printf("|_| \n");
    } else if (guesses == 2) {
        printf(" _ \n");
        printf("| | \n");
        printf("|_| \n");
        printf("|\n");
    } else if (guesses == 3) {
        printf(" _ \n");
        printf("| | \n");
        printf("|_| \n");
        printf("| |\n");
    } else if (guesses == 4) {
        printf(" _ \n");
        printf("| X \n");
        printf("|_| \n");
        printf("| |\n");
    } else if (guesses == 5) {
        printf(" _ \n");
        printf("| X| \n");
        printf("|_| \n");
        printf("| |\n");
    } else {
        printf(" _ \n");
        printf("| X|X \n");
        printf("|_| \n");
        printf("| |\n");
    }
}

int main() {
    char* word = generateRandomWord();
    int guesses = 0;
    char guessedLetter[MAX_WORD_LENGTH];
    for (int i = 0; i < MAX_WORD_LENGTH; i++) {
        guessedLetter[i] = '_';
    }

    while (guesses < MAX_GUESSES) {
        drawHangman(guesses);
        printf("Word: ");
        for (int i = 0; i < MAX_WORD_LENGTH; i++) {
            printf("%c ", guessedLetter[i]);
        }
        printf("\n");
        char letter;
        scanf(" %c", &letter);

        // Check if the letter is in the word
        int found = 0;
        for (int i = 0; i < MAX_WORD_LENGTH; i++) {
            if (word[i] == letter) {
                guessedLetter[i] = letter;
                found = 1;
            }
        }

        if (!found) {
            guesses++;
        } else {
            int correctGuesses = 0;
            for (int i = 0; i < MAX_WORD_LENGTH; i++) {
                if (guessedLetter[i] != '_') {
                    correctGuesses++;
                }
            }
            if (correctGuesses == MAX_WORD_LENGTH) {
                printf("Congratulations! You guessed the word: %s\n", word);
                return 0;
            }
        }
    }

    drawHangman(guesses);
    printf("Game Over! The word was: %s\n", word);

    return 0;
}