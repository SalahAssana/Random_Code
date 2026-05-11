% Image Processing Pipeline
% Advanced Level Implementation in MATLAB

classdef EdgeDetectionPipeline
    properties
        image
        filters
    end
    
    methods
        function obj = EdgeDetectionPipeline(image)
            % Constructor for pipeline
            obj.image = image;
            obj.filters = [];
        end
        
        function filteredImage = applyFilters(obj, filterType)
            % Apply filters to the input image
            if strcmp(filterType, 'blur')
                filteredImage = obj.applyBlurFilter();
            elseif strcmp(filterType, 'sharpen')
                filteredImage = obj.applySharpenFilter();
            else
                error('Invalid filter type');
            end
        end
        
        function blurredImage = applyBlurFilter(obj)
            % Apply blur filter using Gaussian filter
            size = 5;
            sigma = 1.4;
            [h, w] = size(obj.image);
            blurredImage = zeros(h, w);
            for i = 2:(size-1)
                for j = 2:(size-1)
                    sum = 0;
                    for k = -1:1
                        for l = -1:1
                            sum = sum + obj.image(i+k, j+l) * exp(-((k^2 + l^2) / (2*sigma^2)));
                        end
                    end
                    blurredImage(i, j) = sum;
                end
            end
        end
        
        function sharpenedImage = applySharpenFilter(obj)
            % Apply sharpen filter using Laplacian of Gaussian (LoG) filter
            size = 5;
            sigma = 1.4;
            [h, w] = size(obj.image);
            sharpenedImage = zeros(h, w);
            for i = 2:(size-1)
                for j = 2:(size-1)
                    sum = 0;
                    for k = -1:1
                        for l = -1:1
                            sum = sum + obj.image(i+k, j+l) * (1 - exp(-((k^2 + l^2) / (4*sigma^2))));
                        end
                    end
                    sharpenedImage(i, j) = sum;
                end
            end
        end
        
        function thresholdedImage = applyThreshold(obj, threshold)
            % Apply thresholding to the filtered image
            thresholdedImage = obj.image > threshold;
        end
        
        function edgeMap = detectEdges(obj)
            % Detect edges using Canny edge detection algorithm
            grayImage = rgb2gray(obj.image);
            [row, col] = size(grayImage);
            gradientMag = zeros(row, col);
            gradientDir = zeros(row, col, class('uint8'));
            for i = 2:(row-1)
                for j = 2:(col-1)
                    dx = grayImage(i+1, j) - grayImage(i-1, j);
                    dy = grayImage(i, j+1) - grayImage(i, j-1);
                    gradientMag(i, j) = sqrt(dx^2 + dy^2);
                    if abs(dx) > abs(dy)
                        gradientDir(i, j) = dx > 0 ? 0 : 180;
                    else
                        gradientDir(i, j) = dy > 0 ? 90 : 270;
                    end
                end
            end
            % Non-maximum suppression and double-thresholding
            highThreshold = 0.5 * max(gradientMag(:));
            lowThreshold = 0.2 * highThreshold;
            edgeMap = zeros(row, col);
            for i = 2:(row-1)
                for j = 2:(col-1)
                    if gradientMag(i, j) > highThreshold
                        edgeMap(i, j) = 255;
                    elseif gradientMag(i, j) > lowThreshold
                        [p1x, p1y] = find(gradientDir == 0);
                        [p2x, p2y] = find(gradientDir == 180);
                        if i == p1x && j == p1y || i == p2x && j == p2y
                            edgeMap(i, j) = 255;
                        end
                    end
                end
            end
        end
    end
    
    methods (Static)
        function [image] = readImage(filename)
            % Read image file using MATLAB's built-in functions
            [image, ~] = imread(filename);
        end
        
        function displayImage(image, title)
            % Display the processed image with a specified title
            imshow(image), title(title);
        end
    end
    
end

% Main script to test the pipeline
if true
    filename = 'input.png';
    [image] = EdgeDetectionPipeline.readImage(filename);
    pipeline = EdgeDetectionPipeline(image);
    
    % Apply filters and thresholding
    filteredImage = pipeline.applyFilters('blur');
    thresholdedImage = pipeline.applyThreshold(0.5);
    edgeMap = pipeline.detectEdges();
    
    % Display the processed images
    EdgeDetectionPipeline.displayImage(image, 'Original Image');
    EdgeDetectionPipeline.displayImage(filteredImage, 'Blurred Image');
    EdgeDetectionPipeline.displayImage(thresholdedImage, 'Thresholded Image');
    EdgeDetectionPipeline.displayImage(edgeMap, 'Edge Map');
end