% Simple Calculator in MATLAB

% Define operators and their corresponding functions
ops = {'+', '-', '*','/'};
func = { @(x,y) x+y, @(x,y) x-y, @(x,y) x*y, @(x,y) x/y };

% Function to perform calculation based on user input
function result = calc(ope)
    % Ask for two numbers and operator from the user
    num1 = input('Enter first number: ');
    num2 = input('Enter second number: ');
    
    % Validate operator
    if any(strcmpi(ope, ops))
        % Perform calculation using the corresponding function
        result = func{find(strcmpi(ope, ops))}(num1, num2);
    else
        error('Invalid operation. Please try again.');
    end
end

% Main script to run calculator
clear all;
clc;

% Run calculator until user chooses to quit
while true
    % Display menu options
    disp('Calculator Menu:');
    disp('----------------');
    disp('1. Addition (+)');
    disp('2. Subtraction (-)');
    disp('3. Multiplication (*)');
    disp('4. Division (/)');
    disp('5. Quit');
    
    % Ask for operation choice from the user
    choice = input('Enter your choice (1-5): ');
    
    % Validate choice
    if choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5
        if choice == 5
            break;
        end
        
        % Perform calculation based on user's choice
        result = calc(char(ops{choice-1}));
        
        % Display the result
        disp(['The result is: ', num2str(result)]);
    else
        error('Invalid choice. Please try again.');
    end
end

% End of script