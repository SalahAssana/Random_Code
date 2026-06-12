#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int heads = 0;
    int tails = 0;

    // Initialize random seed
    srand(time(NULL));

    for(int i = 0; i < 10000; i++) { // Simulate flipping a coin 10,000 times
        int flip = rand() % 2; // Generate random number (0 or 1)
        if(flip == 0) {
            heads++;
        } else {
            tails++;
        }
    }

    printf("Heads: %d\n", heads);
    printf("Tails: %d\n", tails);

    double probabilityHeads = (double)heads / (heads + tails);
    double probabilityTails = (double)tails / (heads + tails);

    printf("Probability of Heads: %.4f\n", probabilityHeads);
    printf("Probability of Tails: %.4f\n", probabilityTails);

    return 0;
}