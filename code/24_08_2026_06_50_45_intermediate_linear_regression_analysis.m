% Linear Regression Analysis using Gradient Descent
%
% Author: Your Name Here
%

function lin_regression()
    % Load synthetic data
    X = [1; 2; 3; 4; 5];
    y = [2; 3; 5; 7; 11];

    % Initialize parameters and hyperparameters
    theta0 = 0;
    theta1 = 0;
    alpha = 0.01;
    iterations = 1000;

    % Compute linear regression using gradient descent
    for i = 1:iterations
        predictions = X .* theta1 + theta0;
        residuals = y - predictions;
        cost = (residuals' * residuals) / length(X);
        gradients = [sum(-X .* residuals), sum(-residuals)];
        theta1 = theta1 - alpha * mean(gradients(1:end-1));
        theta0 = theta0 - alpha * mean(gradients(end));
    end

    % Plot the results
    x_values = 1:5;
    y_values = theta1 * x_values + theta0;
    plot(X, y, 'ro', x_values, y_values, 'b');
    xlabel('X Values');
    ylabel('Y Values');
    title('Linear Regression using Gradient Descent');
end

lin_regression();