% Temperature Converter - Beginner Level Project

% Define the temperature conversion functions
function celsiusToFahrenheit = celsiusTo Fahrenheit(celsius)
    celsiusToFahrenheit = (celsius * 9/5) + 32;
end

function fahrenheitToCelsius = fahrenheitToCelsius(fahrenheit)
    fahrenheitToCelsius = (fahrenheit - 32) * 5/9;
end

% Main script
clear all;

% Ask the user for input temperature and conversion type
prompt = 'Enter a temperature value: ';
temperature = input(prompt);

prompt = 'Do you want to convert Celsius to Fahrenheit or Fahrenheit to Celsius? (1 for Celsius to Fahrenheit, 2 for Fahrenheit to Celsius): ';
conversionType = input(prompt);

if conversionType == 1
    celsius = temperature;
    fahrenheit = celsiusToFahrenheit(celsius);
    disp(['The equivalent Fahrenheit value is: ' num2str(fahrenheit)]);
else
    fahrenheit = temperature;
    celsius = fahrenheitToCelsius(fahrenheit);
    disp(['The equivalent Celsius value is: ' num2str(celsius)]);
end