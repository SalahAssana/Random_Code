% Temperature Conversion Tool
% BEGINNER complexity project

% Define conversion factors
celsius_to_fahrenheit_factor = 9/5;
fahrenheit_to_celsius_factor = 5/9;

% Define input and output variables
temperature_input = 0;
temperature_output = 0;

% Main program loop
while true
    % Ask user for temperature type (C or F)
    temperature_type = input('Enter T for Celsius or F for Fahrenheit: ', 's');
    
    % Convert temperature to numeric value
    if temperature_type == 'T' || temperature_type == 't'
        temperature_input = str2double(input('Enter temperature in Celsius: ', 's'));
    elseif temperature_type == 'F' || temperature_type == 'f'
        temperature_input = str2double(input('Enter temperature in Fahrenheit: ', 's'));
    else
        disp('Invalid input. Try again!');
        continue;
    end
    
    % Perform conversion
    if temperature_type == 'T' || temperature_type == 't'
        temperature_output = temperature_input * celsius_to_fahrenheit_factor + 32;
        disp([num2str(temperature_input), ' Celsius is equal to ', num2str(temperature_output), ' Fahrenheit.']);
    elseif temperature_type == 'F' || temperature_type == 'f'
        temperature_output = (temperature_input - 32) / fahrenheit_to_celsius_factor;
        disp([num2str(temperature_input), ' Fahrenheit is equal to ', num2str(temperature_output), ' Celsius.']);
    end
end