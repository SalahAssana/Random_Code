import random
import math
from deap import base, creator, tools

# Problem parameters
CITY_COUNT = 20
POPULATION_SIZE = 100
GENERATIONS = 2000
MUTATION_RATE = 0.01
CROSSOVER_RATE = 0.5
CHROMOSOME_LENGTH = CITY_COUNT - 1

# Define the fitness function
def evaluate(individual):
    distance = 0
    for i in range(CHROMOSOME_LENGTH):
        start = individual[i]
        end = individual[(i + 1) % CHROMOSOME_LENGTH]
        distance += math.sqrt((end[0] - start[0])**2 + (end[1] - start[1])**2)
    return -distance,

# Create the fitness function and the problem type
creator.create("FitnessMin", base.Fitness, weights=(-1.0,))
creator.create("Individual", list, fitness=creator.FitnessMin)

# Generate the population
toolbox = base.Toolbox()
toolbox.register("attr_bool", random.randint, 0, CITY_COUNT)
toolbox.register("individual", tools.initRepeat, creator.Individual, toolbox.attr_bool, n=CHROMOSOME_LENGTH)
toolbox.register("population", tools.initRepeat, list, toolbox.individual)

# Register the genetic operators
toolbox.register("mate", tools.cxOrdered)
toolbox.register("mutate", tools.mutGaussian, mu=0, sigma=1, indpb=MUTATION_RATE)
toolbox.register("select", tools.selTournament, tournsize=3)

# Create the population and evaluate its individuals
population = toolbox.population(n=POPULATION_SIZE)
fitnesses = list(map(evaluate, population))

# Run the genetic algorithm
for generation in range(GENERATIONS):
    offspring = toolbox.select(population, len(population))
    children = []
    for parent1, parent2 in zip(offspring[::2], offspring[1::2]):
        child1, child2 = toolbox.mate(parent1, parent2)
        del child1.fitness.values
        del child2.fitness.values
        children.append(child1)
        children.append(child2)
    for child in children:
        toolbox.mutate(child)
        del child.fitness.values
    fitnesses = list(map(evaluate, children))
    population[:] = offspring
    population.extend(children)

# Evaluate the best individual
best_individual = tools.selBest(population, 1)[0]
print("Best solution: ", best_individual)
print("Distance: ", -fitnesses[population.index(best_individual)][0])