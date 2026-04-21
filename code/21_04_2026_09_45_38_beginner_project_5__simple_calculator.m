% Project 5: Simple Calculator

% Initialize variables to store user input and result
num1 = 0;
num2 = 0;
operator = '';

% Define function to perform arithmetic operations
function result = performOperation(num1, num2, operator)
    switch operator
        case '+'
            result = num1 + num2;
        case '-'
            result = num1 - num2;
        case '*'
            result = num1 * num2;
        case '/'
            if num2 ~= 0
                result = num1 / num2;
            else
                error('Division by zero is not allowed');
            end
    end
end

% Main program loop
while true
    % Ask user for input
    disp('Simple Calculator');
    disp('Enter two numbers and an operator (+, -, *, /)');
    inputStr = input('Enter your expression: ', 's');

    % Split user input into number1, operator, and num2
    [numStr1, operatorStr, numStr2] = regexp(inputStr, '(\d+)([+-*/])(\d*)', 'tokens');
    num1 = str2double(numStr1{1});
    operator = operatorStr;
    if ~isempty(numStr2)
        num2 = str2double(numStr2{1});
    else
        num2 = 0;
    end

    % Perform arithmetic operation and display result
    result = performOperation(num1, num2, operator);
    disp(['Result: ', numStr1{1}, ' ', operatorStr, ' ', numStr2{1}, ' = ', num2str(result)]);

    % Ask user if they want to continue
    response = input('Do you want to calculate again? (y/n):', 's');
    while true
        switch lower(response)
            case 'y'
                break;
            case 'n'
                return;
            otherwise
                disp('Invalid input. Please enter y or n.');
                response = input('Do you want to calculate again? (y/n):', 's');
        end
    end
end

% End of script