% Define the filter function to blur an image
function filtered_image = apply_blur(image)
    % Calculate the filter size (3x3 for this example)
    filter_size = 3;
    
    % Initialize the output image with the same size as the input image
    [height, width, ~] = size(image);
    filtered_image = zeros(height, width, 3);
    
    % Iterate over each pixel in the image
    for i = 1:filter_size
        for j = 1:filter_size
            % Calculate the offset from the current pixel
            offset_i = (i - floor(filter_size/2));
            offset_j = (j - floor(filter_size/2));
            
            % Iterate over each neighboring pixel in the filter window
            for k = -floor(filter_size/2):floor(filter_size/2)
                for l = -floor(filter_size/2):floor(filter_size/2)
                    % Calculate the offset from the current pixel to the neighboring pixel
                    neighbor_i = i + k;
                    neighbor_j = j + l;
                    
                    % Check if the neighboring pixel is within the image boundaries
                    if 1 <= neighbor_i && neighbor_i <= height && 1 <= neighbor_j && neighbor_j <= width
                        % Add the weighted value of the neighboring pixel to the current pixel
                        filtered_image(i, j, :) = filtered_image(i, j, :) + image(neighbor_i + offset_i, neighbor_j + offset_j, :);
                    end
                end
            end
        end
    end
    
    % Normalize the pixel values to ensure they're within the valid range [0 255]
    max_value = max(max(filtered_image));
    min_value = min(min(filtered_image));
    normalized_max = max([max_value, 255]);
    normalized_min = min([min_value, 0]);
    
    % Scale and shift the pixel values
    for i = 1:height
        for j = 1;width
            filtered_image(i, j, :) = (filtered_image(i, j, :) - normalized_min) * 255 / (normalized_max - normalized_min);
        end
    end
end

% Load an example image
image = imread('input.png');

% Apply the blur filter to the image
filtered_image = apply_blur(image);

% Display the original and filtered images side-by-side
figure;
subplot(1, 2, 1); imshow(image); title('Original Image');
subplot(1, 2, 2); imshow(filtered_image); title('Filtered Image');
