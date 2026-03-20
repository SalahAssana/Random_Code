#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define constants for genetic algorithm parameters
#define POPULATION_SIZE 100
#define GENERATIONS 500
#define MUTATION_RATE 0.01
#define ELITISM 2

// Define a structure to represent an individual (solution)
typedef struct {
    int *genes;
    double fitness;
} Individual;

// Function to initialize an individual with random genes
Individual* init_individual(int size) {
    Individual* ind = (Individual*)malloc(sizeof(Individual));
    ind->genes = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        ind->genes[i] = rand() % 2;
    }
    ind->fitness = 0.0;
    return ind;
}

// Function to calculate the fitness of an individual
void calc_fitness(Individual* ind, int *target) {
    double fitness = 0.0;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        if (ind->genes[i] == target[i]) {
            fitness += 1.0;
        }
    }
    ind->fitness = fitness / POPULATION_SIZE;
}

// Function to perform selection and crossover
Individual* select_and_crossover(Individual *population, int *target) {
    // Calculate the cumulative sum of fitnesses
    double *cum_sum = (double*)malloc((POPULATION_SIZE + 1) * sizeof(double));
    for (int i = 0; i < POPULATION_SIZE; i++) {
        cum_sum[i] = population[i].fitness;
    }
    cum_sum[POPULATION_SIZE] = 1.0;

    // Perform selection
    Individual* parent1 = &population[rand() % POPULATION_SIZE];
    Individual* parent2 = &population[rand() % POPULATION_SIZE];

    // Crossover (single point)
    int crossover_point = rand() % (POPULATION_SIZE - ELITISM);
    Individual* child = init_individual(POPULATION_SIZE);
    for (int i = 0; i < crossover_point; i++) {
        child->genes[i] = parent1->genes[i];
    }
    for (int i = crossover_point; i < POPULATION_SIZE; i++) {
        child->genes[i] = parent2->genes[i];
    }

    // Mutation
    for (int i = 0; i < POPULATION_SIZE; i++) {
        if (rand() % (1.0 / MUTATION_RATE) == 0) {
            child->genes[i] = 1 - child->genes[i];
        }
    }

    return child;
}

// Function to perform selection and mutation
Individual* select_and_mutate(Individual *population, int *target) {
    // Calculate the cumulative sum of fitnesses
    double *cum_sum = (double*)malloc((POPULATION_SIZE + 1) * sizeof(double));
    for (int i = 0; i < POPULATION_SIZE; i++) {
        cum_sum[i] = population[i].fitness;
    }
    cum_sum[POPULATION_SIZE] = 1.0;

    // Perform selection
    Individual* parent = &population[rand() % POPULATION_SIZE];

    // Mutation
    Individual* child = init_individual(POPULATION_SIZE);
    for (int i = 0; i < POPULATION_SIZE; i++) {
        if (rand() % (1.0 / MUTATION_RATE) == 0) {
            child->genes[i] = 1 - parent->genes[i];
        } else {
            child->genes[i] = parent->genes[i];
        }
    }

    return child;
}

// Main function
int main() {
    srand(time(NULL));

    // Initialize population with random individuals
    Individual* population = (Individual*)malloc(POPULATION_SIZE * sizeof(Individual));
    for (int i = 0; i < POPULATION_SIZE; i++) {
        population[i] = *init_individual(POPULATION_SIZE);
    }

    // Target solution
    int target[POPULATION_SIZE];
    for (int i = 0; i < POPULATION_SIZE; i++) {
        target[i] = rand() % 2;
    }

    // Run the genetic algorithm
    for (int generation = 0; generation < GENERATIONS; generation++) {
        // Calculate fitness of each individual
        for (int i = 0; i < POPULATION_SIZE; i++) {
            calc_fitness(&population[i], target);
        }

        // Perform selection and crossover
        Individual* best_individual = &population[0];
        double best_fitness = population[0].fitness;
        for (int i = 1; i < POPULATION_SIZE; i++) {
            if (population[i].fitness > best_fitness) {
                best_individual = &population[i];
                best_fitness = population[i].fitness;
            }
        }

        Individual* new_population[POPULATION_SIZE];
        int j = 0;
        for (int i = 0; i < POPULATION_SIZE; i++) {
            if (rand() % (1.0 / (double)(ELITISM + 1)) == 0) {
                new_population[j] = best_individual;
                j++;
            } else {
                Individual* child = select_and_crossover(population, target);
                new_population[j] = child;
                j++;
            }
        }

        // Replace old population with new one
        for (int i = 0; i < POPULATION_SIZE; i++) {
            population[i] = *new_population[i];
            free(new_population[i]->genes);
            free(new_population[i]);
        }
    }

    // Print the best individual and its fitness
    Individual* best_individual = &population[0];
    double best_fitness = population[0].fitness;
    for (int i = 1; i < POPULATION_SIZE; i++) {
        if (population[i].fitness > best_fitness) {
            best_individual = &population[i];
            best_fitness = population[i].fitness;
        }
    }

    printf("Best individual: ");
    for (int i = 0; i < POPULATION_SIZE; i++) {
        printf("%d", best_individual->genes[i]);
    }
    printf("\n");
    printf("Best fitness: %f\n", best_fitness);

    return 0;
}