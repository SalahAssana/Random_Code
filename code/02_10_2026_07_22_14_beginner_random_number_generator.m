% Random Number Generator
% This program generates random numbers using various statistical distributions

% Import necessary libraries
rng default; % For reproducibility
import statistics.*

% Define the number of samples to generate
num_samples = 1000;

% Generate random numbers from different distributions
uniform_numbers = uniform(num_samples, 1);
normal_numbers = normrnd(0, 1, num_samples, 1);
poisson_numbers = poissrnd(5, num_samples, 1);
exponential_numbers = exprnd(2, num_samples, 1);

% Display the generated numbers
fprintf('Uniform Random Numbers:\n');
disp(uniform_numbers);

fprintf('\nNormal (Gaussian) Random Numbers:\n');
disp(normal_numbers);

fprintf('\nPoisson Random Numbers:\n');
disp(poisson_numbers);

fprintf('\nExponential Random Numbers:\n');
disp(exponential_numbers);