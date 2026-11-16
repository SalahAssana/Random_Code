% Random Number Generator
% This program generates random numbers within a specified range using different algorithms.

% Define the range of numbers to generate (min and max)
minValue = 1;
maxValue = 100;

% Function to generate random numbers between min and max values
function randNums = generateRandom(min, max)
    % Use the Rand function to generate random numbers
    randNums = randi([min, max], 10, 1);
end

% Generate random numbers using the function
randNums = generateRandom(minValue, maxValue);

% Print the generated random numbers
fprintf('Generated Random Numbers:\n');
for i = 1:length(randNums)
    fprintf('%d ', randNums(i));
end
fprintf('\n');