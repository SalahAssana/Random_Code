from deap import base, creator, tools, algorithms
import numpy as np
import random

class OptimizationProblemSolver:
    def __init__(self):
        self.individual_length = 10
        self.population_size = 100
        self.generations = 500
        self.mutation_probability = 0.01
        self.crossover_probability = 0.5
        self.constraint_function = self.linear_constraint

    def linear_constraint(self, individual):
        # For this example, we'll use a simple linear constraint:
        return np.sum(individual) - 10

    def evaluate(self, individual):
        fitness = creator.create("FitnessMax", base.Fitness)
        fitness.values = [self.constraint_function(individual)]
        return individual, fitness,

    def genetic_algorithm(self):
        # Create the toolbox
        creator.create("FitnessMax", base.Fitness)
        creator.create("Individual", list, fitness=creator.FitnessMax)
        toolbox = base.Toolbox()

        # Register the evaluation function
        toolbox.register("evaluate", self.evaluate)

        # Register the crossover operator
        toolbox.register("mate", tools.cxTwoPoint)

        # Register the mutation operator
        toolbox.register("mutate", tools.mutFlipBit, indpb=self.mutation_probability)

        # Create the population
        population = toolbox.population(n=self.population_size)

        for _ in range(self.generations):
            offspring = algorithms.varAnd(population, toolbox, cxpb=self.crossover_probability, mutpb=self.mutation_probability)
            fits = [ind.fitness.values[0] for ind in offspring]
            print("Generation {}: Best Fitness {}".format(_, np.max(fits)))

        # Get the best individual
        best_individual = tools.selBest(offspring, 1)[0]

        return best_individual

if __name__ == '__main__':
    solver = OptimizationProblemSolver()
    best_individual = solver.genetic_algorithm()
    print("Best Individual: {}".format(best_individual))