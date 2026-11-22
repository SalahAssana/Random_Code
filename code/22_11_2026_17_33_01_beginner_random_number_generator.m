% Random Number Generator
% A simple program that generates random numbers within a specified range

% Define the function to generate random numbers
function randNums = generateRandomNumbers(minValue, maxValue, numNumbers)
    % Initialize an empty array to store the generated numbers
    randNums = zeros(1, numNumbers);
    
    % Loop through the number of times we want to generate a number
    for i = 1:numNumbers
        % Generate a random number within the specified range
        randNums(i) = round(rand*(maxValue-minValue) + minValue);
    end
end

% Main script
minValue = 1;       % Minimum value of the range
maxValue = 100;     % Maximum value of the range
numNumbers = 10;    % Number of random numbers to generate

% Call the function to generate random numbers
randomNumbers = generateRandomNumbers(minValue, maxValue, numNumbers);

% Print the generated random numbers
fprintf('Generated Random Numbers:\n');
fprintf('%d ', randomNumbers);
fprintf('\n');