#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_WORD_LENGTH 20
#define MAX_GUESSES 6

typedef struct {
    char word[MAX_WORD_LENGTH + 1];
    int length;
} Word;

Word* generateRandomWord() {
    Word* word = (Word*)malloc(sizeof(Word));
    const char* dictionary[] = {"apple", "banana", "cherry", "date", "elderberry", "fig", "grape"};
    srand(time(NULL));
    int randomIndex = rand() % (sizeof(dictionary) / sizeof(*dictionary));
    strcpy(word->word, dictionary[randomIndex]);
    word->length = strlen(dictionary[randomIndex]);

    return word;
}

void printWord(Word* word, char* guessedLetters) {
    for (int i = 0; i < word->length; i++) {
        if (guessedLetters[i] == word->word[i]) {
            printf("%c ", word->word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

void gameLoop(Word* word, char* guessedLetters) {
    int guesses = 0;
    while (guesses < MAX_GUESSES) {
        printWord(word, guessedLetters);
        printf("Enter a letter: ");
        char letter;
        scanf(" %c", &letter);

        bool letterFound = false;
        for (int i = 0; i < word->length; i++) {
            if (word->word[i] == letter) {
                guessedLetters[i] = letter;
                letterFound = true;
            }
        }

        if (!letterFound) {
            printf("Incorrect guess! Try again.\n");
            guesses++;
        } else {
            printf("Correct guess! Keep going!\n");
        }

        if (word->length == 0) {
            printf("Congratulations, you guessed the word: %s\n", word->word);
            break;
        }
    }

    if (guesses >= MAX_GUESSES) {
        printWord(word, guessedLetters);
        printf("Game over! The word was %s.\n", word->word);
    }
}

int main() {
    Word* word = generateRandomWord();
    char guessedLetters[MAX_WORD_LENGTH + 1];
    for (int i = 0; i < MAX_WORD_LENGTH; i++) {
        guessedLetters[i] = '_';
    }
    guessedLetters[MAX_WORD_LENGTH] = '\0';

    gameLoop(word, guessedLetters);

    free(word);
    return 0;
}