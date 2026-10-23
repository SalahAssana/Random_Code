% Solving the Traveling Salesman Problem using Genetic Algorithm
% Author: [Your Name]
% Date: [Date]

clear; clc;

% Parameters
n_cities = 10;
population_size = 100;
generations = 500;
mutation_rate = 0.01;
crossover_rate = 0.5;
elite_selection = true;

% Initialize population
population = zeros(n_cities, population_size);
for i = 1:population_size
    population(:,i) = randperm(n_cities);
end

% Define fitness function
fitness = @(individual) -sum(cumsum(diff(individual)))/n_cities;

% Main loop
for gen = 1:generations
    % Elite selection
    if elite_selection
        elite_individuals = sortrows(population, fitness(@population(:,1)), 'descend');
        population = [elite_individuals(1,:) ; population];
    end
    
    % Crossover
    for i = 2:floor(population_size/2)
        parent1 = population(:,randi([1 population_size]));
        parent2 = population(:,randi([1 population_size]));
        child1 = crossover(parent1, parent2);
        child2 = crossover(parent2, parent1);
        population(:,[i, i+1]) = [child1, child2];
    end
    
    % Mutation
    for i = 1:population_size
        if rand < mutation_rate
            j = randi([1 n_cities-1]);
            k = randi([j+1 n_cities]);
            population(:,i) = [population(k+1:end, i); population(1:j, i)];
        end
    end
    
    % Fitness evaluation and ranking
    fitness_values = zeros(1, population_size);
    for i = 1:population_size
        fitness_values(i) = fitness(population(:,i));
    end
    [fitness_values, idx] = sort(fitness_values, 'descend');
    population = population(:,idx);
    
    % Convergence check
    if max(fitness_values)/min(fitness_values) < 1.01
        break;
    end
end

% Print the best solution
best_individual = population(:,1);
best_fitness = fitness(best_individual);
fprintf('Best tour: %s\n', num2str(best_individual));
fprintf('Best fitness: %.2f\n', best_fitness);

function child = crossover(parent1, parent2)
    % Single-point crossover
    crossover_point = randi([1 n_cities-1]);
    child = [parent1(1:crossover_point), parent2(crossover_point+1:end)];
end

if __name__ == '__main__':
    % Run the script
    run;
end