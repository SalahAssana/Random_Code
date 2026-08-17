% Weather Forecasting System
% Author: Your Name

% Import necessary libraries
import data.table

% Define structure for weather data
struct WeatherData
    date
    temperature
    humidity
    precipitation
end

% Function to calculate average temperature
function avgTemp = calcAvgTemp(temperature)
    % Check if input is empty
    if isempty(temperature)
        error('Temperature array is empty');
    end
    
    % Calculate average temperature
    avgTemp = mean(temperature);
end

% Function to predict weather based on historical data and user inputs
function [forecast, uncertainty] = predictWeather(historicalData, date, temperature, humidity, precipitation)
    % Check if input arrays are empty
    if isempty(historicalData) || isempty(date) || isempty(temperature) || isempty(humidity) || isempty(precipitation)
        error('Input arrays are empty');
    end
    
    % Filter historical data based on user inputs
    filteredData = historicalData((historicalData.date <= date) & (abs(historicalData.temperature - temperature) <= 1) & ...
                                    (abs(historicalData.humidity - humidity) <= 0.5) & (abs(historicalData.precipitation - precipitation) <= 0.2));
    
    % Calculate average values for filtered data
    avgTemp = calcAvgTemp(filteredData.temperature);
    avgHumidity = mean(filteredData.humidity);
    avgPrecipitation = mean(filteredData.precipitation);
    
    % Predict weather based on averages
    if avgTemp > 20 && avgHumidity < 0.5 && avgPrecipitation < 0.1
        forecast = 'Sunny';
    elseif avgTemp <= 10 || avgHumidity >= 0.8 || avgPrecipitation >= 2
        forecast = 'Rainy';
    else
        forecast = 'Cloudy';
    end
    
    % Calculate uncertainty based on standard deviation of filtered data
    stdDev = std([filteredData.temperature, filteredData.humidity, filteredData.precipitation]);
    uncertainty = [stdDev, stdDev, stdDev];
end

% Main function to test the weather forecasting system
function main()
    % Synthetic data for testing
    dateArray = {'2022-01-01', '2022-01-02', '2022-01-03'};
    temperature = [15, 18, 20];
    humidity = [0.4, 0.6, 0.5];
    precipitation = [0.1, 0.3, 0.2];
    
    % Create weather data structure
    historicalData = struct();
    for i = 1:length(dateArray)
        historicalData(i) = WeatherData(dateArray{i}, temperature(i), humidity(i), precipitation(i));
    end
    
    % Test the weather forecasting system
    dateInput = '2022-01-04';
    temperatureInput = 19;
    humidityInput = 0.7;
    precipitationInput = 0.5;
    
    [forecast, uncertainty] = predictWeather(historicalData, dateInput, temperatureInput, humidityInput, precipitationInput);
    
    % Display the forecast and uncertainty
    disp(['Forecast: ' forecast]);
    disp(['Uncertainty: ' num2str(uncertainty)]);
end

% Call the main function
main();