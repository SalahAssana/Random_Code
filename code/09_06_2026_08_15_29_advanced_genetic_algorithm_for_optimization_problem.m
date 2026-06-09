% Genetic Algorithm for Optimization Problem
classdef OptimizeProblem < handle
    properties
        populationSize
        generations
        mutationRate
        crossoverRate
        eliteCount
        bestSolution
    end
    
    methods
        function obj = OptimizeProblem(populationSize, generations, mutationRate, crossoverRate, eliteCount)
            obj.populationSize = populationSize;
            obj.generations = generations;
            obj.mutationRate = mutationRate;
            obj.crossoverRate = crossoverRate;
            obj.eliteCount = eliteCount;
            obj.bestSolution = [];
        end
        
        function [population, fitness] = InitializePopulation(obj)
            population = rand(1, obj.populationSize);
            fitness = -population .* (2 * population - 3); % Example optimization problem: minimize the function f(x) = x^2 + (x-1)^2
        end
        
        function [newPopulation, bestIndividual] = Evolve(obj, population)
            % Selection
            fitness = -population .* (2 * population - 3);
            [~, indices] = sort(fitness);
            eliteInds = indices(1:obj.eliteCount);
            
            % Crossover
            offspring = zeros(1, obj.populationSize);
            for i = 1:obj.populationSize/2
                parent1 = population(eliteInds(i));
                parent2 = population(eliteInds(obj.populationSize-i+1));
                crossoverPoint = randi([1, 3]);
                child = (parent1(1:crossoverPoint) .* (1 - obj.crossoverRate)) + ...
                    (parent2(crossoverPoint+1:end) .* (obj.crossoverRate));
                offspring(i*2-1:i*2) = child;
            end
            
            % Mutation
            for i = 1:obj.populationSize/2
                if rand < obj.mutationRate
                    mutationIndex = randi([1, length(offspring)]);
                    offspring(i*2+mutationIndex) = rand;
                end
            end
            
            newPopulation = [population(eliteInds); offspring];
            bestIndividual = max(newPopulation);
        end
        
        function PlotResults(obj)
            figure
            plot(-obj.bestSolution .* (2 * obj.bestSolution - 3));
            title('Optimization Problem Solution');
        end
    end
end

% Main script
if true % Adjust parameters as needed
    populationSize = 100;
    generations = 1000;
    mutationRate = 0.1;
    crossoverRate = 0.5;
    eliteCount = 10;
else
    populationSize = 50;
    generations = 500;
    mutationRate = 0.05;
    crossoverRate = 0.3;
    eliteCount = 5;
end

problem = OptimizeProblem(populationSize, generations, mutationRate, crossoverRate, eliteCount);
[population, fitness] = problem.InitializePopulation();
for i = 1:generations
    [newPopulation, bestIndividual] = problem.Evolve(population);
    population = newPopulation;
    if ~isempty(problem.bestSolution)
        if -bestIndividual .* (2 * bestIndividual - 3) > -problem.bestSolution .* (2 * problem.bestSolution - 3)
            problem.bestSolution = bestIndividual;
        end
    else
        problem.bestSolution = bestIndividual;
    end
end

problem.PlotResults();