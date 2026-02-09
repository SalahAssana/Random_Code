#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int numFlips;
    int headsCount = 0;
    int tailsCount = 0;

    // Ask user for number of flips
    printf("Enter the number of coin flips: ");
    scanf("%d", &numFlips);

    srand(time(NULL)); // Seed random number generator

    for (int i = 0; i < numFlips; i++) {
        int flipResult;
        flipResult = rand() % 2;

        if (flipResult == 0) {
            printf("Heads\n");
            headsCount++;
        } else {
            printf("Tails\n");
            tailsCount++;
        }
    }

    // Display statistics
    printf("\nStatistics:\n");
    printf("Heads: %d\n", headsCount);
    printf("Tails: %d\n", tailsCount);

    return 0;
}