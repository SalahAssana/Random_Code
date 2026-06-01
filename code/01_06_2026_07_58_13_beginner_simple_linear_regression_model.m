% Simple Linear Regression Model
% Author: [Your Name]

% Import necessary libraries
clear all; close all; clc;
import mlrx.*

% Generate synthetic data for X and Y
X = rand(100, 1);
Y = 2 + 3 * X + randn(100, 1);

% Split data into training and testing sets (80% for training)
idx = randperm(size(X,1));
train_idx = idx(1:80);
test_idx = idx(81:end);

X_train = X(train_idx,:);
Y_train = Y(train_idx);

X_test = X(test_idx,:);
Y_test = Y(test_idx);

% Define the linear regression model
model = @() 3 * X + 2;

% Train the model using the training data
coeffs = fit(X_train, Y_train, model);

% Make predictions on the testing data
Y_pred = model(X_test);

% Calculate mean squared error (MSE) for the model
mse = mean((Y_test - Y_pred).^2);

% Print results
fprintf('Coefficients: %f\n', coeffs);
fprintf('Mean Squared Error: %.4f\n', mse);