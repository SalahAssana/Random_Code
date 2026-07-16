% Simple Weather Forecast Program
%
% Author: Your Name (replace with your name)
%
% Description: A simple program that takes user input for location and weather type,
%              then displays the corresponding forecast from synthetic data.

% Synthetic weather data
weather_data = {
    "New York", "Sunny", "High 75, Low 65";
    "Los Angeles", "Cloudy", "High 72, Low 58";
    "Chicago", "Rainy", "High 62, Low 50";
    "Miami", "Windy", "High 78, Low 68";
};

% Function to get user input
function [location, weather] = getUserInput()
    location = input('Enter the city (e.g., New York): ', 's');
    weather = input('Enter the weather type (e.g., Sunny): ', 's');
end

% Main program
[location, weather] = getUserInput();

% Find matching forecast from synthetic data
for i = 1:size(weather_data, 1)
    if strcmp(location, weather_data{i, 1}) && ...
            strcmp(weather, weather_data{i, 2})
        fprintf('The weather forecast for %s is %s with a high of %s and low of %s.\n', ...
                location, weather, weather_data{i, 3}(1:5), weather_data{i, 3}(7:end));
        return
    end
end

% If no match found, display error message
fprintf('No forecast available for %s with weather type %s.\n', location, weather);