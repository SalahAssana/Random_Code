% Simple Weather Forecast
% Copyright 2023 Beginner Level Project

% Import necessary libraries
import statistics;

% Define historical temperature data (synthetic)
temp_data = [20, 22, 25, 28, 30, 32, 35, 38, 40];

% Calculate mean temperature
mean_temp = mean(temp_data);

% Calculate median temperature
median_temp = median(temp_data);

% Calculate mode temperature
mode_temp = mode(temp_data);

% Define function to predict weather based on temperature
function predicted_weather = predict_weather(current_temp)
    if current_temp > mean_temp
        predicted_weather = 'Hot';
    elseif current_temp < mean_temp
        predicted_weather = 'Cold';
    else
        predicted_weather = 'Average';
    end
end

% Predict the weather for each day in historical data
predicted_weathers = zeros(size(temp_data));
for i = 1:length(temp_data)
    predicted_weathers(i) = predict_weather(temp_data(i));
end

% Display results
disp(['Mean Temperature: ', num2str(mean_temp)]);
disp(['Median Temperature: ', num2str(median_temp)]);
disp(['Mode Temperature: ', num2str(mode_temp)]);
disp('Predicted Weathers:');
for i = 1:length(predicted_weathers)
    disp([num2str(temp_data(i)), ': ', predicted_weathers(i)]);
end