#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import random
import time
from deap import base, creator, tools, algorithms

def get_fitness(individual):
    return -sum(x for x in individual),

def genetic_algorithm(n_individuals=100, n_generations=500, n_variables=10):
    # Create a fitness function and an individual class
    creator.create("FitnessMin", base.Fitness, weights=(-1.0,))
    creator.create("Individual", list, fitness=creator.FitnessMin)

    # Define the toolbox
    toolbox = base.Toolbox()
    toolbox.register("attr_bool", random.random)
    toolbox.register("individual", tools.initRepeat, creator.Individual, toolbox.attr_bool, n_variables)
    toolbox.register("population", tools.initRepeat, list, toolbox.individual)
    toolbox.register("mate", tools.cxTwoPoint)
    toolbox.register("mutate", tools.mutFlipBit, indpb=0.05)
    toolbox.register("select", tools.selTournament, tournsize=3)

    # Create the population
    pop = toolbox.population(n_individuals)

    # Evaluate the initial population
    fitnesses = list(map(get_fitness, pop))
    for indiv, fit in zip(pop, fitnesses):
        indiv.fitness.values = fit

    # Run the genetic algorithm
    start_time = time.time()
    final_pop = algorithms.eaSimple(pop, toolbox, cxpb=0.5, mutpb=0.1, ngen=n_generations, verbose=False)
    end_time = time.time()

    # Print the best individual and its fitness
    best_individual = tools.selBest(final_pop, 1)[0]
    print(f"Best individual: {best_individual}")
    print(f"Fitness: {-sum(x for x in best_individual),}")

if __name__ == '__main__':
    genetic_algorithm()