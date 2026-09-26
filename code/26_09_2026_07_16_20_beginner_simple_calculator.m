% Simple Calculator in MATLAB
% BEGINNER LEVEL PROJECT

% Define the arithmetic operations as functions
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
        error('Error: Division by zero is not allowed');
    else
        result = a / b;
    end
end

% Main script to take user input and perform arithmetic operations
clear all;

while true
    % Display the calculator menu
    disp(['Simple Calculator']);
    disp(['1. Addition']);
    disp(['2. Subtraction']);
    disp(['3. Multiplication']);
    disp(['4. Division']);
    disp(['5. Exit']);

    % Get user input
    choice = input('Enter your choice (1-5): ');

    % Validate the user input
    if choice < 1 || choice > 5
        error('Invalid choice');
    end

    % Perform the chosen arithmetic operation
    switch choice
        case 1
            a = input('Enter first number: ');
            b = input('Enter second number: ');
            result = add(a, b);
            disp(['Result: ' num2str(result)]);
        case 2
            a = input('Enter first number: ');
            b = input('Enter second number: ');
            result = subtract(a, b);
            disp(['Result: ' num2str(result)]);
        case 3
            a = input('Enter first number: ');
            b = input('Enter second number: ');
            result = multiply(a, b);
            disp(['Result: ' num2str(result)]);
        case 4
            a = input('Enter first number: ');
            b = input('Enter second number: ');
            result = divide(a, b);
            disp(['Result: ' num2str(result)]);
        case 5
            break;
    end

    % Exit the loop when user chooses to exit
end