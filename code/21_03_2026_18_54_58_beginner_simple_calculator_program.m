% Simple Calculator Program
% BEGINNER complexity project

% Define function for addition
function result = add(a, b)
    % Add two numbers and return the result
    result = a + b;
end

% Define function for subtraction
function result = subtract(a, b)
    % Subtract two numbers and return the result
    result = a - b;
end

% Define function for multiplication
function result = multiply(a, b)
    % Multiply two numbers and return the result
    result = a * b;
end

% Define function for division
function result = divide(a, b)
    % Check if denominator is zero before dividing
    if b == 0
        error('Cannot divide by zero!');
    else
        % Divide two numbers and return the result
        result = a / b;
    end
end

% Main script to perform calculations
calc_result = 0;

while true
    % Display menu options
    disp('Simple Calculator Program');
    disp('1. Addition');
    disp('2. Subtraction');
    disp('3. Multiplication');
    disp('4. Division');
    disp('5. Exit');

    % Get user input for operation and operands
    choice = input('Enter your choice (1-5): ');
    a = input('Enter first operand: ');
    b = input('Enter second operand: ');

    % Perform chosen operation
    switch choice
        case 1
            calc_result = add(a, b);
        case 2
            calc_result = subtract(a, b);
        case 3
            calc_result = multiply(a, b);
        case 4
            calc_result = divide(a, b);
        case 5
            break;
    end

    % Display result
    disp(['Result: ', num2str(calc_result)]);