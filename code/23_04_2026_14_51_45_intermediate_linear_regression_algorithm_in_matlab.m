% Linear Regression Algorithm in MATLAB
% Author: [Your Name]

% Load the dataset (synthetic data)
X = rand(100, 2);
y = 3 * X(:, 1) + 2 * X(:, 2) + randn(100, 1);

% Define a function to compute mean squared error (MSE)
function mse = compute_mse(y_pred, y_true)
    diff = y_pred - y_true;
    mse = mean(diff .^ 2);
end

% Define the linear regression algorithm
function [w, b] = linear_regression(X, y, iterations)
    m = size(X, 1);
    w = zeros(size(X, 2), 1);
    b = 0;

    for i = 1:iterations
        % Compute the predictions
        predictions = X * w + b;

        % Compute the errors
        errors = predictions - y;

        % Update the weights and bias using gradient descent
        dw = (1 / m) * X' * errors;
        db = (1 / m) * sum(errors);

        w = w - 0.01 * dw;
        b = b - 0.01 * db;
    end

    [w, max_idx] = max(abs(w));
    if max_idx > 1
        % Standardize the features
        X_stand = (X - mean(X)) / std(X);
    else
        X_stand = X;
    end
end

% Implement the algorithm and visualize the results
[weights, bias] = linear_regression(X, y, 1000);

% Compute the predictions
predictions = X * weights + bias;

% Plot the original data
figure;
scatter(X(:, 1), X(:, 2), y);
xlabel('Feature 1');
ylabel('Feature 2');
zlabel('Target');

% Plot the predicted data
hold on;
plot(X(:, 1), X(:, 2), predictions, 'r');
legend('Original', 'Predicted');

% Compute and display the MSE
mse = compute_mse(predictions, y);
fprintf('Mean Squared Error (MSE): %.4f\n', mse);

% Display the learned weights and bias
fprintf('Learned Weights: [%.4f, %.4f]\n', weights(1), weights(2));
fprintf('Learned Bias: %.4f\n', bias);

% Pause for 5 seconds before exiting
pause(5);