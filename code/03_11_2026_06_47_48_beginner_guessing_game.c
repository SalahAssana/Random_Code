#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Initialize random seed for generating random numbers
    srand(time(NULL));

    int maxRange = 100; // Maximum range of generated number
    int minGuesses = 3; // Minimum number of guesses allowed

    int attempts = 0;
    int guessedNumber = -1;

    printf("Welcome to the Guessing Game! I'm thinking of a number between 1 and %d.\n", maxRange);

    while (attempts < minGuesses) {
        int guess;
        printf("Enter your guess: ");
        scanf("%d", &guess);

        attempts++;

        if (guess > maxRange || guess < 1) {
            printf("Invalid input. Please enter a number between 1 and %d.\n", maxRange);
            continue;
        }

        int generatedNumber = rand() % (maxRange - 0 + 1) + 0; // Generate random number within the range

        if (guess == generatedNumber) {
            printf("Congratulations! You guessed the correct number in %d attempts.\n", attempts);
            break;
        } else {
            printf("Sorry, your guess is not correct. Try again!\n");
        }
    }

    return 0;
}