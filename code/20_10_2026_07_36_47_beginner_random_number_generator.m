% Random Number Generator
% BEGINNER complexity project

% Import necessary libraries
clc; clear all;

% Define the range for random number generation
min_value = 1;
max_value = 100;

% Generate a random integer within the specified range
random_number = randi([min_value max_value], 1, 1);

% Display the generated random number
fprintf('Random Number: %d\n', random_number);