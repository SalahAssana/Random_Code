% Gaussian Distribution Generator
% A simple program that generates and plots random data following a Gaussian distribution.

% Import necessary libraries
import matplotlib.pyplot as plt
from scipy.stats import norm

% Define parameters for Gaussian distribution
mu = 0; % mean
sigma = 1; % standard deviation
num_samples = 10000; % number of samples

% Generate random data following the Gaussian distribution
data = norm.rvs(mu, sigma, num_samples);

% Plot the histogram of generated data
plt.hist(data, bins=30, density=True);

% Add a plot of the underlying Gaussian distribution
x = plt.linspace(mu - 3*sigma, mu + 3*sigma, 100);
y = norm.pdf(x, mu, sigma);
plt.plot(x, y);

% Show the plot
plt.show();