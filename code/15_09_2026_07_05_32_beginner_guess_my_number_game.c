#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Initialize random number generator
    srand(time(NULL));

    // Set the range of numbers to guess (1-100)
    int min = 1;
    int max = 100;

    // Generate a random number within the range
    int targetNumber = rand() % (max - min + 1) + min;

    printf("Welcome to Guess My Number Game! I'm thinking of a number between 1 and 100.\n");

    int guess;
    while ((guess = getchar()) != '\n') {
        // Check if the input is a valid number
        if (scanf("%d", &guess) == 1) {
            if (guess < min || guess > max) {
                printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
            } else {
                if (guess == targetNumber) {
                    printf("Congratulations! You guessed my number correctly.\n");
                    break;
                } else if (guess < targetNumber) {
                    printf("Too low! Try again.\n");
                } else {
                    printf("Too high! Try again.\n");
                }
            }
        } else {
            printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
        }
    }

    return 0;
}