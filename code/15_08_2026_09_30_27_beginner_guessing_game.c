#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_GUESSES 10
#define MIN_NUMBER 1
#define MAX_NUMBER 100

int main() {
    int numberToGuess;
    int guesses = 0;

    srand(time(NULL)); // seed the random number generator

    numberToGuess = (rand() % (MAX_NUMBER - MIN_NUMBER + 1)) + MIN_NUMBER; // generate a random number to guess

    printf("Welcome to the Guessing Game! You have up to %d attempts to find the number.\n", MAX_GUESSES);

    while (guesses < MAX_GUESSES) {
        int userGuess;
        printf("Enter your guess: ");
        scanf("%d", &userGuess);

        if (userGuess > numberToGuess) {
            printf("Too high! Try again.\n");
        } else if (userGuess < numberToGuess) {
            printf("Too low! Try again.\n");
        } else {
            printf("Congratulations! You guessed the number in %d attempts.\n", guesses + 1);
            return 0;
        }

        guesses++;
    }

    printf("Sorry, you ran out of attempts. The number was %d.\n", numberToGuess);

    return 0;
}