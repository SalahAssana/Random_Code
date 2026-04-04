% Linear Regression Analysis
% Author: [Your Name]

% Load synthetic data
data = load('synthetic_data.mat');

% Define function to perform linear regression
function [slope, intercept] = linear_regression(x, y)
    % Calculate mean of x and y
    mean_x = mean(x);
    mean_y = mean(y);
    
    % Calculate numerator and denominator for slope calculation
    numerator = sum((x - mean_x) .* (y - mean_y));
    denominator = sum((x - mean_x).^2);
    
    % Calculate slope
    slope = numerator / denominator;
    
    % Calculate intercept using the equation y = mx + b, where m is the slope and b is the intercept
    intercept = mean_y - slope * mean_x;
end

% Main script
if nargin < 1 || isempty(data)
    data.x = [0.5, 1, 2, 3, 4, 5];
    data.y = [0.7, 1.5, 2.5, 3.5, 4.5, 5.5];
end

% Perform linear regression
[slope, intercept] = linear_regression(data.x, data.y);

% Print results
fprintf('Slope: %f\n', slope);
fprintf('Intercept: %f\n', intercept);

% Predict y values using the model
predicted_y = slope * data.x + intercept;

% Plot original and predicted y values
plot(data.x, data.y, 'o', data.x, predicted_y, '-');
xlabel('X');
ylabel('Y');
title('Linear Regression Analysis');