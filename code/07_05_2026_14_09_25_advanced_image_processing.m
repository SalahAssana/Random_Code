% ADVANCED Image Processing Program
%
% This program demonstrates the application of filters (blur and threshold) to an image.

classdef FilteredImageProcessor < handle
    methods
        function obj = FilteredImageProcessor(imagePath)
            % Load the input image
            img = imread(imagePath);
            
            % Apply blur filter
            blurredImg = applyBlurFilter(img, 5);
            
            % Apply threshold filter
            thresholdedImg = applyThresholdFilter(blurredImg, 127);
            
            % Display the original and processed images
            displayImages(img, thresholdedImg);
        end
        
        function filteredImage = applyBlurFilter(image, radius)
            % Calculate the filter mask
            [height, width, ~] = size(image);
            filterMask = zeros(height, width);
            for i = 1:radius
                for j = 1:radius
                    filterMask((i+1-ceil(radius/2)):min(i+1+floor(radius/2), height), (j+1-ceil(radius/2)):min(j+1+floor(radius/2), width)) = 1;
                end
            end
            
            % Convolve the image with the filter mask
            filteredImage = conv2(image, filterMask, 'same');
        end
        
        function filteredImage = applyThresholdFilter(image, threshold)
            % Convert the image to grayscale
            grayImage = rgb2gray(image);
            
            % Threshold the image
            filteredImage = grayImage > threshold;
        end
        
        function displayImages(originalImage, processedImage)
            % Display the original and processed images side-by-side
            figure('Name', 'Original vs. Processed Images');
            subplot(1, 2, 1);
            imshow(originalImage);
            title('Original Image');
            subplot(1, 2, 2);
            imshow(processedImage);
            title('Processed Image');
        end
    end
end

% Main script
if nargin == 0
    imagePath = 'path_to_your_image.jpg';  % Replace with your image path
else
    imagePath = varargin{1};
end

processor = FilteredImageProcessor(imagePath);