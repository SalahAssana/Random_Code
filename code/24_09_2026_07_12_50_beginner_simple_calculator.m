% Simple Calculator in MATLAB
% BEGINNER-level project for learning basic arithmetic operations

% Define function to perform simple calculations
function result = calculate(expression)
    % Split expression into operator and operands
    tokens = strsplit(expression, ' ');
    
    % Get the operator (addition or subtraction)
    op = tokens{2};
    
    % Convert operands to numbers
    num1 = str2num(tokens{1});
    num2 = str2num(tokens{3});
    
    % Perform calculation based on operator
    if strcmp(op, '+')
        result = num1 + num2;
    elseif strcmp(op, '-')
        result = num1 - num2;
    else
        error('Invalid operator');
    end
end

% Main script to test the calculator function
clear all;

% Test cases
expressions = {'2 3 +', '5 1 -', '4 2 *', '6 0 /'}; % Add more test cases as needed!

% Run calculations for each expression and display results
for i = 1:length(expressions)
    [expression] = deal(expressions{i});
    result = calculate(expression);
    fprintf('Expression: "%s" => Result: %d\n', expression, result);
end
