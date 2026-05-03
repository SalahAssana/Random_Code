#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Initialize random number generator
    srand(time(NULL));

    // Set range for guessing game (0-100)
    int min = 0;
    int max = 100;

    // Generate a random number within the range
    int target = (rand() % (max - min + 1)) + min;

    // Initialize guess counter
    int attempts = 0;

    printf("Welcome to the Guessing Game!\n");
    printf("I'm thinking of a number between 0 and 100.\n");

    while(1) {
        // Ask user for their guess
        printf("What's your guess? ");
        int guess;
        scanf("%d", &guess);

        // Check if guess is correct
        if(guess == target) {
            printf("Congratulations! You guessed it in %d attempts.\n", attempts + 1);
            break;
        }
        // If guess is too high, give hint
        else if(guess > target) {
            printf("Too high! Try again...\n");
        }
        // If guess is too low, give hint
        else {
            printf("Too low! Try again...\n");
        }

        attempts++;
    }

    return 0;
}