% Simple Plotter in MATLAB
% Plots the function y = x^2 for x from 0 to 10

% Include necessary imports/includes
%

% Define the function to plot
f = @(x) x.^2;

% Create an array of x values from 0 to 10
x = 0:0.1:10;

% Evaluate the function at each x value
y = f(x);

% Plot the results
plot(x, y);
xlabel('X');
ylabel('Y');
title('Simple Plotter in MATLAB');