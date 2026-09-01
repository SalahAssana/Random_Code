% Temperature Converter in MATLAB

% Define conversion factors
celsiusToFahrenheit = (9/5) + 32;

% Function to convert Celsius to Fahrenheit
function fahrenheit = celsiusToFahrenheitTemp(celsius)
    fahrenheit = celsius * celsiusToFahrenheit;
end

% Function to convert Fahrenheit to Celsius
function celsius = fahrenheitToCelsius(fahrenheit)
    celsius = (fahrenheit - 32) / celsiusToFahrenheit;
end

% Main script
clear all;

while true
    
    % Prompt user for temperature conversion option
    disp('1. Convert Celsius to Fahrenheit');
    disp('2. Convert Fahrenheit to Celsius');
    disp('3. Quit');
    
    choice = input('Enter your choice (1, 2 or 3): ', 's');
    
    if strcmp(choice, '1')
        celsius = input('Enter temperature in Celsius: ');
        fahrenheit = celsiusToFahrenheitTemp(celsius);
        disp([num2str(celsius) ' degrees Celsius is equal to ' num2str(fahrenheit) ' degrees Fahrenheit']);
        
    elseif strcmp(choice, '2')
        fahrenheit = input('Enter temperature in Fahrenheit: ');
        celsius = fahrenheitToCelsius(fahrenheit);
        disp([num2str(fahrenheit) ' degrees Fahrenheit is equal to ' num2str(celsius) ' degrees Celsius']);
        
    elseif strcmp(choice, '3')
        break;
        
    else
        disp('Invalid choice. Please try again.');
    end
    
end

disp('Goodbye!');