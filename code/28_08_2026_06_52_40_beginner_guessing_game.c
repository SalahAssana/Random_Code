#include <stdio.h>

int main() {
    int numberToGuess = 42; // secret number to guess
    int guess;
    int tries = 0;

    printf("Welcome to the Guessing Game! I'm thinking of a number between 1 and 100.\n");
    printf("You have unlimited tries to guess it. Good luck!\n\n");

    while (1) {
        printf("Enter your guess: ");
        scanf("%d", &guess);

        if (guess == numberToGuess) {
            printf("Congratulations! You guessed the correct number in %d tries.\n", tries + 1);
            break;
        } else if (guess < numberToGuess) {
            printf("Too low! Try again.\n");
        } else {
            printf("Too high! Try again.\n");
        }
        tries++;
    }

    return 0;
}