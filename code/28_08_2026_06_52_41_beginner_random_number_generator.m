% Random Number Generator
%
% Generate random numbers within a specified range.

% Set the seed for reproducibility
rng(0);

% Define the lower and upper bounds of the range
lowerBound = 1;
upperBound = 100;

% Generate 10 random numbers within the specified range
randomNumbers = randi([lowerBound, upperBound], 1, 10);

% Display the generated random numbers
fprintf('Random Numbers: %d\n', randomNumbers);