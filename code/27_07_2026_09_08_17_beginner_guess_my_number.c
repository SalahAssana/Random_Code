#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Set the range for the randomly generated number
    int min = 1;
    int max = 100;

    // Generate a random number within the specified range
    srand(time(NULL)); // Seed the random number generator
    int targetNumber = (rand() % (max - min + 1)) + min;

    printf("I'm thinking of a number between %d and %d. Try to guess it!\n", min, max);

    int userGuess;
    int attempts = 0;

    while (1) {
        // Ask the user for their guess
        printf("Enter your guess: ");
        scanf("%d", &userGuess);
        attempts++;

        if (userGuess == targetNumber) {
            // The user guessed correctly, display a success message and exit the loop
            printf("\n Congratulations! You guessed it in %d attempts.\n", attempts);
            break;
        } else if (userGuess < targetNumber) {
            // The user's guess was too low, provide a hint
            printf("Too low! Try again...\n");
        } else {
            // The user's guess was too high, provide a hint
            printf("Too high! Try again...\n");
        }
    }

    return 0;
}