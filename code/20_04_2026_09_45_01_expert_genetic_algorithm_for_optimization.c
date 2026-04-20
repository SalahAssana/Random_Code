#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POPULATION_SIZE 100
#define GENERATIONS 500
#define MUTATION_RATE 0.01
#define CROSSOVER_RATE 0.5
#define OPTIMIZATION_FUNCTION 1 // 0: quadratic, 1: exponential

typedef struct {
    double* values;
    int size;
} Individual;

Individual* initializePopulation(int size) {
    Individual* population = (Individual*)malloc(sizeof(Individual) * POPULATION_SIZE);
    for (int i = 0; i < POPULATION_SIZE; i++) {
        population[i].size = size;
        population[i].values = (double*)malloc(sizeof(double) * size);
        for (int j = 0; j < size; j++) {
            population[i].values[j] = (double)rand() / RAND_MAX;
        }
    }
    return population;
}

void mutateIndividual(Individual* individual, int mutationRate) {
    for (int i = 0; i < individual->size; i++) {
        if ((double)rand() / RAND_MAX < mutationRate) {
            individual->values[i] += (2.0 * (double)rand() / RAND_MAX) - 1.0;
        }
    }
}

Individual* crossover(Individual* parent1, Individual* parent2, double crossoverRate) {
    Individual* child = (Individual*)malloc(sizeof(Individual));
    child->size = parent1->size;
    child->values = (double*)malloc(sizeof(double) * child->size);
    for (int i = 0; i < child->size; i++) {
        if ((double)rand() / RAND_MAX < crossoverRate) {
            child->values[i] = parent1->values[i];
        } else {
            child->values[i] = parent2->values[i];
        }
    }
    return child;
}

void evaluatePopulation(Individual* population, int optimizationFunction) {
    double bestFitness = -INFINITY;
    Individual* bestIndividual = NULL;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        double fitness = evaluateIndividual(population[i], optimizationFunction);
        if (fitness > bestFitness) {
            bestFitness = fitness;
            bestIndividual = &population[i];
        }
    }
    printf("Best individual: ");
    for (int i = 0; i < population[0].size; i++) {
        printf("%f ", bestIndividual->values[i]);
    }
    printf("\n");
}

double evaluateIndividual(Individual* individual, int optimizationFunction) {
    double fitness = 0.0;
    switch (optimizationFunction) {
        case 0: // quadratic
            for (int i = 0; i < individual->size; i++) {
                fitness += pow(individual->values[i], 2);
            }
            break;
        case 1: // exponential
            for (int i = 0; i < individual->size; i++) {
                fitness += exp(individual->values[i]);
            }
            break;
    }
    return fitness;
}

void selection(Individual* population) {
    Individual* nextGeneration[POPULATION_SIZE];
    double totalFitness = 0.0;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        totalFitness += evaluateIndividual(&population[i], OPTIMIZATION_FUNCTION);
    }
    for (int i = 0; i < POPULATION_SIZE; i++) {
        Individual* parent1 = &population[rand() % POPULATION_SIZE];
        Individual* parent2 = &population[rand() % POPULATION_SIZE];
        while (&parent1 == &parent2) {
            parent2 = &population[rand() % POPULATION_SIZE];
        }
        double fitness1 = evaluateIndividual(parent1, OPTIMIZATION_FUNCTION);
        double fitness2 = evaluateIndividual(parent2, OPTIMIZATION_FUNCTION);
        if (fitness1 / totalFitness > fitness2 / totalFitness) {
            nextGeneration[i] = parent1;
        } else {
            nextGeneration[i] = parent2;
        }
    }
    for (int i = 0; i < POPULATION_SIZE; i++) {
        population[i].values = nextGeneration[i]->values;
    }
}

void geneticAlgorithm() {
    srand(time(NULL));
    Individual* population = initializePopulation(10);
    for (int generation = 0; generation < GENERATIONS; generation++) {
        for (int individual = 0; individual < POPULATION_SIZE; individual++) {
            mutateIndividual(&population[individual], MUTATION_RATE);
        }
        for (int i = 0; i < POPULATION_SIZE / 2; i++) {
            Individual* parent1 = &population[i * 2];
            Individual* parent2 = &population[i * 2 + 1];
            Individual* child = crossover(parent1, parent2, CROSSOVER_RATE);
            population[individual] = *child;
        }
        selection(population);
    }
    evaluatePopulation(population, OPTIMIZATION_FUNCTION);
}

int main() {
    geneticAlgorithm();
    return 0;
}