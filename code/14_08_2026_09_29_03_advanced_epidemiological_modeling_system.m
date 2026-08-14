% Epidemiological Modeling System
% Advanced complexity project in MATLAB

classdef DiseaseModel < handle
    properties
        populationSize
        infectedIndividuals
        recoveredIndividuals
        deceasedIndividuals
        transmissionRate
        recoveryRate
        mortalityRate
        timeStep
        timeElapsed
    end
    
    methods
        function obj = initialize(populationSize, transmissionRate, recoveryRate, mortalityRate)
            % Initialize the disease model with given parameters
            obj.populationSize = populationSize;
            obj.infectedIndividuals = 1; % Single infected individual to start with
            obj.recoveredIndividuals = 0;
            obj.deceasedIndividuals = 0;
            obj.transmissionRate = transmissionRate;
            obj.recoveryRate = recoveryRate;
            obj.mortalityRate = mortalityRate;
            obj.timeStep = 0.1; % Time step for simulation
            obj.timeElapsed = 0;
        end
        
        function [newInfected, newRecovered, newDeceased] = simulate(obj)
            % Simulate the spread of disease based on current state and parameters
            newInfected = 0;
            newRecovered = 0;
            newDeceased = 0;
            
            for i = 1:obj.infectedIndividuals
                if rand < obj.transmissionRate / (obj.populationSize - obj.infectedIndividuals)
                    newInfected = newInfected + 1;
                end
            end
            
            for i = 1:obj.infectedIndividuals
                if rand < obj.recoveryRate
                    obj.infectedIndividuals = obj.infectedIndividuals - 1;
                    newRecovered = newRecovered + 1;
                elseif rand < (obj.transmissionRate / (obj.populationSize - obj.infectedIndividuals)) * (1 - obj.recoveryRate)
                    newInfected = newInfected + 1;
                else
                    newDeceased = newDeceased + 1;
                    obj.infectedIndividuals = obj.infectedIndividuals - 1;
                end
            end
            
            % Update time elapsed
            obj.timeElapsed = obj.timeElapsed + obj.timeStep;
        end
        
        function plotResults(obj)
            % Plot the results of the simulation
            figure;
            plot((0:obj.timeStep:obj.timeElapsed), [obj.infectedIndividuals, obj.recoveredIndividuals, obj.deceasedIndividuals]);
            xlabel('Time (days)');
            ylabel('Number of individuals');
            title('Disease Spread Simulation Results');
        end
    end
end

% Synthetic data for demonstration purposes
populationSize = 1000;
transmissionRate = 0.01;
recoveryRate = 0.5;
mortalityRate = 0.05;

model = DiseaseModel();
model.initialize(populationSize, transmissionRate, recoveryRate, mortalityRate);

for i = 1:50
    [newInfected, newRecovered, newDeceased] = model.simulate();
end

model.plotResults();

% Run the simulation and plot the results