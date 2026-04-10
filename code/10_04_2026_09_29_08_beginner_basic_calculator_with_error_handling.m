% Basic Calculator with Error Handling
% Author: [Your Name]
% Date: [Current Date]

% Define function to perform arithmetic operations
function result = calculator(input1, operator, input2)
    % Check if inputs are valid numbers
    if ~isnumeric(input1) || ~isnumeric(input2)
        error('Invalid input: Both inputs must be numbers');
    end
    
    % Perform calculation based on operator
    switch operator
        case '+'
            result = input1 + input2;
        case '-'
            result = input1 - input2;
        case '*'
            result = input1 * input2;
        case '/'
            if input2 == 0
                error('Error: Division by zero is not allowed');
            else
                result = input1 / input2;
            end
        otherwise
            error('Invalid operator: Only +, -, *, / are supported');
    end
end

% Main script to test the calculator function
clc; clear;

while true
    % Ask user for inputs and operator
    input1 = input('Enter first number: ');
    operator = input('Enter operator (+, -, *, /): ', 's');
    input2 = input('Enter second number: ');

    % Call the calculator function and display result
    try
        result = calculator(str2double(input1), operator, str2double(input2));
        fprintf('Result: %.2f\n', result);
    catch err
        % Display error message if an error occurs
        fprintf('Error: %s\n', err.message);
    end
    
    % Ask user to continue or exit
    choice = input('Do you want to continue (y/n)? ', 's');
    
    % Exit the loop if user chooses to stop
    if lower(choice) ~= 'y'
        break;
    end
end

% End of script