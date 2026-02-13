% Simple Calculator
%
% Description:
%   This script is a simple calculator that takes in mathematical expressions as input
%   and evaluates them.

function result = calculator(input_string)
    % Initialize the result variable to store the output.
    result = 0;
    
    % Split the input string into tokens (operators and numbers).
    tokens = strsplit(input_string, {'+', '-', '*', '/'});
    
    % Loop through each token and calculate the result.
    for i = 1:length(tokens) - 1
        if strcmp(tokens{i}, '+')
            result = result + str2double(tokens{i+1});
        elseif strcmp(tokens{i}, '-')
            result = result - str2double(tokens{i+1});
        elseif strcmp(tokens{i}, '*')
            result = result * str2double(tokens{i+1});
        elseif strcmp(tokens{i}, '/')
            if str2double(tokens{i+1}) == 0
                error('Cannot divide by zero!');
            else
                result = result / str2double(tokens{i+1});
            end
    end
    
end

% Test the calculator.
input_string = '10 + 3 * 4 - 2';
result = calculator(input_string);
fprintf('The result is: %f\n', result);
