#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the fitness function for the optimization problem
double fitness(double *x) {
    double sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += x[i] * sin(2 * M_PI * i / 5);
    }
    return -sum;
}

// Define the mutation function to introduce new genetic variations
void mutate(double *x, double mutation_rate) {
    for (int i = 0; i < 10; i++) {
        if (rand() % 100 < mutation_rate * 100) {
            x[i] += (rand() % 2) * 2 - 1;
        }
    }
}

// Define the crossover function to combine parent genes
void crossover(double *x1, double *x2, double *child, int crossover_point) {
    for (int i = 0; i < crossover_point; i++) {
        child[i] = x1[i];
    }
    for (int i = crossover_point; i < 10; i++) {
        child[i] = x2[i];
    }
}

// Define the selection function to choose parents based on fitness
void select(double *population[], int population_size, double **parents) {
    double max_fitness = -INFINITY;
    for (int i = 0; i < population_size; i++) {
        if (fitness(population[i]) > max_fitness) {
            max_fitness = fitness(population[i]);
            parents[0] = population[i];
        }
    }
    max_fitness = -INFINITY;
    for (int i = 1; i < population_size; i++) {
        if (fitness(population[i]) > max_fitness) {
            max_fitness = fitness(population[i]);
            parents[1] = population[i];
        }
    }
}

// Define the genetic algorithm function to optimize the solution
void genetic_algorithm(int generations, int population_size, double mutation_rate, double crossover_point) {
    // Initialize the population with random values
    double **population = (double **)malloc(population_size * sizeof(double *));
    for (int i = 0; i < population_size; i++) {
        population[i] = (double *)malloc(10 * sizeof(double));
        for (int j = 0; j < 10; j++) {
            population[i][j] = (rand() % 100) / 100.0;
        }
    }

    // Run the genetic algorithm for the specified number of generations
    for (int i = 0; i < generations; i++) {
        double **parents = (double **)malloc(2 * sizeof(double *));
        select(population, population_size, parents);

        // Create offspring by crossover and mutation
        double **offspring = (double **)malloc(population_size * sizeof(double *));
        for (int j = 0; j < population_size; j++) {
            offspring[j] = (double *)malloc(10 * sizeof(double));
            if (j % 2 == 0) {
                crossover(parents[0], parents[1], offspring[j], (int)(crossover_point * 10));
            } else {
                for (int k = 0; k < 10; k++) {
                    offspring[j][k] = population[rand() % population_size][k];
                }
            }
        }

        // Replace the least fit individuals in the population with the new offspring
        double min_fitness = INFINITY;
        int min_index = -1;
        for (int j = 0; j < population_size; j++) {
            if (fitness(population[j]) < min_fitness) {
                min_fitness = fitness(population[j]);
                min_index = j;
            }
        }
        for (int j = 0; j < population_size; j++) {
            population[min_index][j] = offspring[j][j];
        }

        free(parents);
        free(offspring);
    }

    // Print the final solution
    double max_fitness = -INFINITY;
    int best_index = -1;
    for (int i = 0; i < population_size; i++) {
        if (fitness(population[i]) > max_fitness) {
            max_fitness = fitness(population[i]);
            best_index = i;
        }
    }
    printf("Best solution: ");
    for (int i = 0; i < 10; i++) {
        printf("%.2f ", population[best_index][i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    genetic_algorithm(100, 20, 0.1, 0.5);
    return 0;
}