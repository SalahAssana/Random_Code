% Define function to calculate Euclidean distance between two points
function dist = euclideanDistance(p1, p2)
    dist = sqrt((p1(1) - p2(1))^2 + (p1(2) - p2(2))^2);
end

% Define function to perform K-Means clustering on an image
function [labels, centroids] = kMeans(image, K)
    % Get dimensions of the image
    [rows, cols, ~] = size(image);

    % Initialize labels and centroids
    labels = zeros(rows, cols);
    centroids = rand(1, 3, K); % Randomly initialize centroids

    % Perform K-Means clustering
    for i = 1:50 % Run K-Means for a maximum of 50 iterations
        oldCentroids = centroids;
        
        % Calculate distances from each pixel to the current centroids
        dists = zeros(rows, cols, K);
        for j = 1:K
            dists(:, :, j) = euclideanDistance(reshape(image(:,:,1), rows*cols, 3), reshape(centroids(:,:,j), 1, 3)) + ...
                euclideanDistance(reshape(image(:,:,2), rows*cols, 3), reshape(centroids(:,:,j), 1, 3)) + ...
                euclideanDistance(reshape(image(:,:,3), rows*cols, 3), reshape(centroids(:,:,j), 1, 3));
        end
        
        % Assign each pixel to the closest centroid
        for k = 1:K
            labels(dists(:, :, k) == min(dists(:, :, :)), :) = k;
        end
        
        % Calculate new centroids
        for j = 1:K
            clusterPixels = image(labels == j, :);
            if ~isempty(clusterPixels)
                centroids(:,:,j) = mean(reshape(clusterPixels, rows*cols*3, []), 1);
            else
                centroids(:,:,j) = oldCentroids(:,:,j); % Keep the same centroid if no pixels are assigned to it
            end
        end
        
        % Check for convergence
        if max(max(abs(oldCentroids - centroids))) < 0.01
            break;
        end
    end
    
    % Assign each pixel to its closest cluster center
    labels = k;
end

% Read the image
image = imread('kmeans_example.png');

% Perform K-Means clustering with K = 5
[labels, centroids] = kMeans(image, 5);

% Display the segmented image
figure; imshow(segmentedImage);