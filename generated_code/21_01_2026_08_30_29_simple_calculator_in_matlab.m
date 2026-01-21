% Simple Calculator in MATLAB
% By [Your Name]

clear all;
clc;

% Define functions for arithmetic operations
function result = add(a, b)
    result = a + b;
end

function result = subtract(a, b)
    result = a - b;
end

function result = multiply(a, b)
    result = a * b;
end

function result = divide(a, b)
    if b == 0
        error('Cannot divide by zero!');
    else
        result = a / b;
    end
end

% Main program
while true
    % Display menu
    fprintf('Simple Calculator\n');
    fprintf('1. Addition\n');
    fprintf('2. Subtraction\n');
    fprintf('3. Multiplication\n');
    fprintf('4. Division\n');
    fprintf('5. Quit\n');

    % Get user input
    choice = input('Choose an option (1-5): ');

    if strcmp(choice, '1')
        a = input('Enter first number: ');
        b = input('Enter second number: ');
        result = add(a, b);
        fprintf(['Result: ', num2str(result), '\n']);
    elseif strcmp(choice, '2')
        a = input('Enter first number: ');
        b = input('Enter second number: ');
        result = subtract(a, b);
        fprintf(['Result: ', num2str(result), '\n']);
    elseif strcmp(choice, '3')
        a = input('Enter first number: ');
        b = input('Enter second number: ');
        result = multiply(a, b);
        fprintf(['Result: ', num2str(result), '\n']);
    elseif strcmp(choice, '4')
        a = input('Enter first number: ');
        b = input('Enter second number: ');
        result = divide(a, b);
        fprintf(['Result: ', num2str(result), '\n']);
    elseif strcmp(choice, '5')
        break;
    else
        fprintf('Invalid choice. Please try again.\n');
    end
end

% Display goodbye message
fprintf('\nGoodbye!\n');