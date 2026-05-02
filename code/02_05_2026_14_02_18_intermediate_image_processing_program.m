% Image Processing Program
%
% Description: This program demonstrates various image processing techniques 
%              such as filtering, resizing, and cropping using MATLAB's image 
%              processing libraries.

% Import necessary libraries
import java.awt.image.BufferedImage;
import javax.swing.*;
import java.io.File;
import java.io.IOException;

% Define a function to apply filters to an image
function filteredImage = applyFilter(imagePath, filterName)
    % Read the image file
    image = imread(imagePath);
    
    % Apply the specified filter
    switch filterName
        case 'Blur'
            filteredImage = imfilter(image, fspecial('average'), 'replicate');
        case 'Sharpen'
            filteredImage = imfilter(image, fspecial('laplacian'), 'replicate');
        otherwise
            error('Invalid filter name');
    end
    
    % Display the filtered image
    imshow(filteredImage);
end

% Define a function to resize an image
function resizedImage = resizeImage(imagePath, newSize)
    % Read the image file
    image = imread(imagePath);
    
    % Resize the image using imresize()
    resizedImage = imresize(image, newSize);
    
    % Display the resized image
    imshow(resizedImage);
end

% Define a function to crop an image
function croppedImage = cropImage(imagePath, x, y, w, h)
    % Read the image file
    image = imread(imagePath);
    
    % Crop the image using imcrop()
    croppedImage = imcrop(image, [x y w h]);
    
    % Display the cropped image
    imshow(croppedImage);
end

% Define a main function to test the above functions
function main
    % Specify the image path and filter names
    imagePath = 'path_to_your_image.jpg';
    filters = {'Blur', 'Sharpen'};
    
    % Apply each filter to the image and display the results
    for i = 1:length(filters)
        applyFilter(imagePath, filters{i});
    end
    
    % Specify the new size for resizing
    newSize = [0.5 0.5];
    
    % Resize the image and display the result
    resizedImage = resizeImage(imagePath, newSize);
    imshow(resizedImage);
    
    % Specify the crop coordinates
    x = 100;
    y = 50;
    w = 200;
    h = 150;
    
    % Crop the image and display the result
    croppedImage = cropImage(imagePath, x, y, w, h);
    imshow(croppedImage);
end

% Run the main function when this script is executed
main();