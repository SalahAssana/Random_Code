#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>

// Function to apply Gaussian filter to an image
void applyGaussianFilter(cv::Mat& image) {
    cv::Mat blurred;
    cv::GaussianBlur(image, blurred, cv::Size(0, 0), 1.5);
    image = blurred;
}

// Function to apply Sobel edge detection filter to an image
void applySobelEdgeDetectionFilter(cv::Mat& image) {
    cv::Mat grad_x, grad_y;
    cv::Sobel(image, grad_x, cv::CV_8U, 1, 0);
    cv::Sobel(image, grad_y, cv::CV_8U, 0, 1);

    // Combine the gradient images
    cv::Mat grad;
    cv::merge(grad_x, grad_y, grad);

    image = grad;
}

// Function to apply Laplacian filter to an image
void applyLaplacianFilter(cv::Mat& image) {
    cv::Mat laplacian;
    cv::Laplacian(image, laplacian);
    image = laplacian;
}

// Function to apply Median filter to an image
void applyMedianFilter(cv::Mat& image) {
    cv::Mat filtered;
    cv::medianBlur(image, filtered, 3);
    image = filtered;
}

int main() {
    // Load the image using OpenCV
    cv::Mat originalImage = cv::imread("image.jpg", cv::IMREAD_COLOR);

    // Apply Gaussian filter to the image
    applyGaussianFilter(originalImage);

    // Save the processed image
    cv::imwrite("gaussian_filtered_image.jpg", originalImage);

    // Load the image using OpenCV
    cv::Mat edgeDetectionImage = cv::imread("image.jpg", cv::IMREAD_COLOR);

    // Apply Sobel edge detection filter to the image
    applySobelEdgeDetectionFilter(edgeDetectionImage);

    // Save the processed image
    cv::imwrite("sobel_edge_detected_image.jpg", edgeDetectionImage);

    // Load the image using OpenCV
    cv::Mat laplacianImage = cv::imread("image.jpg", cv::IMREAD_COLOR);

    // Apply Laplacian filter to the image
    applyLaplacianFilter(laplacianImage);

    // Save the processed image
    cv::imwrite("laplacian_filtered_image.jpg", laplacianImage);

    // Load the image using OpenCV
    cv::Mat medianFilteredImage = cv::imread("image.jpg", cv::IMREAD_COLOR);

    // Apply Median filter to the image
    applyMedianFilter(medianFilteredImage);

    // Save the processed image
    cv::imwrite("median_filtered_image.jpg", medianFilteredImage);

    return 0;
}