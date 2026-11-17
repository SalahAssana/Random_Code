import numpy as np
from deap import base, creator, tools, algorithms
import pandas as pd
from sklearn.preprocessing import MinMaxScaler
from keras.models import Sequential
from keras.layers import LSTM, Dense

# Parameters
POPULATION_SIZE = 100
GENERATIONS = 500
TOURNAMENT_SIZE = 3
MUTATION_PROBABILITY = 0.1
CRITERION_FUNCTION_WEIGHTS = [0.5, 0.25, 0.25]

# Synthetic data generation
np.random.seed(42)
data = pd.DataFrame({
    'Open': np.random.uniform(50, 100, size=(1000,)),
    'High': np.random.uniform(50, 100, size=(1000,)),
    'Low': np.random.uniform(50, 100, size=(1000,)),
    'Close': np.random.uniform(50, 100, size=(1000,))
})

# Data preprocessing
scaler = MinMaxScaler()
data[['Open', 'High', 'Low', 'Close']] = scaler.fit_transform(data)

# Define the stock portfolio return function
def calculate_returns(individual):
    weights = individual
    returns = np.sum((weights * data['Close']).diff(), axis=0)
    return -np.mean(returns),  # Minimize the negative return

# Create a fitness class and an individual class
creator.create("FitnessMin", base.Fitness, weights=(-1.0,))
creator.create("Individual", list, fitness=creator.FitnessMin)

# Define the genetic algorithm
def ga(data):
    # Initialize the population
    pop = algorithms.eaSimplePop(
        creator.Individual(list(np.random.uniform(0, 1, size=(data.shape[1],)))), 
        toolbox=base.Toolbox(),
        Npc=POPULATION_SIZE,
        CXPB=MUTATION_PROBABILITY,
        mutate=lambda ind: [np.random.uniform(0, 1) if np.random.rand() < MUTATION_PROBABILITY else x for x in ind]
    )

    # Evaluate the population
    fitnesses = list(map(calculate_returns, pop))
    for ind, fit in zip(pop, fitnesses):
        ind.fitness.values = fit

    # Run the genetic algorithm
    for _ in range(GENERATIONS):
        offspring = algorithms.varAnd(pop, toolbox=base.Toolbox(), cxpb=MUTATION_PROBABILITY)
        fits = map(calculate_returns, offspring)
        for fit, ind in zip(fits, offspring):
            ind.fitness.values = fit
        pop = toolbox.select(offspring, k=len(pop))

    # Return the best individual
    return min(pop, key=lambda x: x.fitness.values).fitness.values[0]

# Run the genetic algorithm and print the result
if __name__ == '__main__':
    result = ga(data)
    print(f"Best portfolio return: {result:.4f}")