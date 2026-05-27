% Image Processing App
classdef EdgeDetector < handle
    methods
        function obj = EdgeDetector()
            % Initialize edge detection parameters
            obj.threshold = 0.5;
            obj.blurSigma = 1.5;
        end
        
        function [image, edges] = applyFilter(obj, image)
            % Apply blur filter to the input image
            blurredImage = imgaussfilt(image, obj.blurSigma);
            
            % Convert the blurred image to grayscale
            grayImage = rgb2gray(blurredImage);
            
            % Compute the Laplacian of Gaussian (LoG) edge detection mask
            logMask = fspecial('log', 5, 1.5);
            
            % Apply the LoG mask to the grayscale image
            edges = imfilter(grayImage, logMask, 'replicate');
        end
        
        function [image] = applyThreshold(obj, edges)
            % Threshold the edge map using a binary thresholding approach
            thresholdedEdges = edges > obj.threshold;
            
            % Replace thresholded values with 255 (white) and non-thresholded values with 0 (black)
            image = im2bw(thresholdedEdges);
        end
    end
end

% Main script
function main()
    % Load the test image
    image = imread('test_image.jpg');
    
    % Create an instance of the EdgeDetector class
    detector = EdgeDetector();
    
    % Apply the edge detection filter and thresholding to the input image
    [filteredImage, edges] = detector.applyFilter(image);
    filteredImage = detector.applyThreshold(edges);
    
    % Display the original and processed images
    subplot(1, 2, 1); imshow(image); title('Original Image');
    subplot(1, 2, 2); imshow(filteredImage); title('Processed Image');
end

main();