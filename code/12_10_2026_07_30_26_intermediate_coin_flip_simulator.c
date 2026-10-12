#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COIN_FLIPS 10000
#define HEADS 0
#define TAILS 1

// Function to simulate coin flip and return result (HEADS/TAILS)
int coinFlip() {
    // Use rand() to generate a random number between 0 and RAND_MAX
    int randomNum = rand();
    // If the number is less than or equal to RAND_MAX / 2, it's HEADS
    if (randomNum <= RAND_MAX / 2) {
        return HEADS;
    } else {
        return TAILS;
    }
}

// Function to calculate the probability of heads/tails based on coin flips
void calculateProbability(int* headsCount, int* tailsCount) {
    *headsCount = 0;
    *tailsCount = 0;

    for (int i = 0; i < COIN_FLIPS; i++) {
        if (coinFlip() == HEADS) {
            (*headsCount)++;
        } else {
            (*tailsCount)++;
        }
    }
}

// Function to display the probability of heads/tails
void displayProbability(int heads, int tails) {
    double totalFlips = COIN_FLIPS;
    double headsProbability = (double)heads / totalFlips;
    double tailsProbability = (double)tails / totalFlips;

    printf("Heads: %.4f%%\n", headsProbability * 100);
    printf("Tails: %.4f%%\n", tailsProbability * 100);
}

int main() {
    srand(time(NULL)); // Seed the random number generator with current time

    int headsCount = 0;
    int tailsCount = 0;

    calculateProbability(&headsCount, &tailsCount);

    displayProbability(headsCount, tailsCount);

    return 0;
}