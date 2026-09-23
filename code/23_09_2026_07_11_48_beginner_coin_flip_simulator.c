#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int numFlips;
    int headsCount = 0;
    int tailsCount = 0;

    printf("Enter the number of coin flips: ");
    scanf("%d", &numFlips);

    srand(time(NULL)); // seed random number generator

    for (int i = 0; i < numFlips; i++) {
        double bias = (double)rand() / RAND_MAX;
        if (bias > 0.5) {
            printf("Heads\n");
            headsCount++;
        } else {
            printf("Tails\n");
            tailsCount++;
        }
    }

    printf("Heads: %d, Tails: %d\n", headsCount, tailsCount);

    return 0;
}