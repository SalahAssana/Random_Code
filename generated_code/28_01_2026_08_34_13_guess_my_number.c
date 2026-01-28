#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Initialize random seed for rand()
    srand(time(NULL));

    int targetNumber = (rand() % 100) + 1; // Generate a random number between 1 and 100
    int guesses = 0;

    printf("Guess My Number!\n");
    while (1) {
        int guess;
        printf("Enter your guess: ");
        scanf("%d", &guess);

        if (guess < targetNumber) {
            printf("Too low! Try again.\n");
        } else if (guess > targetNumber) {
            printf("Too high! Try again.\n");
        } else {
            printf(" Congratulations, you guessed it in %d attempts!\n", guesses + 1);
            break;
        }
        guesses++;
    }

    return 0;
}