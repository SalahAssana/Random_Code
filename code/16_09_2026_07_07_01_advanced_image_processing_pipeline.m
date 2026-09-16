% ADVANCED Image Processing Pipeline
classdef ImageProcessingPipeline
    methods(Static)
        function [filtered_image, edges] = process_image(image_path)
            % Load image
            image = imread(image_path);
            
            % Convert to grayscale
            gray_image = rgb2gray(image);
            
            % Apply Gaussian filter for smoothing
            filtered_image = imfilter(gray_image, fspecial('gaussian', 5, 0.3));
            
            % Threshold the image
            thresholded_image = imbinarize(filtered_image, 0.7);
            
            % Detect edges using Canny edge detection algorithm
            [edges, ~] = edge(thresholded_image, 'canny');
        end
    end
end

% Main function to test the pipeline
function main
    image_path = 'path_to_your_image.jpg';  % Replace with your own image path
    
    [filtered_image, edges] = ImageProcessingPipeline.process_image(image_path);
    
    % Display the filtered and edge-detected images
    figure;
    subplot(1,2,1); imshow(filtered_image); title('Filtered Image');
    subplot(1,2,2); imshow(edges); title('Edge-Detected Image');
end