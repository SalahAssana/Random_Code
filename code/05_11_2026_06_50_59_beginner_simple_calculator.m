% Simple Calculator in MATLAB

% Define function to perform arithmetic operations
function result = calculator(operation, num1, num2)
    % Check if operation is valid
    switch operation
        case 'add'
            result = num1 + num2;
        case 'subtract'
            result = num1 - num2;
        case 'multiply'
            result = num1 * num2;
        case 'divide'
            if num2 ~= 0
                result = num1 / num2;
            else
                disp('Error: Division by zero is not allowed');
                return;
            end
        otherwise
            disp('Error: Invalid operation');
            return;
    end
end

% Main script
if nargin < 3
    disp('Usage: calculator(operation, num1, num2)');
    return;
end

operation = input('Enter the operation (+, -, * or /): ', 's');
num1 = str2double(input('Enter the first number: ', 's'));
num2 = str2double(input('Enter the second number: ', 's'));

% Perform arithmetic operation and display result
result = calculator(operation, num1, num2);
if ~isempty(result)
    disp(['Result: ', num2str(result)]);
else
    disp('Error occurred');
end