#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL)); // seed random number generator
    
    int numberToGuess = rand() % 100 + 1; // generate a random number between 1 and 100
    int attempts = 0;
    
    printf("Welcome to the Guessing Game! I'm thinking of a number between 1 and 100.\n");
    printf("Try to guess it in as few attempts as possible.\n");
    
    while(1) {
        int guess;
        printf("Enter your guess: ");
        scanf("%d", &guess);
        
        attempts++;
        
        if(guess < numberToGuess) {
            printf("Too low! Try again.\n");
        } else if(guess > numberToGuess) {
            printf("Too high! Try again.\n");
        } else {
            printf(" Congratulations, you guessed it in %d attempts!\n", attempts);
            return 0;
        }
    }
}