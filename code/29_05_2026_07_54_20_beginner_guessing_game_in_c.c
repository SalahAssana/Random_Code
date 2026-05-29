#include <stdio.h>
#include <stdlib.h>

int main() {
    // Initialize a random number between 1 and 100
    int randomNumber = rand() % 100 + 1;
    
    // Declare variables to store player's guess and attempts count
    int guess, attempts = 0;
    
    // Start the game loop
    while (1) {
        printf("Guess a number between 1 and 100: ");
        scanf("%d", &guess);
        
        // Check if the player guessed correctly
        if (guess == randomNumber) {
            printf(" Congratulations! You guessed the number in %d attempts.\n", attempts + 1);
            break;
        } else if (guess < randomNumber) {
            printf("Too low, try again!\n");
        } else {
            printf("Too high, try again!\n");
        }
        
        // Increment attempts count
        attempts++;
    }
    
    return 0;
}