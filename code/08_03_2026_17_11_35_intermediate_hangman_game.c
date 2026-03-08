#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_WORD_LENGTH 15
#define MAX_GUESSES 6

typedef struct {
    char word[MAX_WORD_LENGTH + 1];
    int length;
} Word;

void generateWord(Word* word) {
    // Generate a random word of maximum length
    const char* words[] = {"apple", "banana", "cherry", "date", "elderberry"};
    srand(time(NULL));
    strcpy(word->word, words[rand() % 5]);
    word->length = strlen(word->word);
}

void printWord(Word word) {
    // Print the word with underscores for unknown letters
    for (int i = 0; i < word.length; i++) {
        printf("%c", word.word[i] == ' ' ? '_' : word.word[i]);
    }
    printf("\n");
}

int checkGuess(char guess, Word word) {
    // Check if the guess is correct and return the index
    for (int i = 0; i < word.length; i++) {
        if (word.word[i] == guess) {
            return i;
        }
    }
    return -1;
}

void updateWord(char guess, Word* word) {
    // Update the word with correct guesses
    for (int i = 0; i < word->length; i++) {
        if (word->word[i] == guess) {
            printf("%c", word->word[i]);
        } else {
            printf("_");
        }
    }
    printf("\n");
}

void playHangman() {
    Word word;
    generateWord(&word);
    
    int guesses = 0;
    char guessedLetter;
    
    while (guesses < MAX_GUESSES) {
        printWord(word);
        printf("Enter a letter: ");
        scanf("%c", &guessedLetter);
        
        int index = checkGuess(guessedLetter, word);
        if (index != -1) {
            updateWord(guessedLetter, &word);
        } else {
            printf("Incorrect guess! Try again.\n");
        }
    }
    
    printWord(word);
    if (guesses < MAX_GUESSES) {
        printf("Congratulations! You guessed the word.\n");
    } else {
        printf("Game over! The word was %s.\n", word.word);
    }
}

int main() {
    playHangman();
    return 0;
}