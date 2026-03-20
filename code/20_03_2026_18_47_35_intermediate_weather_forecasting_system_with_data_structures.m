% Weather Forecasting System with Data Structures
%
% Copyright 2023 Author Name

function weather_forecast()
    % Initialize data structures for storing climate data
    global climate_data;
    climate_data = struct('date', {}, 'temperature', {}, 'humidity', {});
    
    % Function to add new climate data points
    function add_climate_data(date, temperature, humidity)
        climate_data.date{end+1} = date;
        climate_data.temperature{end+1} = temperature;
        climate_data.humidity{end+1} = humidity;
    end
    
    % Function to calculate average temperature and humidity for a given date range
    function [avg_temp, avg_humidity] = get_avg_climate_data(start_date, end_date)
        temp_sum = 0;
        hum_sum = 0;
        
        % Traverse the climate data structure to find relevant data points
        for i = 1:length(climate_data.date)
            if strcmp(climate_data.date{i}, start_date) || strcmp(climate_data.date{i}, end_date)
                temp_sum = temp_sum + climate_data.temperature{i};
                hum_sum = hum_sum + climate_data.humidity{i};
            end
        end
        
        % Calculate average temperature and humidity
        avg_temp = temp_sum / length(climate_data.date);
        avg_humidity = hum_sum / length(climate_data.date);
    end
    
    % Main program to interact with the user
    while true
        disp('Weather Forecasting System');
        disp('-------------------------');
        disp('1. Add new climate data point');
        disp('2. Get average temperature and humidity for a given date range');
        disp('3. Exit');
        
        choice = input('Enter your choice (1/2/3): ', 's');
        
        switch choice
            case '1'
                % Ask user to enter the new climate data point details
                date = input('Enter date: ', 's');
                temperature = input('Enter temperature: ');
                humidity = input('Enter humidity: ');
                
                % Add the new climate data point
                add_climate_data(date, temperature, humidity);
            case '2'
                start_date = input('Enter start date: ', 's');
                end_date = input('Enter end date: ', 's');
                
                % Calculate and display the average temperature and humidity
                [avg_temp, avg_humidity] = get_avg_climate_data(start_date, end_date);
                disp(['Average Temperature: ', num2str(avg_temp)]);
                disp(['Average Humidity: ', num2str(avg_humidity)]);
            case '3'
                break;
            otherwise
                disp('Invalid choice. Please try again.');
        end
    end
    
end

% Run the weather forecasting system
weather_forecast();