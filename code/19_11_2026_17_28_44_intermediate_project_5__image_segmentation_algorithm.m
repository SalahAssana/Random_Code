% Project 5: Image Segmentation Algorithm

function project5()
    % Load the image
    img = imread('image.jpg');
    
    % Convert the image to grayscale
    gray_img = rgb2gray(img);
    
    % Apply thresholding to separate objects from background
    thresholded_img = gray_img > 0.5;
    
    % Use edge detection (Canny edge detection) to enhance edges
    [edges_x, edges_y] = imgradientxy(thresholded_img, 'canny');
    
    % Apply non-maximum suppression to the edges
    edges = imnonmaxsup(thresholded_img, edges_x, edges_y);
    
    % Hysteresis thresholding to thin the edges
    [high_edges, low_edges] = imhmin(edges, 0.5, 1);
    segmented_img = high_edges | low_edges;
    
    % Display the original image and the segmented image
    figure;
    subplot(1,2,1);
    imshow(img);
    title('Original Image');
    subplot(1,2,2);
    imshow(segmented_img);
    title('Segmented Image');
end

project5();