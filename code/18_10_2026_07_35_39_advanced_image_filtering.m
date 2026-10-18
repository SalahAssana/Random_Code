% Image Filtering Script
%
% This program applies a simple image filter (blur, sharpen, edge detection) to an input image using MATLAB's built-in functions and GUI tools.

classdef ImageFilter < handle
    properties
        inputImage
        outputImage
        filterType
    end
    
    methods
        function obj = ImageFilter(inputImage, filterType)
            obj.inputImage = inputImage;
            obj.outputImage = zeros(size(inputImage));
            obj.filterType = filterType;
        end
        
        function applyFilter(obj)
            switch obj.filterType
                case 'blur'
                    obj.outputImage = imgaussfilt(obj.inputImage, 2);
                case 'sharpen'
                    obj.outputImage = imsharpen(obj.inputImage, 'amount', 5);
                case 'edgeDetection'
                    obj.outputImage = edge(obj.inputImage, 'canny');
                otherwise
                    error('Invalid filter type');
            end
        end
        
        function displayResults(obj)
            figure;
            subplot(1,2,1);
            imshow(obj.inputImage);
            title('Original Image');
            subplot(1,2,2);
            imshow(obj.outputImage);
            title(['Filtered Image - ' obj.filterType]);
        end
    end
end

% Main script
if nargin == 0
    % Load a sample image
    inputImage = imread('image.jpg');
else
    inputImage = varargin{1};
end

filterType = 'blur';  % Default filter type is blur

% Create an ImageFilter object and apply the specified filter
filterObject = ImageFilter(inputImage, filterType);
filterObject.applyFilter();

% Display the original and filtered images
filterObject.displayResults();