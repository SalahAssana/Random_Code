% Weather Forecaster - A simple MATLAB program for beginners

% Import necessary libraries
import java.lang.Math;

% Define the weather conditions
weather_conditions = {'Sunny', 'Cloudy', 'Rainy', 'Windy'};

% Define the temperature ranges
temperature_ranges = [0 20; 21 30; 31 40; 41 50];

% Function to predict the weather based on temperature
function weather = predict_weather(temperature)
    for i = 1:size(temperature_ranges, 1)
        if temperature >= temperature_ranges(i, 1) && temperature <= temperature_ranges(i, 2)
            weather = weather_conditions{i};
            return;
        end
    end
end

% Main script
clear all;

% Ask the user for the temperature
temperature = input('Enter the temperature (in degrees Celsius): ', 'double');

% Predict the weather based on the temperature
weather = predict_weather(temperature);

% Display the predicted weather
fprintf('The weather is expected to be %s.\n', weather);