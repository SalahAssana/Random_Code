#include <stdio.h>
#include <stdlib.h>

int main() {
    // Set the range of numbers for the game
    int min = 1;
    int max = 100;

    // Generate a random number within the range
    srand(time(NULL));
    int numberToGuess = (rand() % (max - min + 1)) + min;

    // Initialize attempts and guesses
    int attempts = 0;
    int guess;

    printf("Welcome to the Guessing Game!\n");
    printf("I'm thinking of a number between %d and %d.\n", min, max);

    while (1) {
        // Ask for the user's guess
        printf("Guess a number: ");
        scanf("%d", &guess);

        attempts++;

        if (guess == numberToGuess) {
            printf(" Congratulations! You guessed it in %d attempts.\n", attempts);
            break;
        } else if (guess > numberToGuess) {
            printf("Too high! Try again.\n");
        } else {
            printf("Too low! Try again.\n");
        }
    }

    return 0;
}