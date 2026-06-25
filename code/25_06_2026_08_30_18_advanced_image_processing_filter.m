% ADVANCED Image Processing Filter in MATLAB
%
% Copyright 2023 Your Name
%

classdef ImageFilter < handle
    properties
        image; % input image
        kernel; % convolution kernel
        outputImage; % processed image
    end
    
    methods
        function obj = ImageFilter(image, kernel)
            obj.image = image;
            obj.kernel = kernel;
            obj.outputImage = zeros(size(obj.image));
        end
        
        function applyFilter(obj)
            [rows, cols, ~] = size(obj.image);
            for i = 1:rows
                for j = 1:cols
                    % Convolve the pixel with the kernel
                    sum = 0;
                    for k = -round(size(obj.kernel, 2)/2):round(size(obj.kernel, 2)/2)
                        for l = -round(size(obj.kernel, 1)/2):round(size(obj.kernel, 1)/2)
                            if (i+k > 0 && i+k <= rows && j+l > 0 && j+l <= cols)
                                sum = sum + obj.image(i+k, j+l) * obj.kernel(k+round(size(obj.kernel, 2)/2)+1, l+round(size(obj.kernel, 1)/2)+1);
                            end
                        end
                    end
                    
                    % Apply the filter to the pixel
                    if strcmpi(obj.kernel(round(size(obj.kernel, 2)/2), round(size(obj.kernel, 1)/2)), 'blur')
                        obj.outputImage(i, j) = sum;
                    elseif strcmpi(obj.kernel(round(size(obj.kernel, 2)/2), round(size(obj.kernel, 1)/2)), 'sharpen')
                        obj.outputImage(i, j) = max(0, min(255, sum + (obj.image(i, j) - mean(double(obj.image(:))))) );
                    end
                end
            end
        end
        
        function displayOutput(obj)
            figure;
            imshow(obj.outputImage);
            title('Filtered Image');
        end
    end
    
end

% Test the filter with a sample image and kernel
if true
    % Load an example image
    image = imread('image.jpg');
    
    % Define the convolution kernel for blur or sharpen effect
    kernelBlur = ones(5, 5) / 25;
    kernelSharpen = [0 -1 0; -1 5 -1; 0 -1 0];
    
    % Create an instance of the ImageFilter class
    filterBlur = ImageFilter(image, kernelBlur);
    filterSharpen = ImageFilter(image, kernelSharpen);
    
    % Apply the blur and sharpen filters to the image
    filterBlur.applyFilter();
    filterSharpen.applyFilter();
    
    % Display the filtered images
    filterBlur.displayOutput();
    filterSharpen.displayOutput();
end