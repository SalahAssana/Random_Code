% Simple Weather Forecast Generator
% BEGINNER complexity project

% Define weather conditions and their probabilities
weather_conditions = {'Sunny', 'Rainy', 'Cloudy'};
probabilities = [0.6 0.3 0.1];

% Generate a random number between 0 and 1
random_number = rand;

% Initialize the index of the selected weather condition
index = 1;

% Find the first weather condition that has a probability greater than or equal to the random number
for i = 1:length(weather_conditions)
    if probabilities(i) >= random_number
        index = i;
        break
    end
end

% Generate the weather forecast
weather_forecast = [sprintf('Tomorrow, it will be %s with a chance of ', weather_conditions{index}) ...
                   sprintf('rain. The high temperature will be around 75 degrees Fahrenheit.')]';

% Display the weather forecast
disp(weather_forecast)