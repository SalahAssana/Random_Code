% Random Number Generator
% Complexity Level: BEGINNER

% Define the range of random numbers to be generated
min_value = 1;
max_value = 100;

% Generate 10 random numbers within the specified range
random_numbers = randi([min_value max_value], 1, 10);

% Display the generated random numbers
disp(random_numbers);