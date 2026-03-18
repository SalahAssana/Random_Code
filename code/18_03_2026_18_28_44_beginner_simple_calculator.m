% Simple Calculator in MATLAB

% Define the arithmetic operations
operations = {'+', '-', '*', '/'};

% Function to perform the chosen operation
function result = calculate(num1, num2, op)
    if strcmp(op, '+')
        result = num1 + num2;
    elseif strcmp(op, '-')
        result = num1 - num2;
    elseif strcmp(op, '*')
        result = num1 * num2;
    elseif strcmp(op, '/')
        % Check for division by zero
        if num2 == 0
            error('Error: Division by zero is not allowed');
        else
            result = num1 / num2;
        end
    else
        error('Error: Invalid operation');
    end
end

% Main script
if nargin < 3
    error('At least three input arguments required');
end

num1 = str2double(input('Enter the first number: ', 's'));
op = input('Enter the operation (+, -, *, /): ', 's');
num2 = str2double(input('Enter the second number: ', 's'));

result = calculate(num1, num2, op);

% Display the result
fprintf('\nThe result is: %.2f\n', result);