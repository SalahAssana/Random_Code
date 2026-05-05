#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Initialize random seed for number generation
    srand(time(NULL));

    // Generate a random number between 1 and 100
    int numberToGuess = rand() % 101;

    printf("Welcome to the Guess the Number Game!\n");
    printf("I'm thinking of a number between 1 and 100.\n");
    printf("Your goal is to guess it in as few attempts as possible.\n");

    // Initialize the number of attempts
    int attempts = 0;

    while (1) {
        // Ask user for their guess
        int guess;
        printf("Enter your guess: ");
        scanf("%d", &guess);

        // Check if the guess is correct
        if (guess == numberToGuess) {
            printf("\n Congratulations, you guessed the number in %d attempts!\n", attempts + 1);
            break;
        }
        // If the guess is too high
        else if (guess > numberToGuess) {
            printf("Too high! Try again.\n");
        }
        // If the guess is too low
        else {
            printf("Too low! Try again.\n");
        }

        attempts++;
    }

    return 0;
}