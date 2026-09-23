% Random Number Generator
% Author: Your Name (Replace this)

clear all; close all; clc;

% Define the range for random number generation
min_val = 1;
max_val = 100;

% Generate a single random number within the defined range
random_num = randi([min_val, max_val]);

% Display the generated random number
fprintf('Random Number: %d\n', random_num);

% Repeat the process to generate multiple random numbers
for i = 1:10
    random_num = randi([min_val, max_val]);
    fprintf('Random Number %d: %d\n', i, random_num);
end