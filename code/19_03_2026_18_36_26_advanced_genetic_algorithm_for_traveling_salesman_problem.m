% Genetic Algorithm for Traveling Salesman Problem

classdef TSP < handle
    properties
        populationSize
        mutationRate
        crossoverProbability
        distances
        population
    end
    
    methods
        function obj = TSP(distances, populationSize, mutationRate, crossoverProbability)
            obj.populationSize = populationSize;
            obj.mutationRate = mutationRate;
            obj.crossoverProbability = crossoverProbability;
            obj.distances = distances;
            obj.population = zeros(1, populationSize);
            for i = 1:populationSize
                obj.population(i) = randi(size(distances, 1), 1);
            end
        end
        
        function fitness = calculateFitness(obj, individual)
            distance = 0;
            for i = 2:length(individual)
                distance = distance + obj.distances(individual(i-1)+1, individual(i));
            end
            distance = distance + obj.distances(individual(end)+1, individual(1)); % Add the last leg of the trip
            fitness = 1 / (distance^2);
        end
        
        function newPopulation = crossover(obj, population)
            newPopulation = zeros(1, length(population));
            for i = 1:floor(length(population) * obj.crossoverProbability)
                parent1 = randi(length(population), 1);
                parent2 = randi(length(population), 1);
                while parent1 == parent2
                    parent2 = randi(length(population), 1);
                end
                crossoverPoint = randi(length(population), 1);
                newIndividual = [population(parent1)(1:crossoverPoint) population(parent2)(crossoverPoint+1:end)];
                newPopulation(i) = newIndividual;
            end
        end
        
        function newPopulation = mutation(obj, population)
            newPopulation = zeros(1, length(population));
            for i = 1:length(population)
                if rand < obj.mutationRate
                    individual = population(i);
                    crossoverPoint = randi(length(individual), 1);
                    newIndividual = [individual(1:crossoverPoint) circshift(individual(crossoverPoint+1:end), 1)];
                    newPopulation(i) = newIndividual;
                else
                    newPopulation(i) = population(i);
                end
            end
        end
        
        function bestSolution = run(obj)
            generation = 0;
            bestFitness = -inf;
            bestSolution = [];
            while true
                fitnesses = zeros(1, length(obj.population));
                for i = 1:length(obj.population)
                    fitnesses(i) = obj.calculateFitness(obj.population(i));
                end
                [sortedFitnesses, indices] = sort(fitnesses, 'descend');
                selectedIndividuals = obj.population(indices(1:obj.populationSize/2));
                newPopulation = obj.crossover(selectedIndividuals);
                newPopulation = obj.mutation(newPopulation);
                if max(sortedFitnesses) > bestFitness
                    bestFitness = max(sortedFitnesses);
                    bestSolution = obj.population(indices(1));
                end
                generation = generation + 1;
                if generation >= 1000 % Stop after a certain number of generations
                    break
                end
            end
        end
    end
    
end

% Example usage:
distances = [10, 20, 30, 40, 50; ... 
              20, 15, 25, 35, 45; ... 
              30, 25, 10, 20, 30; ... 
              40, 35, 20, 15, 25; ... 
              50, 45, 30, 25, 20];
populationSize = 100;
mutationRate = 0.01;
crossoverProbability = 0.5;

tsp = TSP(distances, populationSize, mutationRate, crossoverProbability);
bestSolution = tsp.run();