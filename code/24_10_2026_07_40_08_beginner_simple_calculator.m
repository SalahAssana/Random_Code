% Simple Calculator in MATLAB
% 
% Author: [Your Name]
% Date: [Current Date]

% Define input variable
num1 = 0;
op = '';
num2 = 0;

% Display calculator interface
fprintf('Simple Calculator\n');
fprintf('-----------------\n');
fprintf('Enter number 1: ');
num1 = input('');

while true
    fprintf('\nEnter operation (+, -, *, /): ');
    op = input('');
    
    if strcmp(op, '+') || strcmp(op, '-') || strcmp(op, '*') || strcmp(op, '/')
        fprintf('\nEnter number 2: ');
        num2 = input('');
        
        switch op
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
                    fprintf('Error! Division by zero is not allowed.\n');
                    return
                end
        end
        
        % Display the calculation result
        fprintf('\nResult: %.2f\n', result);
        
    else
        fprintf('\nInvalid operation. Please try again.\n');
    end
    
    % Ask user if they want to continue
    reply = input('Do you want to continue? (y/n): ', 's');
    
    if strcmp(reply, 'n')
        break
    end
end

fprintf('\nCalculator terminated.\n');