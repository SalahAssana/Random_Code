% Temperature Converter
% A simple program that converts Celsius to Fahrenheit and vice versa,
% handling invalid inputs and edge cases.

% Define conversion factors
CtoF = 9/5;
FtoC = 5/9;

% Function to convert temperature from Celsius to Fahrenheit
function F = celsiusToFahrenheit(C)
    % Check for valid input (numeric value)
    if ~isnumeric(C) || isempty(C)
        error('Invalid input: Please enter a numeric value');
    end
    
    % Convert Celsius to Fahrenheit
    F = C * CtoF + 32;
end

% Function to convert temperature from Fahrenheit to Celsius
function C = fahrenheitToCelsius(F)
    % Check for valid input (numeric value)
    if ~isnumeric(F) || isempty(F)
        error('Invalid input: Please enter a numeric value');
    end
    
    % Convert Fahrenheit to Celsius
    C = (F - 32) / CtoF;
end

% Main script
clear all; clc;

while true
    % Prompt user for temperature conversion type
    choice = input('Enter C for Celsius or F for Fahrenheit: ','s');
    
    if lower(choice) == 'c'
        % Get Celsius value from user
        C = str2double(input('Enter the temperature in Celsius: ', 's'));
        
        % Convert Celsius to Fahrenheit and display result
        F = celsiusToFahrenheit(C);
        fprintf('%.1f°C is equivalent to %.1f°F\n', C, F);
    elseif lower(choice) == 'f'
        % Get Fahrenheit value from user
        F = str2double(input('Enter the temperature in Fahrenheit: ', 's'));
        
        % Convert Fahrenheit to Celsius and display result
        C = fahrenheitToCelsius(F);
        fprintf('%.1f°F is equivalent to %.1f°C\n', F, C);
    else
        error('Invalid choice. Please enter C or F');
    end
    
    % Ask user if they want to continue converting temperatures
    response = input('Do you want to convert more temperatures? (y/n): ','s');
    
    % Exit loop if user chooses not to continue
    if lower(response) ~= 'y'
        break;
    end
end

fprintf('Goodbye!\n');