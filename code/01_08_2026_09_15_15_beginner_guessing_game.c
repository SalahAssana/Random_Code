#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Initialize random seed
    srand(time(NULL));

    // Generate a random number between 1 and 100
    int secretNumber = (rand() % 100) + 1;

    int guess;
    int tries = 0;

    printf("Welcome to the Guessing Game! I'm thinking of a number between 1 and 100.\n");

    while (1) {
        // Get user's guess
        printf("Enter your guess: ");
        scanf("%d", &guess);

        // Check if the guess is correct
        if (guess == secretNumber) {
            printf(" Congratulations! You guessed it in %d tries.\n", tries + 1);
            break;
        } else if (guess < secretNumber) {
            printf("Too low! Try again.\n");
        } else {
            printf("Too high! Try again.\n");
        }
        tries++;
    }

    return 0;
}