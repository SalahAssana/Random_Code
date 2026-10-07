% Weather Forecast Simulator

% Import necessary libraries
import java.util.Random;

% Define the structure to store weather forecast data
struct WeatherForecast
    temperature double
    precipitation double
end

% Function to generate random temperature and precipitation values
function [temperature, precipitation] = generateRandomWeather()
    % Generate random temperature between 0 and 100 degrees Fahrenheit
    temperature = round(rand() * 100);
    
    % Generate random precipitation between 0 and 10 inches
    precipitation = round(rand() * 10);
end

% Function to calculate the probability of specific weather conditions based on historical data
function [prob_temperature, prob_precipitation] = calculateProbabilities(weatherData)
    % Calculate total number of records in the dataset
    totalRecords = size(weatherData, 1);
    
    % Calculate the probability of temperature being below 50 degrees Fahrenheit
    prob_temperature_low = sum(weatherData(:, 2) < 50) / totalRecords;
    
    % Calculate the probability of precipitation being above 5 inches
    prob_precipitation_high = sum(weatherData(:, 3) > 5) / totalRecords;
end

% Main function to generate and print weather forecasts based on user input
function main()
    % Initialize random number generator
    rng(0);
    
    % Generate synthetic weather data (replace with actual data if available)
    weatherData = [
        65 3.2 4.5;
        70 1.8 6.1;
        60 2.5 7.3;
        75 4.2 5.9;
        65 3.8 3.1
    ];
    
    % Calculate probabilities based on historical data
    [prob_temperature_low, prob_precipitation_high] = calculateProbabilities(weatherData);
    
    % Ask user for input (replace with actual input if available)
    userInput_temperature = input('Enter your preferred temperature (0-100): ', 's');
    userInput_precipitation = input('Enter your preferred precipitation (0-10): ', 's');
    
    % Convert user input to numbers
    userInput_temperature = str2double(userInput_temperature);
    userInput_precipitation = str2double(userInput_precipitation);
    
    % Generate random weather forecast based on user input and probabilities
    if userInput_temperature < 50 && rand() < prob_temperature_low
        temperature = 45;
    elseif userInput_temperature > 75 && rand() < prob_temperature_low
        temperature = 80;
    else
        [temperature, ~] = generateRandomWeather();
    end
    
    if userInput_precipitation > 5 && rand() < prob_precipitation_high
        precipitation = 8;
    elseif userInput_precipitation < 1 && rand() < prob_precipitation_high
        precipitation = 2;
    else
        [~, precipitation] = generateRandomWeather();
    end
    
    % Print weather forecast
    fprintf('Temperature: %.0f degrees Fahrenheit\n', temperature);
    fprintf('Precipitation: %.2f inches\n', precipitation);
end

% Run the main function
main()