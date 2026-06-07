% Advanced Image Processing Filter using CUDA
% Copyright 2023, Your Name

classdef ImageFilter < handle
    properties
        image
        filteredImage
    end
    
    methods
        function obj = ImageFilter(imagePath)
            % Load the image and get its dimensions
            img = imread(imagePath);
            [height, width, ~] = size(img);
            
            % Create a CUDA device
            cudaDevice = gpuDevice;
            
            % Define the filter kernel
            filterKernel = @(___, varargin) { ...
                'kernel', 'filterKernel', ...
                'input', img, ...
                'output', zeros(size(img)), ...
                'sharedMemorySize', 1024 * 8 };
            
            % Launch the kernel on the GPU
            output = filterKernel(height, width);
            
            % Download the filtered image from the GPU
            obj.image = gpuArray(img);
            obj.filteredImage = gather(output);
        end
        
        function displayResult(obj)
            % Display the original and filtered images
            figure;
            subplot(1, 2, 1);
            imshow(obj.image);
            title('Original Image');
            
            subplot(1, 2, 2);
            imshow(obj.filteredImage);
            title('Filtered Image');
        end
        
        function [filteredImage] = blur(image)
            % Define the blur filter kernel
            kernelSize = 5;
            filterKernel = zeros(kernelSize, kernelSize);
            filterKernel(2, 2) = 1 / (kernelSize^2);
            
            % Convolve the image with the filter kernel
            filteredImage = conv2(image, filterKernel, 'same');
        end
        
        function [filteredImage] = grayscale(image)
            % Convert the image to grayscale using a filter kernel
            filterKernel = [0.299, 0.587, 0.114; 0.299, 0.587, 0.114; 0.299, 0.587, 0.114];
            
            % Convolve the image with the filter kernel
            filteredImage = conv2(image, filterKernel, 'same');
        end
    end
    
end

% Define the CUDA filter kernel
function output = filterKernel(height, width)
    % Get the input and output images from the MATLAB workspace
    img = gpuArray.zeros([height, width, 3], 'like', im2double(gpuArray('inputImage')));
    output = gpuArray.zeros(size(img), 'like', img);
    
    % Apply the blur filter kernel
    for i = 1:height - 4
        for j = 1:width - 4
            pixel = img(i:i+4, j:j+4, :);
            filteredPixel = zeros(3, 1);
            for k = 1:3
                for l = 1:9
                    if l <= 5 && l >= 2
                        filteredPixel(k) = filteredPixel(k) + pixel(l, l, k);
                    end
                end
            end
            output(i:i+4, j:j+4, :) = filteredPixel;
        end
    end
    
    % Copy the filtered image back to the MATLAB workspace
    gpuArray.copy(output, 'outputImage');
end

% Test the filter class
if true
    imagePath = 'path_to_your_image.jpg';
    filter = ImageFilter(imagePath);
    
    % Apply the blur and grayscale filters
    blurredImage = filter.blur(filter.image);
    grayscaleImage = filter.grayscale(filter.image);
    
    % Display the results
    filter.displayResult();
end