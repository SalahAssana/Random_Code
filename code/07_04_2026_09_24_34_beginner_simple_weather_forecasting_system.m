% Simple Weather Forecasting System in MATLAB
% BEGINNER Level Implementation

% Import necessary libraries
clear; clc; close all;
import mlr.*

% Synthetic Data for simplicity (real-world data would be more complex)
temperatureData = [20, 22, 25, 27, 30, 32, 35];
humidityData = [50, 60, 70, 80, 90, 100, 110];

% Define the weather forecasting function
function [forecastTemperature, forecastHumidity] = predictWeather(currentTemperature, currentHumidity)
    % Simple linear regression-based prediction for temperature
    forecastTemperature = (currentTemperature + 1) * (length(temperatureData) / length(humidityData));
    
    % Simple linear regression-based prediction for humidity
    forecastHumidity = (currentHumidity + 5) * (length(humidityData) / length(temperatureData));
end

% Call the weather forecasting function with initial data
[forecastTemperature, forecastHumidity] = predictWeather(temperatureData(1), humidityData(1));

% Display the predicted results
fprintf('Predicted Temperature: %.2f degrees Celsius\n', forecastTemperature);
fprintf('Predicted Humidity: %.0f %%\n', forecastHumidity);

% Run the code to see the output
if ~exist('test.mex')
    predictWeather(temperatureData(1), humidityData(1));