#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed random number generator for reproducibility
    srand(time(NULL));

    int totalFlips = 1000000; // Total flips to simulate
    int headsCount = 0; // Count of heads

    // Simulate coin flips and count heads
    for (int i = 0; i < totalFlips; i++) {
        if ((rand() % 2) == 0) { // Heads probability: 50%
            headsCount++;
        }
    }

    double headsProbability = (double)headsCount / totalFlips;
    printf("Heads probability: %.4f\n", headsProbability);

    return 0;
}