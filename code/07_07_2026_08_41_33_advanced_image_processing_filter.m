% ADVANCED Image Processing Filter
%
% This filter applies various advanced filters and effects to input images.

classdef AdvancedImageFilter
    methods(Static)
        function filteredImage = applyFilters(inputImage)
            % Read the input image.
            if nargin < 1 || isempty(inputImage)
                inputImage = imread('input.png');
            end
            
            % Apply a Sobel edge detection filter.
            sobelX = fspecial('sobel', [3 3]);
            sobelY = fspecial('sobel', [3 3]);
            gradientX = imfilter(inputImage, sobelX, 'replicate');
            gradientY = imfilter(inputImage, sobelY, 'replicate');
            magnitude = sqrt(gradientX.^2 + gradientY.^2);
            
            % Apply a Gaussian blur filter.
            sigma = 1;
            [h, w] = size(inputImage);
            outputImage = zeros(h, w);
            for i = 1:h
                for j = 1:w
                    sum = 0;
                    for k = -sigma:sigma
                        for l = -sigma:sigma
                            if (i + k > 0) && (i + k <= h) && (j + l > 0) && (j + l <= w)
                                sum = sum + inputImage(i + k, j + l) * exp(-((k/sigma)^2 + (l/sigma)^2));
                            end
                        end
                    end
                    outputImage(i, j) = sum;
                end
            end
            
            % Apply a median filter.
            structuringElement = ones(3);
            filteredImage = medfilt2(inputImage, structuringElement, 'symmetric');
        end
    end
end

% Example usage:
inputImage = imread('input.png');
filteredImage = AdvancedImageFilter.applyFilters(inputImage);
imwrite(filteredImage, 'output.png');