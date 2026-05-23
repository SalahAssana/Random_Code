#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define POPULATION_SIZE 1000
#define GENERATIONS 500
#define MUTATION_RATE 0.01
#define ELITISM 10
#define FUNCTION_EVALUATIONS 10000

typedef struct {
    double* genes;
    double fitness;
} Individual;

Individual* initialize_population(int size) {
    Individual* population = (Individual*)malloc(size * sizeof(Individual));
    for (int i = 0; i < size; i++) {
        population[i].genes = (double*)malloc(5 * sizeof(double)); // Each individual has 5 genes
        for (int j = 0; j < 5; j++) {
            population[i].genes[j] = (rand() % 100) / (double)RAND_MAX;
        }
    }
    return population;
}

void evaluate_fitness(Individual* population, int size) {
    for (int i = 0; i < size; i++) {
        double sum = 0.0;
        for (int j = 0; j < 5; j++) {
            sum += pow(population[i].genes[j], 2);
        }
        population[i].fitness = -sum + FUNCTION_EVALUATIONS;
    }
}

Individual* select_parents(Individual* population, int size) {
    Individual* parents = (Individual*)malloc(size * sizeof(Individual));
    for (int i = 0; i < ELITISM; i++) {
        Individual temp = population[0];
        population[0] = population[i];
        population[i] = temp;
    }
    for (int i = 0; i < size - ELITISM; i++) {
        double max_fitness = -INFINITY;
        int parent_index = 0;
        for (int j = 0; j < size; j++) {
            if (population[j].fitness > max_fitness) {
                max_fitness = population[j].fitness;
                parent_index = j;
            }
        }
        parents[i] = population[parent_index];
    }
    return parents;
}

Individual* crossover(Individual* parents, int size) {
    Individual* offspring = (Individual*)malloc(size * sizeof(Individual));
    for (int i = 0; i < size / 2; i++) {
        double crossover_point = rand() % 5;
        for (int j = 0; j < 5; j++) {
            if (j < crossover_point) {
                offspring[i].genes[j] = parents[i * 2].genes[j];
                offspring[i + 1].genes[j] = parents[i * 2 + 1].genes[j];
            } else {
                offspring[i].genes[j] = parents[i * 2 + 1].genes[j];
                offspring[i + 1].genes[j] = parents[i * 2].genes[j];
            }
        }
    }
    return offspring;
}

Individual* mutate(Individual* population, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 5; j++) {
            if (rand() % (1.0 / MUTATION_RATE) == 0) {
                population[i].genes[j] += (rand() % 100) / (double)RAND_MAX - 0.5;
                if (population[i].genes[j] > 1.0) {
                    population[i].genes[j] = 1.0;
                } else if (population[i].genes[j] < 0.0) {
                    population[i].genes[j] = 0.0;
                }
            }
        }
    }
    return population;
}

void plot_results(Individual* population, int size) {
    double best_fitness = -INFINITY;
    for (int i = 0; i < size; i++) {
        if (population[i].fitness > best_fitness) {
            best_fitness = population[i].fitness;
        }
    }
    printf("Best fitness: %f\n", best_fitness);
}

int main() {
    srand(time(NULL));
    Individual* population = initialize_population(POPULATION_SIZE);
    for (int i = 0; i < GENERATIONS; i++) {
        evaluate_fitness(population, POPULATION_SIZE);
        Individual* parents = select_parents(population, POPULATION_SIZE);
        Individual* offspring = crossover(parents, POPULATION_SIZE / 2);
        population = mutate(offspring, POPULATION_SIZE - ELITISM);
    }
    plot_results(population, POPULATION_SIZE);
    return 0;
}