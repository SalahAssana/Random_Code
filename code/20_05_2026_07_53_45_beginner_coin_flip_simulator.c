#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int heads = 0;
    int tails = 0;

    // Seed the random number generator
    srand(time(NULL));

    for(int i = 0; i < 100; i++) { // Simulate 100 coin flips
        int flip = rand() % 2; // Randomly generate a 0 or 1 (0 for heads, 1 for tails)

        if(flip == 0) {
            printf("Heads\n");
            heads++;
        } else {
            printf("Tails\n");
            tails++;
        }
    }

    printf("\nFinal count:\nHeads: %d\nTails: %d\n", heads, tails);

    return 0;
}