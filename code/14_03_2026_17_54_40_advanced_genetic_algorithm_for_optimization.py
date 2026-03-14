import numpy as np
from scipy.optimize import minimize
import random

class Population:
    def __init__(self, size):
        self.size = size
        self.population = [np.random.rand(2) for _ in range(size)]

    def evaluate(self, func):
        return [func(individual) for individual in self.population]

    def crossover(self, p1, p2):
        child = (p1[0] + p2[0]) / 2
        return child

    def mutation(self, individual):
        if random.random() < 0.5:
            individual[0] += np.random.uniform(-0.1, 0.1)
        if random.random() < 0.5:
            individual[1] += np.random.uniform(-0.1, 0.1)
        return individual

    def evolve(self, func, mutation_rate):
        population = self.population
        fitness = self.evaluate(func)
        indices = np.argsort(fitness)

        parents = [population[i] for i in indices[:int(0.2 * len(indices))]]
        children = []

        while len(parents) > 0:
            p1 = random.choice(parents)
            parents.remove(p1)
            if len(parents) > 0:
                p2 = random.choice(parents)
                parents.remove(p2)

                child = self.crossover(p1, p2)
                child = self.mutation(child)

                children.append(child)
                for _ in range(3):
                    parent = random.choice(parents)
                    if len(parents) > 0:
                        parents.remove(parent)
                        children.append(self.mutation(parent))
        population = children
        return Population(len(population)), fitness[indices[:int(0.2 * len(indices)))]


def func(individual):
    x, y = individual
    return -(x**2 + y**2)


if __name__ == '__main__':
    size = 100
    pop = Population(size)
    best, _ = minimize(func, np.array([1, 1]), method="SLSQP")
    print("Best solution:", best)