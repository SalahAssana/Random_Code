#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Set the range for the random number
    int min = 1;
    int max = 100;

    // Generate a random number within the set range
    srand(time(NULL));
    int target_number = (rand() % (max - min + 1)) + min;

    // Initialize the number of attempts
    int attempts = 0;

    printf("Guess a number between %d and %d: ", min, max);

    int guess;
    scanf("%d", &guess);

    while(guess != target_number) {
        if(guess < target_number) {
            printf("Too low! Try again: ");
        } else {
            printf("Too high! Try again: ");
        }
        scanf("%d", &guess);
        attempts++;
    }

    printf("Congratulations, you guessed the number in %d attempts!\n", attempts);

    return 0;
}