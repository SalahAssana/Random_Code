#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed random number generator
    srand(time(NULL));

    // Generate a random number between 1 and 100
    int targetNumber = rand() % 101;

    printf("Welcome to the Guessing Game! I'm thinking of a number between 1 and 100.\n");
    printf("Your goal is to guess the number in as few attempts as possible.\n\n");

    // Initialize the number of guesses
    int numGuesses = 0;

    while (1) {
        // Ask the user for their guess
        int guess;
        printf("Enter your guess: ");
        scanf("%d", &guess);

        // Increment the number of guesses
        numGuesses++;

        // Check if the user guessed correctly
        if (guess == targetNumber) {
            printf(" Congratulations! You guessed the correct number in %d attempts.\n", numGuesses);
            break;
        } else if (guess < targetNumber) {
            printf("Your guess is too low. Try again!\n");
        } else {
            printf("Your guess is too high. Try again!\n");
        }
    }

    return 0;
}