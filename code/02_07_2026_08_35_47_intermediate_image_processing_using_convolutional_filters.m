% Image Processing using Convolutional Filters

% Define the convolutional filter (kernel)
filter = [0 1 0; 1 -4 1; 0 1 0];

function processedImage = convolve(image, filter)
    % Get the dimensions of the image and filter
    [rows, cols] = size(image);
    kernelRows = size(filter, 1);
    kernelCols = size(filter, 2);

    % Initialize the output image with zeros
    processedImage = zeros(rows + kernelRows - 1, cols + kernelCols - 1);

    % Iterate over each pixel in the original image
    for i = 1:rows
        for j = 1:cols
            % Extract the sub-image centered at the current pixel
            subImage = image(max(1, i - floor(kernelRows / 2)):min(rows, i + floor(kernelRows / 2)), 
                              max(1, j - floor(kernelCols / 2)):min(cols, j + floor(kernelCols / 2)));

            % Convolve the sub-image with the filter
            result = sum(sum(subImage .* filter));

            % Place the convolved value at the corresponding location in the output image
            processedImage(i + kernelRows / 2 - 1, j + kernelCols / 2 - 1) = result;
        end
    end
end

% Load an example image
image = imread('cameraman.tif');

% Convolve the image with the filter
processedImage = convolve(image, filter);

% Display the original and processed images
figure;
imshow(image);
title('Original Image');
figure;
imshow(processedImage);
title('Processed Image');