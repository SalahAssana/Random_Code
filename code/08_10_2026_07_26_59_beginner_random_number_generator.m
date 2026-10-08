% Random Number Generator

% Define the minimum and maximum values for the random range
min_value = 1;
max_value = 100;

% Generate 10 random numbers within the specified range
random_numbers = randi([min_value max_value], 1, 10);

% Display the generated random numbers
disp(random_numbers);