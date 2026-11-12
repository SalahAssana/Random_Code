% K-Means Clustering Algorithm
%
% Copyright 2023, [Your Name]
%

function [centroids, assignments] = kmeans(data, num_clusters)
    % Check if data is a matrix
    if size(data, 2) ~= 2
        error('Data must be a matrix with two columns');
    end

    % Check if num_clusters is a positive integer
    if ~isinteger(num_clusters) || num_clusters < 1
        error('num_clusters must be a positive integer');
    end

    % Initialize centroids randomly
    centroids = data(randperm(size(data, 1)), :);

    % Initialize assignments
    assignments = zeros(size(data, 1), 1);

    % Iterate until convergence or max iterations reached
    for i = 1:1000
        for j = 1:size(data, 1)
            % Calculate distances to each centroid
            dists = bsxfun(@minus, data(j,:), centroids).^2;
            dists = sum(dists, 2);

            % Assign the point to the closest centroid
            [~, assignments(j)] = min(dists);
        end

        % Update centroids based on new assignments
        for k = 1:num_clusters
            cluster_points = data(assignments==k,:);
            if ~isempty(cluster_points)
                centroids(k,:) = mean(cluster_points, 1);
            else
                centroids(k,:) = zeros(1, size(data, 2));
            end
        end

        % Check for convergence
        if all(centroids == centroids(i-1,:))
            break;
        end
    end

    % Output results
    fprintf('Converged after %d iterations.\n', i);
end

% Example usage:
data = rand(100, 2);
num_clusters = 3;

[centroids, assignments] = kmeans(data, num_clusters);

figure;
scatter(data(:,1), data(:,2));
hold on;
scatter(centroids(:,1), centroids(:,2), 'r', 'o');
hold off;