#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define constants for genetic algorithm parameters
#define POPULATION_SIZE 100
#define GENERATIONS 1000
#define MUTATION_RATE 0.01
#define CROSSOVER_RATE 0.5
#define TARGET_VALUE 5000

// Define the fitness function type
typedef int (*FitnessFunction)(int);

// Structure to represent a chromosome (solution)
typedef struct {
    int *genes;
    int size;
} Chromosome;

// Function to initialize a new chromosome with random genes
Chromosome* init_chromosome(int size) {
    Chromosome* chr = malloc(sizeof(Chromosome));
    chr->size = size;
    chr->genes = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        chr->genes[i] = rand() % 10; // Random genes
    }
    return chr;
}

// Function to evaluate the fitness of a chromosome
int fitness_function(Chromosome* chr, FitnessFunction func) {
    int sum = 0;
    for (int i = 0; i < chr->size; i++) {
        sum += func(chr->genes[i]);
    }
    return sum;
}

// Function to perform crossover between two chromosomes
Chromosome* crossover(Chromosome* parent1, Chromosome* parent2) {
    Chromosome* child = init_chromosome(parent1->size);
    int crossover_point = rand() % (parent1->size - 1) + 1;
    for (int i = 0; i < parent1->size; i++) {
        if (i < crossover_point) {
            child->genes[i] = parent1->genes[i];
        } else {
            child->genes[i] = parent2->genes[i];
        }
    }
    return child;
}

// Function to perform mutation on a chromosome
Chromosome* mutate(Chromosome* chr, int mutation_rate) {
    for (int i = 0; i < chr->size; i++) {
        if (rand() % 100 <= mutation_rate * 100) { // Randomly decide whether to mutate
            chr->genes[i] = rand() % 10; // Mutate gene
        }
    }
    return chr;
}

// Function to select the fittest chromosome from a population
Chromosome* select_fittest(Chromosome** population, int size) {
    int max_fitness = -1;
    Chromosome* fittest_chr = NULL;
    for (int i = 0; i < size; i++) {
        int fitness = fitness_function(population[i], &max);
        if (fitness > max_fitness) {
            max_fitness = fitness;
            fittest_chr = population[i];
        }
    }
    return fittest_chr;
}

// Main genetic algorithm loop
void ga_loop(FitnessFunction func, Chromosome** population) {
    for (int i = 0; i < GENERATIONS; i++) {
        // Select the fittest chromosome
        Chromosome* fittest = select_fittest(population, POPULATION_SIZE);
        
        // Perform crossover and mutation on the fittest chromosome
        Chromosome* child1 = crossover(fittest, init_chromosome(fittest->size));
        Chromosome* child2 = crossover(fittest, init_chromosome(fittest->size));
        child1 = mutate(child1, MUTATION_RATE);
        child2 = mutate(child2, MUTATION_RATE);
        
        // Replace the least fit chromosome with a new one
        int min_fitness = INT_MAX;
        Chromosome* least_fit_chr = NULL;
        for (int j = 0; j < POPULATION_SIZE; j++) {
            int fitness = fitness_function(population[j], &max);
            if (fitness < min_fitness) {
                min_fitness = fitness;
                least_fit_chr = population[j];
            }
        }
        *least_fit_chr = *child1; // Replace the least fit chromosome with a new one
        
        // Print the best solution found so far
        int best_solution = -1;
        Chromosome* best_chr = NULL;
        for (int j = 0; j < POPULATION_SIZE; j++) {
            int fitness = fitness_function(population[j], &max);
            if (fitness > best_solution) {
                best_solution = fitness;
                best_chr = population[j];
            }
        }
        printf("Generation %d: Best solution is %d\n", i, best_solution);
    }
}

int main() {
    srand(time(NULL)); // Initialize random seed
    
    // Define the target function to optimize
    int max(int x) { return x; }
    
    // Create the initial population of chromosomes
    Chromosome** population = malloc(POPULATION_SIZE * sizeof(Chromosome*));
    for (int i = 0; i < POPULATION_SIZE; i++) {
        population[i] = init_chromosome(TARGET_VALUE);
    }
    
    // Run the genetic algorithm
    ga_loop(&max, population);
    
    // Free memory
    for (int i = 0; i < POPULATION_SIZE; i++) {
        free(population[i]->genes);
        free(population[i]);
    }
    free(population);
    
    return 0;
}