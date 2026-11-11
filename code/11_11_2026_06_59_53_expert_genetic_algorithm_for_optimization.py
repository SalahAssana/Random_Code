import random
import numpy as np

class GeneticAlgorithm:
    def __init__(self, population_size, generations, mutation_rate):
        self.population_size = population_size
        self.generations = generations
        self.mutation_rate = mutation_rate
        self.elite_individuals = int(population_size * 0.1)
        self.population = [random.random() for _ in range(population_size)]
        self.best_individual = max(self.population)

    def evolve(self):
        new_population = []
        for _ in range(self.population_size):
            parent1, parent2 = random.sample(self.population, 2)
            child = self.crossover(parent1, parent2)
            if np.random.rand() < self.mutation_rate:
                child = self.mutate(child)
            new_population.append(max([child, self.best_individual]))
        return new_population

    def crossover(self, parent1, parent2):
        midpoint = len(parent1) // 2
        child = parent1[:midpoint] + [x for x in parent2 if x not in parent1[:midpoint]]
        return child

    def mutate(self, individual):
        for i in range(len(individual)):
            if np.random.rand() < self.mutation_rate:
                individual[i] = random.random()
        return individual

    def run(self):
        population = self.population
        for _ in range(self.generations):
            population = self.evolve()
            self.best_individual = max(population)
        return self.best_individual

if __name__ == '__main__':
    ga = GeneticAlgorithm(100, 500, 0.1)
    best_individual = ga.run()
    print("Best individual:", best_individual)