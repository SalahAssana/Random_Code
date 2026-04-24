% Monte Carlo Simulation for Option Pricing
% Advanced MATLAB Code

classdef Optionsimulator < handle
    methods
        function obj = Optionsimulator(stockPrice, strikePrice, timeToMaturity, riskFreeRate, volatility)
            obj.stockPrice = stockPrice;
            obj.strikePrice = strikePrice;
            obj.timeToMaturity = timeToMaturity;
            obj.riskFreeRate = riskFreeRate;
            obj.volatility = volatility;
        end
        
        function [optionPrice] = estimateOptionPrice(obj, numPaths, numSteps)
            % Monte Carlo Simulation
            paths = zeros(numPaths, numSteps);
            for i = 1:numPaths
                path = obj.stockPrice * exp((obj.riskFreeRate - 0.5*obj.volatility^2) / obj.timeToMaturity + ...
                    obj.volatility * sqrt(obj.timeToMaturity) * randn(numSteps));
                paths(i,:) = path;
            end
            
            % Calculate option price
            callPayoffs = max(paths(:,end) - obj.strikePrice, 0);
            putPayoffs = max(obj.strikePrice - paths(:,end), 0);
            
            callOptionPrice = mean(callPayoffs);
            putOptionPrice = mean(putPayoffs);
            
            % Calculate average option price
            optionPrice = (callOptionPrice + putOptionPrice) / 2;
        end
    end
    
end

% Synthetic data for testing
stockPrice = 100;
strikePrice = 105;
timeToMaturity = 1/12;
riskFreeRate = 0.05;
volatility = 0.20;

numPaths = 10000;
numSteps = 252;

simulator = Optionsimulator(stockPrice, strikePrice, timeToMaturity, riskFreeRate, volatility);
optionPrice = simulator.estimateOptionPrice(numPaths, numSteps);

fprintf('Estimated option price: %.2f\n', optionPrice);