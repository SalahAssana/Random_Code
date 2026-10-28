from deap import base, creator, tools, algorithms
import numpy as np
import random
import math

# Define the fitness function
def eval_fit(individual):
    # Convert individual to a list of floats
    individual = [float(x) for x in individual]
    
    # Calculate the objective function value
    sum_squared_diffs = sum((individual[i] - i ** 2) ** 2 for i in range(5))
    return (-sum_squared_diffs,)  # The minus sign is because DEAP uses minimization by default

# Create a fitness class and an individual class
creator.create("FitnessMin", base.Fitness, weights=(-1.0,))
creator.create("Individual", list, fitness=creator.FitnessMin)

# Define the genetic algorithm parameters
toolbox = base.Toolbox()
toolbox.register("attr_bool", random.randint, 0, 1)
toolbox.register("individual", tools.initRepeat, creator.Individual, toolbox.attr_bool, 5)
toolbox.register("population", tools.initRepeat, list, toolbox.individual)
toolbox.register("evaluate", eval_fit)
toolbox.register("mate", tools.cxTwoPoint)
toolbox.register("mutate", tools.mutFlipBit, indpb=0.05)
toolbox.register("select", tools.selTournament, tournsize=3)

# Define the genetic algorithm
def main():
    # Create a population of 40 individuals
    pop = toolbox.population(n=40)
    
    # Evaluate the initial population
    fitnesses = list(map(toolbox.evaluate, pop))
    for ind, fit in zip(pop, fitnesses):
        ind.fitness.values = fit
    
    # Evolve the population over 50 generations
    for g in range(50):
        # Select parents
        offspring = algorithms.varAnd(pop, toolbox, cxpb=0.5, mutpb=0.1)
        
        # Evaluate the new population
        fitnesses = list(map(toolbox.evaluate, offspring))
        for ind, fit in zip(offspring, fitnesses):
            ind.fitness.values = fit
        
        # Replace the worst 10% of individuals with the new population
        pop = tools.selReplace(pop, offspring, 0.1)
    
    # Print the best individual
    best_individual = tools.selBest(pop, 1)[0]
    print("Best individual:", best_individual)

if __name__ == '__main__':
    main()