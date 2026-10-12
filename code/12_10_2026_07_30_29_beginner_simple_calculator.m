% Simple Calculator in MATLAB
% Beginner Level Implementation

% Define input variables
num1 = 0;
num2 = 0;
operator = '';

% Function to get user input for numbers and operator
function [num1, num2, operator] = getUserInput()
    % Get first number from user
    disp('Enter the first number:');
    num1 = input('');

    % Get second number from user
    disp('Enter the second number:');
    num2 = input('');

    % Get the operator from user
    disp('Enter the operator (+, -, *, /):');
    operator = input('');
end

% Function to perform arithmetic operations based on the operator
function result = performOperation(num1, num2, operator)
    switch operator
        case '+'
            result = num1 + num2;
        case '-'
            result = num1 - num2;
        case '*'
            result = num1 * num2;
        case '/'
            if num2 == 0
                disp('Error: Division by zero is not allowed!');
                return;
            end
            result = num1 / num2;
    end
end

% Main script to get user input, perform the operation, and display the result
[num1, num2, operator] = getUserInput();
result = performOperation(num1, num2, operator);
disp(['The result is: ' num2str(result)]);