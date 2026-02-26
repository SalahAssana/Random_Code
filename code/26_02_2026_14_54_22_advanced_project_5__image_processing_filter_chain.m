% Project 5: Image Processing Filter Chain
%
% Copyright (C) 2022 Your Name
%
% This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or any later version.
%

function filter_chain_example

    % Load test image
    img = imread('test_image.jpg');
    img = rgb2gray(img);

    % Filter chain: Blur -> Threshold -> Edge Detection
    blurred_img = blur_filter(img);
    thresholded_img = threshold(blurred_img, 0.5);
    edge_detected_img = canny_edge_detection(thresholded_img);

    % Display the filter chain results
    subplot(2,2,1); imshow(img); title('Original Image');
    subplot(2,2,2); imshow(blurred_img); title('Blurred Image');
    subplot(2,2,3); imshow(thresholded_img); title('Thresholded Image');
    subplot(2,2,4); imshow(edge_detected_img); title('Edge Detected Image');

end

% Blur Filter
function blurred_img = blur_filter(img)
    % Apply Gaussian filter with 5x5 kernel and std deviation of 1.0
    kernel = fspecial('gaussian', [5 5], 1);
    blurred_img = imfilter(img, kernel, 'replicate');
end

% Threshold Function
function thresholded_img = threshold(img, threshold_value)
    % Apply thresholding to the image using the given threshold value
    thresholded_img = img > threshold_value;
end

% Canny Edge Detection Function
function edge_detected_img = canny_edge_detection(img)
    % Apply Canny edge detection algorithm
    [gx, gy] = imgradient(img);
    gxy = sqrt(gx.^2 + gy.^2);
    edges = gxy > 0.5;
    edge_detected_img = edges;
end
