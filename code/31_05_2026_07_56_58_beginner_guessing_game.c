#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL)); // seed random number generator

    int low = 1;
    int high = 100; // adjust this to change the range of numbers
    int target = rand() % (high - low + 1) + low;

    printf("Welcome to the guessing game! I'm thinking of a number between 1 and 100.\n");
    printf("You have to guess it. Good luck!\n");

    int guesses = 0;
    int guess;
    while(1) {
        printf("Enter your guess: ");
        scanf("%d", &guess);

        if(guess < low || guess > high) {
            printf("Invalid input! Please enter a number between %d and %d.\n", low, high);
            continue;
        }

        guesses++;

        if(guess == target) {
            printf(" Congratulations! You guessed the correct number in %d attempts.\n", guesses);
            break;
        } else if(guess < target) {
            printf("Too low! Try again.\n");
        } else {
            printf("Too high! Try again.\n");
        }
    }

    return 0;
}