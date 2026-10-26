#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int numFlips;
    printf("Enter the number of coin flips: ");
    scanf("%d", &numFlips);

    srand(time(NULL)); // seed random number generator

    int heads = 0, tails = 0;

    for (int i = 0; i < numFlips; i++) {
        int flip = rand() % 2; // 0 for tails, 1 for heads
        if (flip == 0) {
            printf("Tails\n");
            tails++;
        } else {
            printf("Heads\n");
            heads++;
        }
    }

    printf("\nResults:\n");
    printf("Heads: %d\n", heads);
    printf("Tails: %d\n", tails);

    return 0;
}