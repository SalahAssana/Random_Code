% Image Filter
% Apply different filters to an image, such as blurring or sharpening.

% Import necessary libraries
imtool;
filter_toolbox;

% Define the filter functions
function filtered_image = blur(image, radius)
    % Blur the image using a Gaussian filter
    filtered_image = imfilter(image, fspecial('gaussian', [radius radius], 0.1));
end

function filtered_image = sharpen(image, radius)
    % Sharpen the image using a Laplacian of Gaussian (LoG) filter
    log_filter = fspecial('log', [radius radius], 2);
    filtered_image = imfilter(image, log_filter) - imfilter(imfilter(image, log_filter), log_filter);
end

function filtered_image = edge_detect(image, threshold)
    % Detect edges in the image using a Canny filter
    gradient_x = fspecial('kaiser', [3 1], 10);
    gradient_y = fspecial('kaiser', [1 3], 10);
    grad_x = imfilter(image, gradient_x);
    grad_y = imfilter(image, gradient_y);
    grad_magnitude = sqrt(grad_x.^2 + grad_y.^2);
    filtered_image = (grad_magnitude > threshold) * 255;
end

% Load the test image
image = imread('test_image.jpg');

% Apply filters to the image
blurred_image = blur(image, 5);
sharpened_image = sharpen(image, 3);
edge_detected_image = edge_detect(image, 50);

% Display the filtered images
figure;
imshow(image);
title('Original Image');
figure;
imshow(blurred_image);
title('Blurred Image');
figure;
imshow(sharpened_image);
title('Sharpened Image');
figure;
imshow(edge_detected_image, []);
title('Edge Detected Image');
