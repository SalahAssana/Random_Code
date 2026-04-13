% Image Segmentation using K-Means Clustering
%
% This script demonstrates how to segment objects in an image using K-Means clustering.

% Define the necessary classes and functions
classdef Object
    properties
        pixels
    end
end

function [objects, segmentedImage] = kmeansSegmentation(imagePath)
    % Load the image
    img = imread(imagePath);
    
    % Convert the image to RGB format
    rgbImg = ind2rgb(img, gray(256));
    
    % Define the number of clusters (K) and the maximum number of iterations
    K = 5;
    maxIterations = 1000;
    
    % Initialize the centroids
    centroids = zeros(K, size(rgbImg, 3));
    
    % Loop through each pixel in the image
    for i = 1:size(img, 1)
        for j = 1:size(img, 2)
            % Calculate the distance from the current pixel to each centroid
            distances = zeros(1, K);
            for k = 1:K
                distances(k) = sqrt(sum((rgbImg(i, j, :) - centroids(k, :)).^2));
            end
            
            % Assign the pixel to the closest centroid
            [minDistance, minIndex] = min(distances);
            rgbImg(i, j, :) = centroids(minIndex, :);
        end
    end
    
    % Update the centroids based on the assigned pixels
    for k = 1:K
        clusterPixels = zeros(1, size(img, 3));
        for i = 1:size(img, 1)
            for j = 1:size(img, 2)
                if rgbImg(i, j, :) == centroids(k, :)
                    clusterPixels = [clusterPixels; rgbImg(i, j, :)];
                end
            end
        end
        
        % Calculate the new centroid as the mean of the pixels in the cluster
        centroids(k, :) = mean(clusterPixels);
    end
    
    % Repeat until convergence or maximum iterations reached
    for iteration = 1:maxIterations
        % Assign each pixel to the closest centroid
        for i = 1:size(img, 1)
            for j = 1:size(img, 2)
                distances = zeros(1, K);
                for k = 1:K
                    distances(k) = sqrt(sum((rgbImg(i, j, :) - centroids(k, :)).^2));
                end
                
                [minDistance, minIndex] = min(distances);
                rgbImg(i, j, :) = centroids(minIndex, :);
            end
        end
        
        % Update the centroids based on the assigned pixels
        for k = 1:K
            clusterPixels = zeros(1, size(img, 3));
            for i = 1:size(img, 1)
                for j = 1:size(img, 2)
                    if rgbImg(i, j, :) == centroids(k, :)
                        clusterPixels = [clusterPixels; rgbImg(i, j, :)];
                    end
                end
            end
            
            % Calculate the new centroid as the mean of the pixels in the cluster
            centroids(k, :) = mean(clusterPixels);
        end
        
        % Check for convergence
        converged = true;
        for k = 1:K
            for l = 1:size(img, 3)
                if abs(centroids(k, l) - oldCentroids(k, l)) > 0.001
                    converged = false;
                    break
                end
            end
            
            if ~converged
                break
            end
        end
        
        if converged
            break
        end
        
        % Store the previous centroids for the next iteration
        oldCentroids = centroids;
    end
    
    % Segment the image based on the final centroids
    segmentedImage = zeros(size(img));
    for i = 1:size(img, 1)
        for j = 1:size(img, 2)
            distances = zeros(1, K);
            for k = 1:K
                distances(k) = sqrt(sum((rgbImg(i, j, :) - centroids(k, :)).^2));
            end
            
            [minDistance, minIndex] = min(distances);
            segmentedImage(i, j) = minIndex;
        end
    end
    
    % Create objects for each cluster
    objects = cell(1, K);
    for k = 1:K
        pixels = zeros(1, size(img, 3));
        for i = 1:size(img, 1)
            for j = 1:size(img, 2)
                if segmentedImage(i, j) == k
                    pixels = [pixels; rgbImg(i, j, :)];
                end
            end
            
            objects{k} = Object();
            objects{k}.pixels = pixels;
    end
    
    % Display the segmented image and the cluster statistics
    figure;
    imshow(segmentedImage);
    
    for k = 1:K
        subplot(2, K, k + 1);
        scatter3(pixels(:, 1), pixels(:, 2), pixels(:, 3));
        title(num2str(k));
    end
end

% Test the function with a synthetic image
kmeansSegmentation('syntheticImage.png');