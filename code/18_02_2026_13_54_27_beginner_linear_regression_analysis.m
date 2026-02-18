% Linear Regression Analysis in MATLAB

% Load the dataset (synthetic data)
X = [1 2 3 4 5; 6 7 8 9 10];
y = [0.5 1 1.5 2 2.5];

% Add a column of ones for the intercept term
X = [ones(size(X,1),1) X];

% Coefficients (theta)
theta = zeros(2,1);

% Learning rate and maximum number of iterations
alpha = 0.01;
max_iter = 1000;

for i = 1:max_iter
    % Gradient calculation
    gradient = (X'*((X*theta - y))) / size(X,1);
    
    % Update theta
    theta = theta - alpha * gradient;
end

% Print the final coefficients
fprintf('Intercept: %.4f\n', theta(1));
fprintf('Slope: %.4f\n', theta(2));

% Plot the data and regression line
plot(X(:,2), y, 'o');
hold on;
x = [min(X(:,2)) : 0.1 : max(X(:,2))];
y = x * theta(2) + theta(1);
plot(x, y);
xlabel('X');
ylabel('Y');
title('Linear Regression Analysis');