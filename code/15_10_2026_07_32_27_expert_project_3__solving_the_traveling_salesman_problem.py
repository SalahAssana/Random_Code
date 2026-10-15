import random
import math
from deap import base, creator, tools

# Define the problem parameters
POPULATION_SIZE = 100
GENE_COUNT = 30
MUTATION_PROBABILITY = 0.01
CROSSOVER_RATE = 0.5
TOURNAMENT_SIZE = 3
ELITISM = 1

# Function to calculate the fitness (distance) of a route
def evaluate(individual):
    distance = 0
    for i in range(len(individual)-1):
        distance += math.sqrt((points[individual[i]][0] - points[individual[i+1]][0])**2 + 
                               (points[individual[i]][1] - points[individual[i+1]][1])**2)
    return distance,

# Function to create a new individual
def create_individual():
    individual = random.sample(range(GENE_COUNT), GENE_COUNT)
    return individual,

# Create the creator function and toolbox
creator.create("FitnessMin", base.Fitness, weights=(-1.0,))
creator.create("Individual", list, fitness=creator.FitnessMin)

toolbox = base.Toolbox()

toolbox.register("individual", create_individual)
toolbox.register("population", tools.initRepeat, list, toolbox.individual)
toolbox.register("mate", tools.cxTwoPoint)
toolbox.register("mutate", tools.mutGaussian, mu=0, sigma=1, indpb=MUTATION_PROBABILITY)
toolbox.register("select", tools.selTournament, tournsize=TOURNAMENT_SIZE)

# Create the population and evaluate the initial individuals
population = toolbox.population(n=POPULATION_SIZE)
for individual in population:
    fitness = evaluate(individual)
    individual.setfitness(*fitness)

# Run the genetic algorithm for 1000 generations
best_individual = None
for generation in range(1000):
    offspring = toolbox.select(population, k=len(population))
    for child1, child2 in zip(offspring[::2], offspring[1::2]):
        if random.random() < CROSSOVER_RATE:
            toolbox.mate(child1, child2)
    for mutant in population:
        if random.random() < MUTATION_PROBABILITY:
            toolbox.mutate(mutant)
    fits = [individual.fitness.values[0] for individual in population]
    best_individual = max(range(len(fits)), key=lambda i:fits[i])
    
if __name__ == '__main__':
    # Read the points from a file
    with open("points.txt", "r") as f:
        points = [[int(x) for x in line.split(",")] for line in f.readlines()]
    
    # Run the genetic algorithm
    population = toolbox.population(n=POPULATION_SIZE)
    for individual in population:
        fitness = evaluate(individual)
        individual.setfitness(*fitness)
    
    # Run the genetic algorithm for 1000 generations
    best_individual = None
    for generation in range(1000):
        offspring = toolbox.select(population, k=len(population))
        for child1, child2 in zip(offspring[::2], offspring[1::2]):
            if random.random() < CROSSOVER_RATE:
                toolbox.mate(child1, child2)
        for mutant in population:
            if random.random() < MUTATION_PROBABILITY:
                toolbox.mutate(mutant)
        fits = [individual.fitness.values[0] for individual in population]
        best_individual = max(range(len(fits)), key=lambda i:fits[i])
    
    # Print the best route
    best_route = population[best_individual]
    print("Best route:", best_route)
    print("Distance:", evaluate(best_route)[0][0], "units")