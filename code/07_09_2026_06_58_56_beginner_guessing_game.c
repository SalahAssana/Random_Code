#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed random number generator
    srand(time(NULL));

    // Generate a random number between 1 and 100
    int target = rand() % 101;

    int guess;
    int attempts = 0;

    printf("Welcome to the Guessing Game! I'm thinking of a number between 1 and 100.\n");
    printf("Try to guess it in as few attempts as possible.\n");

    while (1) {
        // Ask for the player's guess
        printf("Enter your guess: ");
        scanf("%d", &guess);

        // Increment the attempt counter
        attempts++;

        if (guess < target) {
            printf("Too low! Try again.\n");
        } else if (guess > target) {
            printf("Too high! Try again.\n");
        } else {
            printf(" Congratulations, you guessed it in %d attempts!\n", attempts);
            break;
        }
    }

    return 0;
}