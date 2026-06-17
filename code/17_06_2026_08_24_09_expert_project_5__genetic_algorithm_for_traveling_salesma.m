% Project 5: Genetic Algorithm for Traveling Salesman Problem

% Initialization
clear; close all; clc;

% Function to calculate distance between two cities
function dist = distance(cities1, cities2)
    num_cities = size(cities1, 1);
    total_distance = 0;
    for i = 1:num_cities-1
        total_distance = total_distance + sqrt((cities2(i+1, 1) - cities1(i, 1))^2 + (cities2(i+1, 2) - cities1(i, 2))^2);
    end
    dist = total_distance;
end

% Function to generate the initial population of chromosomes
function pop = generate_population(num_cities, num_chromosomes, max_distance)
    pop = zeros(num_cities, num_chromosomes);
    for i = 1:num_chromosomes
        chromosome = randperm(num_cities);
        pop(:, i) = chromosome;
    end
end

% Function to calculate the fitness of a chromosome
function fitness = calculate_fitness(chromosome, cities)
    distance = 0;
    for i = 1:size(cities, 1)-1
        distance = distance + sqrt((cities(chromosome(i+1), 1) - cities(chromosome(i), 1))^2 + (cities(chromosome(i+1), 2) - cities(chromosome(i), 2))^2);
    end
    fitness = 1 / (distance + eps);
end

% Function to perform crossover on a pair of chromosomes
function [child1, child2] = crossover(parent1, parent2)
    % Select a random crossover point
    crossover_point = randi([2, size(parent1, 1)-1]);
    
    % Create the children by combining the parents
    child1 = [parent1(1:crossover_point), parent2(crossover_point+1:end)];
    child2 = [parent2(1:crossover_point), parent1(crossover_point+1:end)];
end

% Function to perform mutation on a chromosome
function mutated_chromosome = mutate(chromosome, max_distance)
    % Select a random position for the mutation
    mutation_position = randi([1, size(chromosome, 1)]);
    
    % Create a new chromosome by swapping two cities at the selected position
    new_chromosome = chromosome;
    i = randi([1, size(chromosome, 1)-1]);
    j = i + 1;
    while j == i
        j = randi([1, size(chromosome, 1)-1]);
    end
    new_chromosome([i, j]) = new_chromosome([j, i]);
    
    mutated_chromosome = new_chromosome;
end

% Main genetic algorithm loop
function best_chromosome = genetic_algorithm(num_cities, num_chromosomes, population_size, mutation_rate, generations)
    % Generate the initial population of chromosomes
    pop = generate_population(num_cities, num_chromosomes, 1000);
    
    % Evaluate the fitness of each chromosome in the population
    fitnesses = zeros(1, size(pop, 2));
    for i = 1:size(pop, 2)
        fitnesses(i) = calculate_fitness(pop(:, i), [rand(num_cities, 1); pop(1, :)]);
    end
    
    % Select the best chromosomes to form the next generation
    indices = zeros(1, population_size);
    for i = 1:population_size
        indices(i) = find(fitnesses == max(fitnesses), 1, 'last');
        fitnesses(indices(i)) = -Inf;
    end
    selected_chromosomes = pop(:, indices);
    
    % Perform crossover and mutation to generate the next generation
    for i = 1:population_size/2
        parent1 = selected_chromosomes(:, randi([1, population_size]));
        parent2 = selected_chromosomes(:, find(indices ~= parent1));
        child1 = crossover(parent1, parent2);
        child2 = crossover(parent1, parent2);
        
        % Apply mutation to the children with a certain probability
        for j = 1:population_size/2
            if rand < mutation_rate
                child1(:, j) = mutate(child1(:, j), 1000);
                child2(:, j) = mutate(child2(:, j), 1000);
            end
        end
        
        % Add the children to the selected chromosomes
        selected_chromosomes = [selected_chromosomes, child1; selected_chromosomes, child2];
    end
    
    % Evaluate the fitness of each chromosome in the new generation
    fitnesses = zeros(1, size(selected_chromosomes, 2));
    for i = 1:size(selected_chromosomes, 2)
        fitnesses(i) = calculate_fitness(selected_chromosomes(:, i), [rand(num_cities, 1); selected_chromosomes(1, :)]);
    end
    
    % Select the best chromosome from the new generation
    best_index = find(fitnesses == max(fitnesses), 1, 'last');
    best_chromosome = selected_chromosomes(:, best_index);
    
    % Perform crossover and mutation for a specified number of generations
    for i = 2:generations
        % Select the best chromosomes to form the next generation
        indices = zeros(1, population_size);
        for j = 1:population_size
            indices(j) = find(fitnesses == max(fitnesses), 1, 'last');
            fitnesses(indices(j)) = -Inf;
        end
        selected_chromosomes = pop(:, indices);
        
        % Perform crossover and mutation to generate the next generation
        for j = 1:population_size/2
            parent1 = selected_chromosomes(:, randi([1, population_size]));
            parent2 = selected_chromosomes(:, find(indices ~= parent1));
            child1 = crossover(parent1, parent2);
            child2 = crossover(parent1, parent2);
            
            % Apply mutation to the children with a certain probability
            for k = 1:population_size/2
                if rand < mutation_rate
                    child1(:, k) = mutate(child1(:, k), 1000);
                    child2(:, k) = mutate(child2(:, k), 1000);
                end
            end
            
            % Add the children to the selected chromosomes
            selected_chromosomes = [selected_chromosomes, child1; selected_chromosomes, child2];
        end
        
        % Evaluate the fitness of each chromosome in the new generation
        fitnesses = zeros(1, size(selected_chromosomes, 2));
        for j = 1:size(selected_chromosomes, 2)
            fitnesses(j) = calculate_fitness(selected_chromosomes(:, j), [rand(num_cities, 1); selected_chromosomes(1, :)]);
        end
        
        % Select the best chromosome from the new generation
        best_index = find(fitnesses == max(fitnesses), 1, 'last');
        best_chromosome = selected_chromosomes(:, best_index);
    end
    
    best_chromosome;
end

% Main function to run the genetic algorithm
function main()
    % Parameters for the problem
    num_cities = 20;
    num_chromosomes = 1000;
    population_size = 50;
    mutation_rate = 0.01;
    generations = 500;
    
    % Run the genetic algorithm
    best_chromosome = genetic_algorithm(num_cities, num_chromosomes, population_size, mutation_rate, generations);
end

main();