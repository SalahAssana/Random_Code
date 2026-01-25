% Random Number Generator
% Generate random numbers within a specified range and display them

% Import necessary libraries
import java.util.Random;

% Define function to generate random numbers
function random_numbers = generate_random_numbers(min_value, max_value, number_of_numbers)
    % Create a new instance of the Random class
    rand_object = Random();

    % Initialize an array to store the generated random numbers
    random_numbers = zeros(1, number_of_numbers);

    % Generate and store random numbers within the specified range
    for i = 1:number_of_numbers
        random_numbers(i) = min_value + rand_object.nextDouble() * (max_value - min_value);
    end

end

% Main program
if nargin == 0
    min_value = 1;
    max_value = 100;
    number_of_numbers = 10;
else
    [min_value, max_value, number_of_numbers] = deal(varargin{:});
end

% Generate and display random numbers
random_numbers = generate_random_numbers(min_value, max_value, number_of_numbers);

fprintf('Generated Random Numbers:\n');
fprintf('%f ', random_numbers);
fprintf('\n');