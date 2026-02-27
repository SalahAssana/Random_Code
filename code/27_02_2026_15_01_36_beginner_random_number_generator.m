% Random Number Generator
% This program generates random numbers within a specified range
% and checks if they are unique.

% Initialize variables
min_num = 1; % minimum value for the random number range
max_num = 100; % maximum value for the random number range
num_numbers = 10; % number of random numbers to generate

% Generate random numbers
random_numbers = randi([min_num max_num], [1 num_numbers]);

% Check if the generated numbers are unique
unique_numbers = unique(random_numbers);

% Display the results
fprintf('Random Numbers: ');
for i = 1:length(random_numbers)
    fprintf('%d ', random_numbers(i));
end
fprintf('\n');
fprintf('Unique Random Numbers: ');
for i = 1:length(unique_numbers)
    fprintf('%d ', unique_numbers(i));
end
fprintf('\n');

% Check if all numbers are unique (should be the case for small ranges)
if length(random_numbers) == length(unique_numbers)
    fprintf('All random numbers are unique.\n');
else
    fprintf('Not all random numbers are unique.\n');
end