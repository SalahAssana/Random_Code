#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define the function to optimize
double func(double x) {
    return (x - 3.0) * (x - 3.0) + 1.5;
}

// Simulated Annealing Algorithm
void simulated_annealing(int N, double T, double alpha, double *best_x, double *best_f) {
    int i;
    double x[N], f[N];
    for (i = 0; i < N; i++) {
        x[i] = (double)rand() / RAND_MAX * 6.0 - 3.0;
        f[i] = func(x[i]);
    }
    double current_f = func(*best_x);
    double new_f, delta_f;

    for (int iter = 0; T > 1e-6; iter++) {
        int j = rand() % N;
        double dx = (double)rand() / RAND_MAX * 2.0 - 1.0;
        double x_new = x[j] + dx;
        new_f = func(x_new);
        delta_f = new_f - current_f;

        if (delta_f < 0 || exp(-delta_f / T) > (double)rand() / RAND_MAX) {
            *best_x = x_new;
            current_f = new_f;
        }

        T *= alpha;
    }
}

int main() {
    int N = 100; // Population size
    double T = 100.0; // Initial temperature
    double alpha = 0.9; // Cooling rate

    srand(time(NULL)); // Seed the random number generator

    double best_x, best_f;
    simulated_annealing(N, T, alpha, &best_x, &best_f);

    printf("Best x: %f\n", best_x);
    printf("Best f: %f\n", best_f);

    return 0;
}