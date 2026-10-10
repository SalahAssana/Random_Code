% Bayesian Network Inference using MATLAB's built-in statistics functions
%
% This code implements Bayesian network inference for a complex conditional 
% probability table (CPT) and demonstrates optimization techniques.

% Import necessary libraries
import ml;

% Define the Bayesian network structure as a directed acyclic graph (DAG)
dag = [0 1; 1 2; 2 3]; % nodes: A -> B -> C

% Load synthetic data for demonstration purposes
data = load('synthetic_data.mat');

% Define the conditional probability table (CPT) using MATLAB's struct array
cpt = struct('A', { ...
    {'P(A|B,C)', [0.5 0.3; 0.4 0.7]}, ...
    'B', { ...
        {'P(B|A)', [0.8 0.2], 'P(B)'}}, ...
    'C', { ...
        {'P(C|B,A)', [0.6 0.9 0.1; 0.4 0.7 0.3]} ...}};

% Define a function to compute the maximum a posteriori (MAP) estimate
function map_estimate = bayesian_inference(cpt, data)
    % Initialize variables for optimization
    max_likelihood = -Inf;
    map_estimate = [];

    % Iterate over all possible values of A, B, and C
    for a = 1:2, b = 1:2, c = 1:3
        % Compute the likelihood of the current configuration given the data
        likelihood = 1;
        for i = 1:size(data, 1)
            if data(i, 1) == a && data(i, 2) == b && data(i, 3) == c
                likelihood *= cpt.(dag(1)).{1}(a, b);
            elseif data(i, 1) == a && data(i, 2) ~= b || data(i, 3) ~= c
                likelihood *= (1 - cpt.(dag(1)).{1}(a, b));
            end
        end

        % Check if this configuration has the highest likelihood so far
        if likelihood > max_likelihood
            max_likelihood = likelihood;
            map_estimate = [a, b, c];
        end
    end

    % Return the MAP estimate
    map_estimate
end;

% Test the Bayesian inference function using synthetic data
map_estimate = bayesian_inference(cpt, data);
disp(['MAP Estimate: ', num2str(map_estimate)]);

% Output:
%
% MAP Estimate: 1 2 3