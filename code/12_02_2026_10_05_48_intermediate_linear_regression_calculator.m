% Linear Regression Calculator
%
% This script calculates linear regression coefficients (slope and intercept)
% using NumPy and Pandas in MATLAB.

function lineRegCalculator
    % Clear command window
    clear all
    
    % Define function to calculate linear regression
    function [slope, intercept] = linearRegression(x, y)
        % Calculate mean of x and y
        meanX = mean(x);
        meanY = mean(y);
        
        % Calculate numerator for slope calculation
        numerator = sum((x - meanX) .* (y - meanY));
        
        % Calculate denominator for slope calculation
        denominator = sum((x - meanX).^2);
        
        % Calculate slope using formula: (Σ(x - x̄)(y - ȳ)) / Σ(x - x̄)^2
        slope = numerator ./ denominator;
        
        % Calculate intercept using formula: ȳ - m * x̄
        intercept = meanY - slope .* meanX;
    end
    
    % Define function to visualize data and regression line
    function plotDataAndRegression(x, y, slope, intercept)
        % Plot original data
        scatter(x, y);
        
        % Calculate regression line values
        minX = min(x);
        maxX = max(x);
        xValues = [minX:0.1:maxX];
        yValues = slope .* xValues + intercept;
        
        % Plot regression line
        plot(xValues, yValues);
    end
    
    % Synthetic data for testing
    x = [1 2 3 4 5];
    y = [2 3 5 7 11];
    
    % Calculate linear regression coefficients
    [slope, intercept] = linearRegression(x, y);
    
    % Plot original data and regression line
    plotDataAndRegression(x, y, slope, intercept);
end

lineRegCalculator