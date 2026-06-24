#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int numberToGuess;
    int guess;

    // Seed random number generator for consistency
    srand(time(NULL));

    // Generate a random number between 1 and 100
    numberToGuess = rand() % 100 + 1;

    printf("I'm thinking of a number between 1 and 100. Try to guess it!\n");

    while (1) {
        // Get user's guess
        scanf("%d", &guess);

        if (guess < numberToGuess) {
            printf("Too low! Try again.\n");
        } else if (guess > numberToGuess) {
            printf("Too high! Try again.\n");
        } else {
            printf("Congratulations, you guessed it!\n");
            break;
        }
    }

    return 0;
}