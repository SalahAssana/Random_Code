% Image Processing Filter
%
% Description: Applies filters such as blurring and thresholding to an image using matrix operations.

function filteredImage = applyFilter(image, filterType)
    % Apply filter to the input image
    %
    % Parameters:
    %   image - Input image (RGB or grayscale)
    %   filterType - Type of filter to apply ('blur' or 'threshold')

    if nargin ~= 2
        error('Invalid number of input arguments');
    end

    if ~strcmp(filterType, 'blur') && ~strcmp(filterType, 'threshold')
        error('Invalid filter type. Choose ''blur'' or ''threshold''.');
    end

    % Convert image to grayscale if it's RGB
    if size(image, 3) == 3
        image = rgb2gray(image);
    end

    % Apply blur filter
    if strcmp(filterType, 'blur')
        filteredImage = conv2(image, fspecial('average'), 'same');
    % Apply threshold filter
    elseif strcmp(filterType, 'threshold')
        thresholdValue = 127;  % Default threshold value
        thresholdedImage = image > thresholdValue;
        filteredImage = uint8(thresholdedImage * 255);
    end

end

% Test the function with a sample image
image = imread('cameraman.tif');
filteredImage = applyFilter(image, 'blur');

figure; imshow(image); title('Original Image');
figure; imshow(filteredImage); title('Filtered Image (Blurred)');

image = rgb2gray(imread('peppers.png'));
filteredImage = applyFilter(image, 'threshold');

figure; imshow(image); title('Original Image');
figure; imshow(filteredImage); title('Filtered Image (Thresholded)');