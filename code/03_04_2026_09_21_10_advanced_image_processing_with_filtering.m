% Image Processing with Filtering
% ADVANCED-level program using OpenCV
% Single file implementation

% Import necessary libraries
import java.awt.*;
import java.io.*;

% Define class for image processing
class ImageProcessor {
    % Constructor
    public function ImageProcessor()
        this.filter = "blur";
    end

    % Method to apply filter
    public function processImage(image, filter)
        switch (filter) {
            case "blur"
                this.applyBlurFilter(image);
                break;
            case "sharpen"
                this.applySharpenFilter(image);
                break;
            case "edge detection"
                this.applyEdgeDetectionFilter(image);
                break;
            default
                disp("Invalid filter. Please choose from 'blur', 'sharpen', or 'edge detection'.");
        end
    end

    % Method to apply blur filter
    private function applyBlurFilter(image)
        % Convert image to grayscale
        grayImage = rgb2gray(image);

        % Apply Gaussian blur
        blurredImage = imgfilter(grayImage, "Gaussian");

        % Display result
        imshow(blurredImage);
    end

    % Method to apply sharpen filter
    private function applySharpenFilter(image)
        % Convert image to grayscale
        grayImage = rgb2gray(image);

        % Apply unsharp masking (sharpening)
        sharpenedImage = imgfilter(grayImage, "Unsharp");

        % Display result
        imshow(sharpenedImage);
    end

    % Method to apply edge detection filter
    private function applyEdgeDetectionFilter(image)
        % Convert image to grayscale
        grayImage = rgb2gray(image);

        % Apply Canny edge detection
        edges = canny(grayImage, 0.5, 3);

        % Display result
        imshow(edges);
    end

    % Helper method for filter application
    private function imgfilter(image, filterType)
        switch (filterType) {
            case "Gaussian"
                sigma = 1;
                blurredImage = fspecial("gaussian", [sigma, sigma]);
                filteredImage = imfilter(image, blurredImage, 'replicate');
                break;
            case "Unsharp"
                amount = 2;
                threshold = 0.5;
                radius = 1;
                sharpenedImage = unsharp(image, amount, threshold, radius);
                break;
            default
                disp("Invalid filter type.");
        end

        % Return filtered image
        filteredImage
    end

    % Helper method for unsharp masking (sharpening)
    private function unsharp(image, amount, threshold, radius)
        k = fspecial("unsharp", [amount, threshold, radius]);
        sharpenedImage = imfilter(image, k, 'replicate');
        sharpenedImage
    end
}

% Create an instance of the ImageProcessor class and process an image
processor = ImageProcessor();
image = imread('example.jpg');
processor.processImage(image, "blur");
```
