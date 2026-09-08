% Random Number Generator
% BEGINNER complexity project

% Import necessary libraries
rng default; % Set the random seed for reproducibility
n = 10; % Define the number of random numbers to generate
lower_bound = -100; % Define the lower bound of the range
upper_bound = 100; % Define the upper bound of the range

% Generate random numbers
random_numbers = randi([lower_bound, upper_bound], 1, n);

% Display the generated random numbers
fprintf('Generated Random Numbers: %s\n', num2str(random_numbers));

% Calculate and display statistical measures (mean, median, mode)
stats = [mean(random_numbers), median(random_numbers), mode(random_numbers)];
fprintf('Statistical Measures:\n');
fprintf('  Mean: %.2f\n', stats(1));
fprintf('  Median: %.2f\n', stats(2));
fprintf('  Mode: %.2f\n', stats(3));

% Display the distribution of random numbers
histogram(random_numbers);
xlabel('Random Number Values');
ylabel('Frequency');
title('Distribution of Random Numbers');

% Pause to display the histogram
pause;