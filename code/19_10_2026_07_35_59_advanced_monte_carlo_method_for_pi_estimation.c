#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITERATIONS 1000000
#define TOTAL_POINTS 50000
#define PI_ESTIMATION_POINTS 40000

int main() {
    int i;
    double piEstimate = 0.0, pointCount = 0.0;
    int insideCircle = 0;

    srand(time(NULL)); // Seed the random number generator

    for (i = 0; i < MAX_ITERATIONS; i++) {
        double x = (double)rand() / RAND_MAX * 2 - 1;
        double y = (double)rand() / RAND_MAX * 2 - 1;

        if ((x*x + y*y) <= 1) {
            insideCircle++;
        }

        pointCount++;

        if (pointCount >= PI_ESTIMATION_POINTS) {
            piEstimate = (double)insideCircle / pointCount * 4;
            printf("Estimated Pi: %f\n", piEstimate);
            break;
        }
    }

    return 0;
}