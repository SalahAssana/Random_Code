% Simple Weather Forecast
%
% A program that generates random weather forecasts based on user input for different cities.

% Ask the user to enter the city name
city = input('Enter the city name: ','s');

% Define a struct to hold the weather data
weather_data = struct('City', '', 'Temperature', 0, 'Condition', '');

% Initialize the weather data with default values
weather_data.City = city;
weather_data.Temperature = round(rand * 100); % Random temperature between 0-100
weather_data.Condition = ['Sunny' if rand < 0.5; 'Cloudy' if rand >= 0.5];

% Display the weather forecast
fprintf('The weather in %s is %d degrees with a condition of %s.\n', ...
        weather_data.City, weather_data.Temperature, weather_data.Condition);