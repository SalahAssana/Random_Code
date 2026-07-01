% ADVANCED Image Processing Filter
% Design a program that applies various filters (e.g., blur, thresholding) to images using advanced algorithms and GPU acceleration.

classdef Filter < handle
    methods
        function obj = Filter(filterType)
            if nargin < 1
                filterType = 'blur';
            end
            
            switch filterType
                case 'blur'
                    obj.filterFcn = @applyBlur;
                case 'thresholding'
                    obj.filterFcn = @applyThresholding;
                otherwise
                    error('Invalid filter type');
            end
        end
        
        function filteredImage = apply(obj, image)
            if nargin < 2
                error('Input image is required');
            end
            
            % Use CUDA kernel to perform filtering on GPU
            imgLab = rgb2lab(image);
            labFilteredImage = zeros(size(imgLab));
            
            % Set up filter parameters
            filterSize = 5;
            sigma = 1.0;
            
            % Run the kernel
            [height, width] = size(imgLab(:,:,1));
            gridSize = ceil(height/filterSize) * ceil(width/filterSize);
            blockSize = 256;
            numBlocksX = ceil(height/filterSize);
            numBlocksY = ceil(width/filterSize);
            
            filteredImage = zeros(size(image));
            
            kernel @() {
                int2 idx = blockIdx.x * blockDim.x + threadIdx.x;
                int2 idy = blockIdx.y * blockDim.y + threadIdx.y;
                
                if (idx >= height || idy >= width)
                    return;
                float2 pixel = imgLab(idy, idx, :);
                float2 filteredPixel = 0.0f;
                
                for (int i = -filterSize; i <= filterSize; i++) {
                    for (int j = -filterSize; j <= filterSize; j++) {
                        int2 neighborIdx = idx + i;
                        int2 neighborIdy = idy + j;
                        
                        if (neighborIdx >= height || neighborIdy >= width)
                            continue;
                        
                        float2 neighborPixel = imgLab(neighborIdy, neighborIdx, :);
                        filteredPixel += exp(-((pixel.r - neighborPixel.r) * (pixel.r - neighborPixel.r) / (sigma * sigma)) ...
                                                + ((pixel.g - neighborPixel.g) * (pixel.g - neighborPixel.g) / (sigma * sigma)) ...
                                                + ((pixel.b - neighborPixel.b) * (pixel.b - neighborPixel.b) / (sigma * sigma)));
                    }
                }
                
                filteredPixel /= pow(2, 2 * filterSize);
                labFilteredImage(idy, idx, :) = pixel;
            } numBlocksX, numBlocksY, blockSize, blockSize;
            
            % Apply the filter
            for i = 1:height
                for j = 1 width
                    labFilteredImage(i, j, :) = obj.filterFcn(labFilteredImage(i, j, :));
                end
            end
            
            filteredImage = lab2rgb(labFilteredImage);
        end
        
        function pixel = applyBlur(pixel)
            % Simple blur filter (Gaussian blur)
            sigma = 1.0;
            pixel.r *= exp(-pow((pixel.r - 50), 2) / (sigma * sigma));
            pixel.g *= exp(-pow((pixel.g - 50), 2) / (sigma * sigma));
            pixel.b *= exp(-pow((pixel.b - 50), 2) / (sigma * sigma));
        end
        
        function pixel = applyThresholding(pixel)
            % Simple thresholding filter
            threshold = 50;
            if (pixel.r > threshold && pixel.g > threshold && pixel.b > threshold)
                pixel.r = 255;
                pixel.g = 255;
                pixel.b = 255;
            else
                pixel.r = 0;
                pixel.g = 0;
                pixel.b = 0;
            end
        end
    end
end

% Example usage
filterType = 'thresholding';
image = imread('image.jpg');
filter = Filter(filterType);
filteredImage = filter.apply(image);

figure; imshow(filteredImage); title('Filtered Image');

% Load and display the original image
figure; imshow(image); title('Original Image');