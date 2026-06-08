#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL)); // seed random number generator
    int flip; // variable to store coin flip result
    flip = rand() % 2; // generate a random number between 0 and 1 (inclusive)
    if (flip == 0) {
        printf("Heads\n");
    } else {
        printf("Tails\n");
    }
    return 0;
}