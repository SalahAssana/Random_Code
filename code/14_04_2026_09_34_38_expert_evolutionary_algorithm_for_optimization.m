% Evolutionary Algorithm for Optimization
%
% This program uses genetic algorithms to optimize a complex function,
% featuring mutation, selection, and crossover operators.

function optimized_results = evolutionary_algorithm()
    % Define the optimization problem: Rastrigin's Function
    fitness_function = @(x) -sum(x.*cos(2*pi*x) + x.^2 .* 10 * sin(2*pi*x));

    % Set parameters for the genetic algorithm
    population_size = 100;
    generations = 500;
    mutation_rate = 0.01;
    crossover_rate = 0.5;

    % Initialize the population with random values
    population = rand(population_size, 1);

    % Run the genetic algorithm for the specified number of generations
    for generation = 1:generations
        % Evaluate the fitness of each individual in the population
        fitness = zeros(1, population_size);
        for i = 1:population_size
            fitness(i) = fitness_function(population(i));
        end

        % Perform selection based on fitness
        selected_individuals = population;
        selected_fitness = fitness;
        [selected_individuals, selected_fitness] = sortrows([selected_individuals, selected_fitness], 2, 'descend');

        % Crossover (single-point crossover)
        offspring = zeros(1, population_size);
        for i = 1:population_size/2
            parent1 = selected_individuals(i);
            parent2 = selected_individuals(end-i+1);
            crossover_point = randi([1, 10]);
            offspring(2*i-1) = (parent1 + parent2)/2;
            offspring(2*i) = (parent1 * parent2)/2;
        end

        % Mutation
        for i = 1:population_size
            if rand < mutation_rate
                selected_individuals(i) = rand;
            end
        end

        % Replace the least fit individuals with new offspring
        population(selected_fitness < selected_fitness(1, end-5)) = offspring;

        % Display progress every 10 generations
        if mod(generation, 10) == 0
            disp(['Generation ', num2str(generation)]);
        end
    end

    % Return the optimized results
    optimized_results = population(selected_fitness > selected_fitness(1, end-5));
end

% Run the evolutionary algorithm
optimized_results = evolutionary_algorithm();