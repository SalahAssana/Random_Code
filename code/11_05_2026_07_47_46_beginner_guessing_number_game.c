#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Initialize random seed for generating random numbers
    srand(time(NULL));

    // Generate a random number between 1 and 100
    int numberToGuess = (rand() % 100) + 1;

    printf("Welcome to the Guessing Number Game!\n");
    printf("I'm thinking of a number between 1 and 100.\n");

    int guess;
    int tries = 0;

    while (1) {
        // Ask user for their guess
        printf("What's your guess? ");
        scanf("%d", &guess);

        // Check if the guess is correct
        if (guess == numberToGuess) {
            printf(" Congratulations! You guessed correctly!\n");
            break;
        }
        // Check if the guess is higher than the number to guess
        else if (guess > numberToGuess) {
            printf("Too high! Try again.\n");
        }
        // Check if the guess is lower than the number to guess
        else {
            printf("Too low! Try again.\n");
        }

        tries++;
    }

    printf("It took you %d tries to guess correctly!\n", tries);

    return 0;
}