#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int numberToGuess = rand() % 100 + 1; // Generate random number between 1 and 100
    int attempts = 0;

    printf("Welcome to the Guessing Game! Think of a number between 1 and 100.\n");

    while (1) {
        int guess;
        printf("Enter your guess: ");
        scanf("%d", &guess);

        attempts++;

        if (guess < numberToGuess) {
            printf("Too low, try again!\n");
        } else if (guess > numberToGuess) {
            printf("Too high, try again!\n");
        } else {
            printf(" Congratulations! You guessed the correct number in %d attempts.\n", attempts);
            break;
        }
    }

    return 0;
}