import numpy as np
from deap import base, creator, tools, algorithms
import networkx as nx
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.spatial.distance import pdist, squareform

# Set the parameters for the problem
POPULATION_SIZE = 100
GENERATIONS = 1000
MUTATION_RATE = 0.1
CROSSOVER_RATE = 0.5

# Create a fitness class and an individual class
creator.create("FitnessMin", base.Fitness, weights=(1.0,))
creator.create("Individual", list, fitness=creator.FitnessMin)

# Define the problem as a graph
G = nx.Graph()
G.add_edge('A', 'B', weight=10)
G.add_edge('A', 'C', weight=15)
G.add_edge('B', 'D', weight=20)
G.add_edge('C', 'D', weight=25)
G.add_edge('C', 'E', weight=30)
G.add_edge('D', 'F', weight=35)
G.add_edge('E', 'F', weight=40)

# Create a distance matrix
distance_matrix = nx.to_pandas_adjacency(G).values

# Define the genetic algorithm
def evaluate(individual):
    # Convert the individual to a route
    route = [G.nodes()[i] for i in individual]
    
    # Calculate the total distance of the route
    total_distance = 0
    for i in range(len(route) - 1):
        total_distance += G.get_edge_data(route[i], route[i+1])['weight']
    total_distance += G.get_edge_data(route[-1], route[0])['weight']  # Add the distance from F to A
    
    # Calculate the fitness
    fitness = 1.0 / total_distance
    
    return (fitness,)

def genetic_algorithm(population_size, generations):
    # Create a population and evaluate it
    population = algorithms.varAnd(population, toolbox, cxpb=CROSSOVER_RATE, mutpb=MUTATION_RATE)
    fitnesses = list(map(evaluate, population))
    
    # Initialize the best individual
    best_individual = min(fitnesses)[0]
    
    for _ in range(generations):
        # Evaluate the new generation
        offspring = algorithms.varAnd(population, toolbox, cxpb=CROSSOVER_RATE, mutpb=MUTATION_RATE)
        fitnesses = list(map(evaluate, offspring))
        
        # Update the best individual
        best_individual = max(fitnesses)[0]
        
        # Replace the population with the new generation
        population = offspring
    
    return best_individual

# Create a toolbox and define the genetic operators
toolbox = base.Toolbox()
toolbox.register("attr_bool", np.random.choice, [True, False])
toolbox.register("individual", tools.initRepeat, creator.Individual, toolbox.attr_bool, 1)
toolbox.register("population", tools.initRepeat, list, toolbox.individual)

# Run the genetic algorithm
best_individual = genetic_algorithm(POPULATION_SIZE, GENERATIONS)

# Print the best individual and its fitness
print("Best Individual:", [G.nodes()[i] for i in best_individual])
print("Fitness:", 1.0 / evaluate(best_individual)[0])

# Plot the optimal route
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
for edge in G.edges():
    ax.plot([G.nodes()[edge[0]], G.nodes()[edge[1]]], [0, 0], [0, 0], 'k-')
ax.scatter(G.nodes(), [0]*len(G.nodes()), [0]*len(G.nodes()))
plt.show()