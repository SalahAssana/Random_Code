% Image Filter
% Apply a simple image filter using convolution and pixel manipulation

% Import necessary libraries
import imutils
import numpy as np

% Define the kernel for the filter (a 3x3 matrix)
kernel = [[-1, -1, -1], [-1, 8, -1], [-1, -1, -1]]

% Load the image to be filtered
image = imutils.imread('input.jpg');

% Initialize an output array of the same size as the input image
output = np.zeros((image.shape[0], image.shape[1]));

% Apply the filter using convolution
for i in range(image.shape[0] - 2):
    for j in range(image.shape[1] - 2):
        pixel_sum = 0;
        for k in range(3):
            for l in range(3):
                if (i + k >= 0) and (j + l >= 0):
                    pixel_sum += image[i+k, j+l] * kernel[k, l];
        output[i+1, j+1] = pixel_sum;

% Save the filtered image
imutils.imwrite('output.jpg', output);

% Check if this script is being run directly
if __name__ == '__main__':
    % Run the filter on the input image
    main();