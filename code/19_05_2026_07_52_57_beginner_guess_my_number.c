#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed random number generator for better randomness
    srand(time(NULL));

    // Set range of possible numbers (1-100)
    int min = 1;
    int max = 100;

    // Generate a random number within the range
    int secretNumber = (rand() % (max - min + 1)) + min;

    printf("Guess My Number! I'm thinking of a number between %d and %d.\n", min, max);

    int guess;
    while (1) {
        // Get user's guess
        printf("Enter your guess: ");
        scanf("%d", &guess);

        if (guess < secretNumber) {
            printf("Too low! Try again.\n");
        } else if (guess > secretNumber) {
            printf("Too high! Try again.\n");
        } else {
            printf(" Congratulations! You guessed the number: %d\n", secretNumber);
            break;
        }
    }

    return 0;
}