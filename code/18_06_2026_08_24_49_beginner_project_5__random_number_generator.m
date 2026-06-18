% Project 5: Random Number Generator
% BEGINNER complexity project

% Import necessary libraries
rng default; % Set random seed for reproducibility
rand_num = zeros(1,10); % Initialize array to store 10 random numbers

% Prompt user for range and distribution parameters
min_val = input('Enter minimum value (inclusive): ');
max_val = input('Enter maximum value (inclusive): ');
distribution = input('Enter distribution type (0: uniform, 1: normal): ');

% Generate random numbers based on user input
if distribution == 0 % Uniform distribution
    rand_num = min_val + (max_val - min_val + 1) * rand(1,10);
elseif distribution == 1 % Normal distribution
    mean_val = (min_val + max_val)/2; % Calculate mean value
    std_dev = (max_val - min_val)/3.5; % Calculate standard deviation
    rand_num = mean_val + std_dev*randn(1,10);
end

% Display the generated random numbers
fprintf('Random Numbers:\n');
fprintf('%f ', rand_num);
fprintf('\n');