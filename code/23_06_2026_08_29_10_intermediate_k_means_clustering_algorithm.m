% K-Means Clustering Algorithm
% Author: Your Name

% Import necessary libraries
import ml;

% Define the K-Means function
function [centroids, labels] = kmeans(data, k)
    % Initialize centroids randomly
    centroids = data(randperm(size(data, 1)), :);
    
    % Initialize labels with -1 (unknown cluster)
    labels = -ones(size(data, 1), 1);
    
    % Repeat until convergence or maximum iterations
    for i = 1:100
        % Assign each data point to the closest centroid
        for j = 1:size(data, 1)
            distances = sqrt(sum((data(j, :) - centroids).^2));
            [min_dist, idx] = min(distances);
            labels(j) = idx;
        end
        
        % Update centroids based on assigned labels
        new_centroids = zeros(size(centroids));
        for c = 1:k
            indices = find(labels == c);
            new_centroids(c, :) = mean(data(indices, :), 1);
        end
        
        % Check for convergence (if all centroids are the same)
        if norm(new_centroids - centroids) < eps
            break;
        end
        
        % Update centroids
        centroids = new_centroids;
    end
    
    % Return final centroids and labels
    return [centroids, labels];
end

% Load synthetic data
data = [
    1.2 3.4 5.6;
    0.8 2.9 4.7;
    1.5 3.1 5.3;
    0.9 2.5 4.2;
    1.8 3.6 5.9;
    0.7 2.8 4.5;
    1.3 3.3 5.8;
    0.6 2.4 4.1;
    1.9 3.7 6.1;
    0.5 2.6 4.3;
];

% Run K-Means with k = 3
[k] = size(data, 2);
[centroids, labels] = kmeans(data, 3);

% Display results
figure;
scatter(data(:, 1), data(:, 2), 'o');
hold on;
for c = 1:k
    indices = find(labels == c);
    scatter(data(indices, 1), data(indices, 2), 'o', 'filled', ...
        {'color', ['rgbc'][c], 'markerfacecolor', ['rgbc'][c]});
end
xlabel('Feature 1');
ylabel('Feature 2');
title('K-Means Clustering with k = 3');