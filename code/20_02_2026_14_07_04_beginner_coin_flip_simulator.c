#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int numFlips;
    int heads = 0;
    int tails = 0;

    printf("Enter the number of coin flips: ");
    scanf("%d", &numFlips);

    srand(time(NULL)); // seed random number generator

    for (int i = 0; i < numFlips; i++) {
        int flipResult = rand() % 2;
        if (flipResult == 0) {
            printf("Heads\n");
            heads++;
        } else {
            printf("Tails\n");
            tails++;
        }
    }

    printf("\nCoin Flip Results:\n");
    printf("Heads: %d\n", heads);
    printf("Tails: %d\n", tails);

    return 0;
}