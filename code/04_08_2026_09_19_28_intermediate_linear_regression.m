% Linear Regression
% Author: [Your Name]

% Clear all variables and close figures
clear; close all;

% Define the function for linear regression
function beta = linear_regression(X, y)
    % Calculate mean of X and y
    n = length(y);
    x_mean = mean(X);
    y_mean = mean(y);

    % Calculate coefficients using ordinary least squares (OLS) method
    numerator = 0;
    denominator = 0;
    for i = 1:n
        numerator = numerator + (X(i) - x_mean)*(y(i) - y_mean);
        denominator = denominator + (X(i) - x_mean)^2;
    end

    beta = numerator / denominator;
end

% Define the function to calculate R-squared value
function rsq = r_squared(y, y_hat)
    % Calculate mean of actual and predicted values
    y_mean = mean(y);
    y_hat_mean = mean(y_hat);

    % Calculate sum of squared errors (SSE) and total sum of squares (SST)
    sse = sum((y - y_mean).^2);
    sst = sum((y - y_hat_mean).^2);

    % Calculate R-squared value
    rsq = 1 - (sse / sst);
end

% Generate synthetic data for demonstration purposes
n_samples = 100;
x = rand(n_samples, 1);
y = 3 * x + 0.5 * randn(size(x));

% Split data into training and testing sets
train_size = floor(0.8 * n_samples);
X_train = x(1:train_size, :);
y_train = y(1:train_size);
X_test = x(train_size+1:end, :);
y_test = y(train_size+1:end);

% Train the model using linear regression
beta = linear_regression(X_train, y_train);

% Calculate predicted values for training and testing sets
y_train_hat = X_train * beta;
y_test_hat = X_test * beta;

% Calculate R-squared value for training and testing sets
rsq_train = r_squared(y_train, y_train_hat);
rsq_test = r_squared(y_test, y_test_hat);

% Print the results
fprintf('Training R-squared: %f\n', rsq_train);
fprintf('Testing R-squared: %f\n', rsq_test);