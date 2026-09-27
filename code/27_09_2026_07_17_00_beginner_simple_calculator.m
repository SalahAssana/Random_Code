% Simple Calculator in MATLAB
% Beginner-level project for learning basics of MATLAB programming

% Define input variables
num1 = 0;
op = '';
num2 = 0;

% Ask user for input
prompt = 'Enter the first number: ';
num1 = input(prompt);

prompt = 'Enter an operator (+, -, *, /): ';
op = input(prompt);

prompt = 'Enter the second number: ';
num2 = input(prompt);

% Perform calculations based on operator
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
            disp('Error: Division by zero!');
            return;
        end
end

% Display the calculation and result
fprintf('The answer is %f\n', result);