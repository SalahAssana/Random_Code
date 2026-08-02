% Define filter functions
function filtered_image = apply_filter(image, filter)
    % Get image dimensions
    [height, width] = size(image);
    
    % Initialize output image
    filtered_image = zeros(height, width);
    
    % Convolve the image with the filter
    for i = 1:height
        for j = 1:width
            sum = 0;
            for k = -size(filter, 2)/2:size(filter, 2)/2
                for l = -size(filter, 1)/2:size(filter, 1)/2
                    if i + k > 0 && i + k <= height && j + l > 0 && j + l <= width
                        sum = sum + image(i+k, j+l) * filter(k+size(filter, 2)/2+1, l+size(filter, 1)/2+1);
                    end
                end
            end
            filtered_image(i, j) = sum;
        end
    end
end

% Main script
image = imread('test_image.jpg'); % Load test image
filter = [0.25, 0.5, 0.25; 0.5, 1, 0.5; 0.25, 0.5, 0.25]; % Define filter

filtered_image = apply_filter(image, filter); % Apply filter to the image

% Display the filtered image
imshow(filtered_image);
