% Project 5: Image Segmentation using k-means clustering and edge detection techniques in MATLAB.

classdef KMeans
    methods
        function obj = KMeans(k)
            % Constructor for K-Means algorithm.
            obj.k = k;
            obj.centroids = zeros(3, k);
            obj.labels = ones(size(img(:)))*-1;
        end
        
        function [labels, centroids] = cluster(obj, img)
            % Perform K-Means clustering on the image pixels.
            [rows, cols, ~] = size(img);
            pixels = reshape(img, rows*cols, 3);
            
            for i = 1:obj.k
                obj.centroids(:, i) = mean(pixels(: ,i), 2);
            end
            
            labels = assignClusters(obj, pixels, obj.centroids);
        end
        
        function labels = assignClusters(obj, pixels, centroids)
            % Assign each pixel to its closest centroid.
            for i = 1:size(pixels, 1)
                minDist = inf;
                closestCentroid = -1;
                for j = 1:obj.k
                    dist = norm(pixels(i,:) - centroids(:,j));
                    if dist < minDist
                        minDist = dist;
                        closestCentroid = j;
                    end
                end
                labels(i) = closestCentroid;
            end
        end
    end
    
end

classdef EdgeDetector
    methods
        function obj = EdgeDetector()
            % Constructor for Edge Detection algorithm.
            obj.filterSize = 3;
            obj.threshold = 0.5;
        end
        
        function edges = detect(obj, img)
            % Perform edge detection on the image using Sobel operator.
            [rows, cols, ~] = size(img);
            gradX = zeros(rows, cols);
            gradY = zeros(rows, cols);
            
            for i = 2:rows-1
                for j = 2:cols-1
                    if mod(i, obj.filterSize) == 0 && mod(j, obj.filterSize) == 0
                        % Calculate gradient in x and y directions.
                        gradX(i, j) = (img(i+1,j) - img(i-1,j)) + 2*(img(i+1,j+1) - img(i-1,j-1));
                        gradY(i, j) = (img(i,j+1) - img(i,j-1)) + 2*(img(i+1,j+1) - img(i-1,j-1));
                    end
                end
            end
            
            edges = zeros(rows, cols);
            
            for i = 2:rows-1
                for j = 2:cols-1
                    if gradX(i, j)^2 + gradY(i, j)^2 > obj.threshold^2
                        % Mark pixels with gradient magnitude above the threshold as edges.
                        edges(i, j) = 1;
                    end
                end
            end
        end
    end
    
end

function img = loadImage()
    % Load a sample image for testing.
    img = imread('image.jpg');
end

img = loadImage();
k = 5;  % Number of clusters for K-Means algorithm.
detector = EdgeDetector();

% Perform K-Means clustering on the image pixels.
clusterer = KMeans(k);
[labels, centroids] = cluster(clusterer, img);

% Segment the image based on the cluster labels.
segmentedImg = reshape(img, size(img, 1), size(img, 2), []);
for i = 1:k
    indices = find(labels == i-1);
    segmentedImg(:,:,i) = img(indices(:));
end

% Detect edges in the segmented images.
edges = detector.detect(segmentedImg);

figure;
imshow(edges, []);
