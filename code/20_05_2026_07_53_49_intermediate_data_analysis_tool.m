% Data Analysis Tool - Intermediate Level Project
%
% Description: A program that uses arrays, matrices, and statistics to analyze and visualize data.

% Import necessary libraries
import java.util.*;

% Define a function to calculate the mean of an array
function mean_value = calculate_mean(array)
    mean_value = sum(array) / length(array);
end

% Define a function to calculate the standard deviation of an array
function std_deviation = calculate_std_deviation(array, mean)
    std_deviation = sqrt(sum((array - mean).^2) / (length(array) - 1));
end

% Define a function to generate random synthetic data
function [x, y] = generate_synthetic_data(num_samples)
    x = rand(1, num_samples);
    y = 3 * x + 0.5 * randn(1, num_samples) + 2;
end

% Main script
if nargin == 0
    % Generate synthetic data if no input is provided
    [x, y] = generate_synthetic_data(100);
else
    % Use the input data instead of generating new synthetic data
    x = [];
    y = [];
end

% Calculate and display the mean and standard deviation of the data
mean_value = calculate_mean(y);
std_deviation = calculate_std_deviation(y, mean_value);

fprintf('Mean: %.2f\n', mean_value);
fprintf('Standard Deviation: %.2f\n', std_deviation);

% Plot the data using a scatter plot
figure;
scatter(x, y);
xlabel('X');
ylabel('Y');
title('Data Scatter Plot');