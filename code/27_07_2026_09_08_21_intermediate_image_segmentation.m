% Image Segmentation using Thresholding and Edge Detection Techniques
%
% This script demonstrates an image segmentation algorithm that uses thresholding
% and edge detection techniques to separate objects from the background.

function segImage = imageSegmentation(imagePath)
    % Load the input image
    img = imread(imagePath);

    % Convert the image to grayscale
    grayImg = rgb2gray(img);

    % Apply thresholding to segment out the foreground (objects) from the background
    threshVal = 0.5;  % Threshold value (0-1)
    thresImg = imbinarize(grayImg, threshVal);

    % Perform edge detection using Canny edge detection algorithm
    cannyThresh1 = 0.5;  % First threshold for Canny edge detection
    cannyThresh2 = 1;     % Second threshold for Canny edge detection
    [edgMap,~] = edge(thresImg, 'canny', cannyThresh1, cannyThresh2);

    % Visualize the segmented image (optional)
    if nargin > 0
        figure;
        subplot(1,2,1);
        imshow(img);
        title('Original Image');
        subplot(1,2,2);
        montage({thresImg, edgMap});
        title('Segmented Image and Edges');
    end

    % Return the segmented image
    segImage = thresImg;
end

% Test the function with a sample image
testImagePath = 'path_to_your_image.jpg';  % Replace with your image path
seggedImg = imageSegmentation(testImagePath);
```
