% Random Number Generator

% Define the range for random number generation
min_value = 1;
max_value = 100;

% Generate and display 10 random numbers within the specified range
for i = 1:10
    rand_num = min_value + (max_value - min_value) * rand(1);
    fprintf('Random Number %d: %.2f\n', i, rand_num);
end