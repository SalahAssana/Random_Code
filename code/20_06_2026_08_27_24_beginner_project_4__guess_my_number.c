#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Initialize random number generator
    srand(time(NULL));

    int targetNumber;
    targetNumber = rand() % 100 + 1; // Randomly generate a number between 1 and 100

    int guess;
    int tries = 0;

    printf("Welcome to Guess My Number! I'm thinking of a number between 1 and 100.\n");
    printf("You can start guessing now. Good luck!\n");

    while (guess != targetNumber) {
        scanf("%d", &guess);
        tries++;

        if (guess < targetNumber) {
            printf("Too low, try again! You have tried %d times.\n", tries);
        } else if (guess > targetNumber) {
            printf("Too high, try again! You have tried %d times.\n", tries);
        }
    }

    printf("Congratulations! You guessed my number in %d tries. The answer was %d\n", tries, targetNumber);

    return 0;
}