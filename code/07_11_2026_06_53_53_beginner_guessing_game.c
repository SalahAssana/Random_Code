#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Initialize random number generator
    srand(time(NULL));

    int secretNumber = rand() % 100 + 1; // Random number between 1 and 100

    printf("Welcome to the Guessing Game! I'm thinking of a number between 1 and 100.\n");

    int guess;
    while (1) {
        printf("Enter your guess: ");
        scanf("%d", &guess);

        if (guess == secretNumber) {
            printf("Congratulations, you guessed it!\n");
            break;
        } else if (guess < secretNumber) {
            printf("Too low! Try again.\n");
        } else {
            printf("Too high! Try again.\n");
        }
    }

    return 0;
}