% Simple Weather Forecasting using Linear Regression
% BEGINNER complexity project

% Load necessary libraries
load weather_data.mat  % Assuming you have a 'weather_data.mat' file containing historical data
% Alternatively, you can create your own synthetic dataset and save it as 'weather_data.mat'

% Define the input features (X) and output labels (y)
X = weather_data(:, 1:2);  % Assuming you have two input features: temperature and humidity
y = weather_data(:, 3);  % Assuming you have one output label: precipitation

% Split data into training and testing sets
train_size = 0.8;  % 80% for training, 20% for testing
[X_train, X_test, y_train, y_test] = splitData(X, y, train_size);

% Train a linear regression model using the training data
b = (X_train \ y_train);  % Slope/Co-efficient of the line
a = mean(y_train) - b * mean(X_train);  % Intercept/Y-intercept

% Use the trained model to make predictions on the testing data
y_pred = a + X_test * b;

% Calculate the Mean Absolute Error (MAE) between predicted and actual values
mae = mean(abs(y_test - y_pred));

% Display results
fprintf('Linear Regression Model Trained.\n');
fprintf('Mean Absolute Error: %.2f\n', mae);

% Function to split data into training and testing sets
function [X_train, X_test, y_train, y_test] = splitData(X, y, train_size)
    idx = randperm(size(X, 1));
    train_idx = idx(1:round(train_size*size(X, 1)));
    test_idx = setdiff(1:size(X, 1), train_idx);
    
    X_train = X(train_idx, :);
    X_test = X(test_idx, :);
    y_train = y(train_idx);
    y_test = y(test_idx);
end