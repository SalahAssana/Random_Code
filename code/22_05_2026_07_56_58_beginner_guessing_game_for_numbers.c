#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator for reproducibility
    srand(time(NULL));

    int lowerBound = 1;
    int upperBound = 100;

    int secretNumber = (rand() % (upperBound - lowerBound + 1)) + lowerBound;

    printf("Welcome to the Guessing Game! I'm thinking of a number between %d and %d. Try to guess it.\n", lowerBound, upperBound);

    int guess;
    do {
        scanf("%d", &guess);
        if (guess < secretNumber) {
            printf("Your guess is too low. Try again!\n");
        } else if (guess > secretNumber) {
            printf("Your guess is too high. Try again!\n");
        }
    } while (guess != secretNumber);

    printf("Congratulations! You guessed the number: %d\n", secretNumber);

    return 0;
}