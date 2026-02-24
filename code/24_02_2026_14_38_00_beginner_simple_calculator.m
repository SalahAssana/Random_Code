% Simple Calculator in MATLAB
% Author: [Your Name]

% Initialize variables to hold input string and result
input_str = '';
result = 0;

% Define function to evaluate arithmetic expression
function res = eval_expr(expr)
    % Split the expression by operators
    tokens = strsplit(expr, {'+', '-', '*', '/'});
    
    % Initialize variables for numeric values and operator
    num1 = str2double(tokens{1});
    op = '';
    num2 = 0;
    
    % Process each token
    for i = 2:length(tokens)
        if strcmp(op, '')
            num1 = str2double(tokens{i-1});
            op = tokens{i};
        else
            switch op
                case '+'
                    num2 = num1 + str2double(tokens{i});
                case '-'
                    num2 = num1 - str2double(tokens{i});
                case '*'
                    num2 = num1 * str2double(tokens{i});
                case '/'
                    num2 = num1 / str2double(tokens{i});
            end
            op = '';
            num1 = num2;
        end
    end
    
    % Return the final result
    res = num1;
end

% Define function to handle parentheses
function expr = handle_parens(expr)
    % Find the position of the opening parenthesis
    pos = strfind(expr, '(');
    
    % If there is an opening parenthesis, find its matching closing parenthesis
    if ~isempty(pos)
        pos2 = strfind(expr(pos:end), ')');
        new_pos = pos + pos2(1) - 1;
        
        % Recursively handle the expression inside parentheses
        expr2 = expr(pos:new_pos);
        result = eval_expr(expr2);
        expr(new_pos+1:length(expr)) = num2str(result);
    end
end

% Main script
while true
    % Prompt user for input
    disp('Enter an arithmetic expression (e.g., 2+3*4):');
    input_str = input('Input: ');
    
    % Handle parentheses and evaluate the expression
    handle_parens(input_str);
    result = eval_expr(input_str);
    
    % Display the result
    disp(['Result:', num2str(result)]);