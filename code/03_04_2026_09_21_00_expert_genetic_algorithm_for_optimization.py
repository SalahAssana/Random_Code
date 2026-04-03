import numpy as np
from deap import base, creator, tools, algorithms
import random

# Define problem size
N_VIENS = 10
N_ITEMS = 20
CAPACITY = 1000

# Define fitness function
def evaluate(individual):
    # Convert individual to route (list of indices)
    route = [int(x) for x in individual]
    total_distance = 0
    for i in range(N_VIENS - 1):
        total_distance += np.linalg.norm(np.array(route[i]) - np.array(route[i + 1]))
    total_distance += np.linalg.norm(np.array(route[-1]) - np.array(route[0]))
    return (-total_distance,),

# Create fitness class and individual
creator.create("FitnessMin", base.Fitness, weights=(-1.0,))
creator.create("Individual", list, fitness=creator.FitnessMin)

# Define genetic algorithm parameters
TOURNAMENT_SIZE = 3
ELITE_SIZE = 2
POPULATION_SIZE = 100
GENE_MUTATION_PROBABILITY = 0.01
GROWTH_RATE = 1.5

# Create toolbox
toolbox = base.Toolbox()
toolbox.register("attr_bool", random.randint, 0, N_ITEMS)
toolbox.register("individual", tools.initRepeat, creator.Individual, toolbox.attr_bool, n=N_VIENS)
toolbox.register("population", tools.initRepeat, list, toolbox.individual)

# Define genetic algorithm function
def genetic_algorithm(population_size=POPULATION_SIZE):
    # Initialize population
    pop = population(size=population_size)

    for g in range(GENETIC_ALGORITHM_GENERATIONS):
        # Evaluate population fitness
        fitnesses = list(map(evaluate, [individual for individual in pop]))
        fitnesses = [creator.FitnessMin(individual) for individual in fitnesses]

        # Select elite individuals
        elite = tools.selBest(fitnesses, ELITE_SIZE)

        # Perform crossover and mutation
        offspring = algorithms.varAnd(pop, toolbox, cxpb=0.5, mutpb=0.1, elites=elite)

        # Replace population with new generation
        pop = offspring

    return pop

# Run genetic algorithm
best_individuals = []
for _ in range(100):
    best_individual = genetic_algorithm()
    best_individuals.append(max(best_individuals, key=lambda individual: individual.fitness.values[0]))

print("Best individual:", best_individuals)