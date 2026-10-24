#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Define constants
#define POPULATION_SIZE 100
#define GENERATIONS 500
#define CROSSOVER_PROBABILITY 0.5
#define MUTATION_PROBABILITY 0.05
#define NUM_VARIABLES 10

// Define the fitness function
double fitness(double *solution) {
    double sum = 0;
    for (int i = 0; i < NUM_VARIABLES; i++) {
        sum += pow(solution[i], 2);
    }
    return -sum;
}

// Define the crossover operator
void single_point_crossover(double *parent1, double *parent2, double *child1, double *child2) {
    int crossover_point = rand() % NUM_VARIABLES;
    for (int i = 0; i < crossover_point; i++) {
        child1[i] = parent1[i];
        child2[i] = parent2[i];
    }
    for (int i = crossover_point; i < NUM_VARIABLES; i++) {
        child1[i] = parent2[i];
        child2[i] = parent1[i];
    }
}

// Define the mutation operator
void gaussian_mutation(double *solution, double sigma) {
    for (int i = 0; i < NUM_VARIABLES; i++) {
        solution[i] += randn() * sigma;
    }
}

double randn(void) {
    static int initialized = 0;
    double variance = 1.0;
    double std_dev = sqrt(variance);
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }
    return (rand() / (RAND_MAX / std_dev)) * 2 - 1;
}

int main() {
    // Initialize the population
    double **population = malloc(POPULATION_SIZE * sizeof(double *));
    for (int i = 0; i < POPULATION_SIZE; i++) {
        population[i] = malloc(NUM_VARIABLES * sizeof(double));
        for (int j = 0; j < NUM_VARIABLES; j++) {
            population[i][j] = (double)rand() / RAND_MAX;
        }
    }

    // Evaluate the initial fitness
    double **fitness_values = malloc(POPULATION_SIZE * sizeof(double *));
    for (int i = 0; i < POPULATION_SIZE; i++) {
        fitness_values[i] = malloc(sizeof(double));
        *(fitness_values[i]) = fitness(population[i]);
    }

    // Run the genetic algorithm
    int generation = 0;
    while (generation < GENERATIONS) {
        // Select parents
        double **parents = malloc(POPULATION_SIZE * sizeof(double *));
        for (int i = 0; i < POPULATION_SIZE / 2; i++) {
            double r1, r2;
            do {
                r1 = rand() / (RAND_MAX);
                r2 = rand() / (RAND_MAX);
            } while (r1 > r2 || r1 == 0 && r2 == 0);
            parents[2 * i] = population[r1];
            parents[2 * i + 1] = population[r2];
        }

        // Apply crossover
        double **children = malloc(POPULATION_SIZE * sizeof(double *));
        for (int i = 0; i < POPULATION_SIZE / 2; i++) {
            single_point_crossover(parents[2 * i], parents[2 * i + 1],
                children[2 * i], children[2 * i + 1]);
        }

        // Apply mutation
        for (int i = 0; i < POPULATION_SIZE / 2; i++) {
            if (rand() / (RAND_MAX) < MUTATION_PROBABILITY) {
                gaussian_mutation(children[i], 0.1);
            }
        }

        // Replace the least fit individuals with children
        for (int i = 0; i < POPULATION_SIZE; i++) {
            double min_fitness = INFINITY;
            int min_index = -1;
            for (int j = 0; j < POPULATION_SIZE / 2; j++) {
                if (*(fitness_values[j]) < min_fitness) {
                    min_fitness = *(fitness_values[j]);
                    min_index = j;
                }
            }
            population[min_index] = children[i];
        }

        // Evaluate the new fitness
        for (int i = 0; i < POPULATION_SIZE; i++) {
            *(fitness_values[i]) = fitness(population[i]);
        }

        generation++;
    }

    // Print the final solution
    double best_fitness = INFINITY;
    int best_index = -1;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        if (*(fitness_values[i]) < best_fitness) {
            best_fitness = *(fitness_values[i]);
            best_index = i;
        }
    }
    printf("Best solution: ");
    for (int i = 0; i < NUM_VARIABLES; i++) {
        printf("%f ", population[best_index][i]);
    }
    printf("\n");

    // Free memory
    for (int i = 0; i < POPULATION_SIZE; i++) {
        free(population[i]);
        free(fitness_values[i]);
    }
    free(population);
    free(fitness_values);

    return 0;
}