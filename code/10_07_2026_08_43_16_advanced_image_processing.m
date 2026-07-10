% Image Processing
% ADVANCED-level program that applies basic image processing techniques (such as thresholding or edge detection) to an input image.

classdef EdgeDetector < handle
    properties
        threshold
    end
    
    methods
        function obj = EdgeDetector(threshold)
            obj.threshold = threshold;
        end
        
        function [edges] = detect(obj, image)
            grayImage = rgb2gray(image);
            edges = imadjustthreshold(grayImage, obj.threshold, 0.5);
        end
    end
end

classdef ThresholdingTechnique < handle
    properties
        threshold
    end
    
    methods
        function obj = ThresholdingTechnique(threshold)
            obj.threshold = threshold;
        end
        
        function [binaryImage] = apply(obj, image)
            grayImage = rgb2gray(image);
            binaryImage = im2bw(grayImage, obj.threshold);
        end
    end
end

% Create an instance of EdgeDetector with a threshold value of 0.5
edgeDetector = EdgeDetector(0.5);

% Load the image 'cameraman.tif' from the file
image = imread('cameraman.tif');

% Apply edge detection on the image using the created instance of EdgeDetector
edges = edgeDetector.detect(image);

% Display the detected edges
figure; imshow(edges); title('Detected Edges');

% Create an instance of ThresholdingTechnique with a threshold value of 0.5
thresholdingTechnique = ThresholdingTechnique(0.5);

% Apply thresholding on the image using the created instance of ThresholdingTechnique
binaryImage = thresholdingTechnique.apply(image);

% Display the binary image
figure; imshow(binaryImage); title('Binary Image');