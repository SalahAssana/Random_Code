% Particle Swarm Optimization in MATLAB
classdef Particle < handle
    properties
        position
        velocity
        personalBest
        fitness
        inertia
        cognitive
        social
    end
    
    methods
        function obj = Particle(nDimensions, lowerBound, upperBound)
            obj.position = rand(1,nDimensions) * (upperBound - lowerBound) + lowerBound;
            obj.velocity = zeros(1,nDimensions);
            obj.personalBest = obj.position;
            obj.fitness = NaN;
            obj.inertia = 0.729;
            obj.cognitive = 1.494;
            obj.social = 1.494;
        end
        
        function update(obj, globalBest)
            % Update velocity
            obj.velocity = obj.inertia * obj.velocity + ...
                obj.cognitive * rand() * (obj.personalBest - obj.position) + ...
                obj.social * rand() * (globalBest - obj.position);
            
            % Update position
            obj.position = obj.position + obj.velocity;
        end
        
        function newFitness = evaluate(obj, fitnessFunction)
            % Evaluate the fitness of the particle
            newFitness = fitnessFunction(obj.position);
            if isnan(obj.fitness) || newFitness < obj.fitness
                obj.personalBest = obj.position;
                obj.fitness = newFitness;
            end
        end
        
        function [bestPosition, bestFitness] = getResults(obj)
            % Get the results of the particle
            bestPosition = obj.personalBest;
            bestFitness = obj.fitness;
        end
    end
end

classdef PSO < handle
    properties
        particles
        dimensions
        lowerBound
        upperBound
        fitnessFunction
        globalBest
        globalBestFitness
    end
    
    methods
        function obj = PSO(nParticles, nDimensions, lowerBound, upperBound, fitnessFunction)
            obj.particles = zeros(1,nParticles);
            for i = 1:nParticles
                obj.particles(i) = Particle(nDimensions, lowerBound, upperBound);
            end
            obj.dimensions = nDimensions;
            obj.lowerBound = lowerBound;
            obj.upperBound = upperBound;
            obj.fitnessFunction = fitnessFunction;
        end
        
        function run(obj)
            % Initialize global best
            obj.globalBestFitness = inf;
            obj.globalBest = zeros(1,obj.dimensions);
            
            for i = 1:10000
                for j = 1:length(obj.particles)
                    % Update particle velocity and position
                    obj.particles(j).update(obj.globalBest);
                    
                    % Evaluate the fitness of each particle
                    newFitness = obj.particles(j).evaluate(@obj.fitnessFunction);
                    
                    if newFitness < obj.globalBestFitness
                        % Update global best
                        obj.globalBest = obj.particles(j).position;
                        obj.globalBestFitness = newFitness;
                    end
                end
            end
        end
        
        function [bestPosition, bestFitness] = getResults(obj)
            % Get the results of the PSO algorithm
            bestPosition = obj.globalBest;
            bestFitness = obj.globalBestFitness;
        end
    end
end

% Define a fitness function for testing
function fitness = sphere(x)
    fitness = sum((x-5).^2);
end

% Create an instance of the PSO algorithm and run it
pso = PSO(20, 10, -5, 5, @sphere);
pso.run();

% Get the results of the PSO algorithm
[bestPosition, bestFitness] = pso.getResults();
fprintf('Best position: %f\n', bestPosition');