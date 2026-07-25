% Linear Regression Analysis
%
% Copyright 2022 The MathWorks, Inc.

% Define synthetic data
n_samples = 100;
x_data = rand(n_samples, 1);
y_data = 3 * x_data + 2 * randn(size(x_data));

% Define function to perform linear regression
function [w, b] = linreg(x, y)
    % Calculate mean of input features and target variable
    x_mean = mean(x);
    y_mean = mean(y);
    
    % Calculate covariance matrix
    cov_matrix = (x - x_mean)' * (y - y_mean) / (n_samples - 1);
    
    % Calculate weights and bias
    w = cov_matrix(1) / var(x);
    b = y_mean - w * x_mean;
end

% Perform linear regression on synthetic data
[w, b] = linreg(x_data, y_data);

% Define function to visualize linear regression results
function [] = plot_linear_regression(x, y, w, b)
    % Create figure and axis
    fig = figure();
    ax = axes('Parent', fig);
    
    % Plot original data
    scatter(x, y, 'MarkerEdgeColor', 'b');
    
    % Plot linear regression line
    x_range = [min(x) max(x)];
    y_range = w * x_range + b;
    plot(x_range, y_range, '--k');
    
    % Set title and labels
    title('Linear Regression Results');
    xlabel('Feature Values');
    ylabel('Target Variable');
end

% Visualize linear regression results on synthetic data
plot_linear_regression(x_data, y_data, w, b);

% Show figure
fig.Visible = 'on';