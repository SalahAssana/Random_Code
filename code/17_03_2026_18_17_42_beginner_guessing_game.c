#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Initialize random number generator
    srand(time(NULL));

    int answer = (rand() % 100) + 1; // Generate a random number between 1 and 100

    printf("Welcome to the Guessing Game! I'm thinking of a number between 1 and 100.\n");

    int tries = 0;

    while(1) {
        // Ask user for their guess
        int guess;
        scanf("%d", &guess);

        tries++;

        if(guess > answer) {
            printf("Your guess is too high. Try again!\n");
        } else if(guess < answer) {
            printf("Your guess is too low. Try again!\n");
        } else {
            printf("Congratulations! You guessed the number in %d tries.\n", tries);
            break;
        }
    }

    return 0;
}