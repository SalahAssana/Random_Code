% Temperature Converter
% BEGINNER complexity project

% Define conversion factors
F_TO_C = 5/9;
C_TO_F = 9/5;

% Function to convert Fahrenheit to Celsius
function celsius = fahrenheit_to_celsius(fahrenheit)
    celsius = (fahrenheit - 32) * F_TO_C;
end

% Function to convert Celsius to Fahrenheit
function fahrenheit = celsius_to_fahrenheit(celsius)
    fahrenheit = celsius * C_TO_F + 32;
end

% Main script
clear all;

% Ask user for input temperature and conversion type
fprintf('Temperature Converter\n');
fprintf('-------------------\n');
fprintf('Enter a temperature value: ');
temp_value = input('Fahrenheit or Celsius (F/C)? ');

% Convert temperature based on user's choice
if temp_value == 'F' || temp_value == 'f'
    fprintf('\nEnter Fahrenheit temperature: ');
    fahrenheit = input('');
    celsius = fahrenheit_to_celsius(str2num(fahrenheit));
    fprintf(['\nThe equivalent Celsius temperature is: ', num2str(celsius), '\n']);
elseif temp_value == 'C' || temp_value == 'c'
    fprintf('\nEnter Celsius temperature: ');
    celsius = input('');
    fahrenheit = celsius_to_fahrenheit(str2num(celsius));
    fprintf(['\nThe equivalent Fahrenheit temperature is: ', num2str(fahrenheit), '\n']);
else
    error('Invalid input. Please enter F for Fahrenheit or C for Celsius.');
end

% Pause before exiting
pause;