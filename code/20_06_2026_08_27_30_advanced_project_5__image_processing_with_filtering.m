% Project 5: Image Processing with Filtering
% Advanced complexity project using matrix operations and convolution algorithms

function filteredImage = applyFilters(image, filters)
    % Apply filters to an image using matrix operations and convolution algorithms
    %   filteredImage = applyFilters(image, filters)
    %   where:
    %       image: input image (grayscale or RGB)
    %       filters: cell array of filter matrices (e.g., blur, sharpen)

    % Convert image to grayscale if necessary
    if size(image, 3) == 3, % RGB image
        grayImage = rgb2gray(image);
    else, % Grayscale image
        grayImage = image;
    end

    % Apply filters to the grayscale image
    filteredGrayImage = zeros(size(grayImage));
    for i = 1:length(filters)
        filterMatrix = filters{i};
        [height, width] = size(filterMatrix);
        paddedImage = padarray(grayImage, [height/2 height/2], 'symmetric');
        filteredRow = conv2(paddedImage, filterMatrix, 'same');
        filteredGrayImage = filteredGrayImage + filteredRow;
    end

    % Convert the filtered grayscale image back to RGB if necessary
    if size(image, 3) == 3
        filteredImage = cat(3, filteredGrayImage, filteredGrayImage, filteredGrayImage);
    else
        filteredImage = filteredGrayImage;
    end
end

function filterMatrix = generateBlurFilter()
    % Generate a blur filter matrix (5x5)
    filterMatrix = [1/9 1/9 1/9 1/9 1/9; ...
                    1/9 1/3 0.2 1/3 1/9; ...
                    1/9 0.2 1/3 0.2 1/9; ...
                    1/9 1/3 0.2 1/3 1/9; ...
                    1/9 1/9 1/9 1/9 1/9];
end

function filterMatrix = generateSharpenFilter()
    % Generate a sharpen filter matrix (5x5)
    filterMatrix = [-1 -1 -1 -1 -1; ...
                     -1 2 0 2 -1; ...
                     -1 0 9 0 -1; ...
                     -1 2 0 2 -1; ...
                     -1 -1 -1 -1 -1];
end

% Example usage
image = imread('sample.jpg');
blurFilter = generateBlurFilter();
sharpenFilter = generateSharpenFilter();

filteredImage = applyFilters(image, {blurFilter});
figure; imshow(filteredImage);

filteredImage = applyFilters(image, {sharpenFilter});
figure; imshow(filteredImage);