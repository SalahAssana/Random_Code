% Simple Calculator Program
% Author: [Your Name]
% Date: [Date]

% Define input string to store mathematical expression
expr = '';

% Define output variable to store result
result = 0;

% Define array of supported operators and their corresponding functions
operators = {'+', '-', '*', '/'};
ops_func = @(x) eval(x);

% Function to parse input string and evaluate expression
function out = parse_input(str)
    % Split the input string into tokens (operators, numbers, parentheses)
    tokens = strsplit(str, {' ', '+', '-', '*', '/', '.', '(', ')'});
    
    % Initialize variables for parsing and evaluating
    i = 1;
    op = '';
    num = 0;
    prev_num = 0;
    
    % Parse input string and evaluate expression
    while i <= length(tokens)
        token = tokens{i};
        
        if any(strcmp(operators, token))
            % Apply operator to previous number
            prev_num = ops_func({num, op, token});
            
            % Update variables for next iteration
            num = 0;
            op = token;
        elseif isnumeric(str2double(token))
            % Convert string token to numeric value and store in variable
            num = str2double(token);
        end
        
        i = i + 1;
    end
    
    % Apply operator to last number
    result = ops_func({num, op});
end

% Main program loop
while true
    % Prompt user for input
    fprintf('Enter a mathematical expression (or "q" to quit): ');
    expr = input('>> ', 's');
    
    if strcmp(expr, 'q')
        break;
    end
    
    % Parse and evaluate the input string
    parse_input(expr);
    
    % Print result
    fprintf('\nResult: %.2f\n', result);
end