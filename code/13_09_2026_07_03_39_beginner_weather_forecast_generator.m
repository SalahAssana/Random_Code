% Weather Forecast Generator

% Import necessary libraries
clear; clc;
format compact;

% Define weather parameters
temp = [25 20 15 10]; % Temperature in Celsius
humid = [60 70 50 40]; % Humidity in percentage
precip = ['Sunny', 'Cloudy', 'Rainy', 'Snowy']; % Precipitation conditions

% Generate forecast based on temperature, humidity, and precipitation data
for i = 1:length(temp)
    if temp(i) > 20 && humid(i) < 50
        forecast = [num2str(temp(i)) 'C with ' precip{i} and low humidity.';
    elseif temp(i) <= 10 || humid(i) >= 80
        forecast = [num2str(temp(i)) 'C with ' precipt{i} and high humidity.';
    else
        forecast = ['Partly cloudy at ' num2str(temp(i)) 'C with moderate humidity.'];
    end
    fprintf('Forecast for today: %s\n', forecast);
end

% End of program