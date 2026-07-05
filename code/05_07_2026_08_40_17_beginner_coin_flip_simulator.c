#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int numFlips;
    srand(time(NULL)); // seed random number generator
    printf("Enter the number of coin flips: ");
    scanf("%d", &numFlips);

    int heads = 0, tails = 0;

    for (int i = 0; i < numFlips; i++) {
        int flip = rand() % 2;
        if (flip == 0) {
            printf("Heads\n");
            heads++;
        } else {
            printf("Tails\n");
            tails++;
        }
    }

    double headPercentage = (double)heads / numFlips * 100.0;
    double tailPercentage = (double)tails / numFlips * 100.0;

    printf("\nResults:\n");
    printf("Heads: %d (%.2f%%)\n", heads, headPercentage);
    printf("Tails: %d (%.2f%%)\n", tails, tailPercentage);

    return 0;
}