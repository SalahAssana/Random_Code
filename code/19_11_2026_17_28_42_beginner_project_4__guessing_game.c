#include <stdio.h>
#include <stdlib.h>

int main() {
    // Computer thinks of a number between 1 and 100
    int targetNumber = rand() % 101; // Randomly generates a number from 0 to 100
    
    printf("Welcome to the Guessing Game! I'm thinking of a number between 1 and 100.\n");
    
    int guess;
    int attempts = 0;
    
    do {
        printf("Enter your guess: ");
        scanf("%d", &guess);
        
        if (guess < targetNumber) {
            printf("Too low. Try again!\n");
        } else if (guess > targetNumber) {
            printf("Too high. Try again!\n");
        }
        attempts++;
    } while (guess != targetNumber);
    
    printf("\nCongratulations! You guessed it in %d attempts.\n", attempts);
    
    return 0;
}