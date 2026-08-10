#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Initialize random seed for generating random number
    srand(time(NULL));

    // Generate a random number between 1 and 100
    int targetNumber = rand() % 100 + 1;

    int guess;
    int tries = 0;

    printf("Welcome to the Guessing Game! I'm thinking of a number between 1 and 100.\n");
    printf("Try to guess it in as few attempts as possible!\n");

    while (1) {
        // Ask user for their guess
        printf("Enter your guess: ");
        scanf("%d", &guess);

        tries++;

        if (guess < targetNumber) {
            printf("Too low! Try again.\n");
        } else if (guess > targetNumber) {
            printf("Too high! Try again.\n");
        } else {
            printf("Congratulations, you guessed it in %d attempts!\n", tries);
            break;
        }
    }

    return 0;
}