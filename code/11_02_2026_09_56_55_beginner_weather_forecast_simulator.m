% Weather Forecast Simulator
% Author: [Your Name]
% Date: [Current Date]

clear all;
close all;

% Define constants for weather types and their probabilities
num_weather_types = 5; % Sunny, Cloudy, Rainy, Windy, Snowy
weather_probabilities = [0.4, 0.3, 0.2, 0.05, 0.05];

% Generate random weather forecast based on probabilities
random_value = rand;
weather_index = find(cumsum(weather_probabilities) > random_value);

switch weather_index
    case 1 % Sunny
        weather_description = 'Partly Cloudy with a high of 75F and a low of 55F';
    case 2 % Cloudy
        weather_description = 'Overcast with a high of 65F and a low of 45F';
    case 3 % Rainy
        weather_description = 'Rain showers expected with a high of 60F and a low of 50F';
    case 4 % Windy
        weather_description = 'Windy conditions with a high of 70F and a low of 40F';
    case 5 % Snowy
        weather_description = 'Snow flurries expected with a high of 45F and a low of 30F';
end

% Display the generated weather forecast
fprintf('Today''s Weather Forecast: %s\n', weather_description);