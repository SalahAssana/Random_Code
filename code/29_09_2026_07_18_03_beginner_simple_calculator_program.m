% Simple Calculator Program
% BEGINNER complexity project

% Define a function to evaluate mathematical expressions
function result = calculator(expression)
    % Split the expression into operands and operator
    tokens = strsplit(expression, ' ');
    operand1 = str2double(tokens{1});
    operator = tokens{2};
    operand2 = str2double(tokens{3});

    % Perform the operation based on the operator
    switch operator
        case '+'
            result = operand1 + operand2;
        case '-'
            result = operand1 - operand2;
        case '*'
            result = operand1 * operand2;
        case '/'
            if operand2 ~= 0
                result = operand1 / operand2;
            else
                error('Division by zero!');
            end
    end
end

% Main program to test the calculator function
expression = input('Enter a mathematical expression (e.g., 2 + 3): ', 's');
result = calculator(expression);
fprintf('Result: %f\n', result);