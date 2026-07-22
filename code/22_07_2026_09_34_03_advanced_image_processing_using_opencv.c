#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// Class for image processing operations
class ImageProcessor {
public:
    // Constructor to initialize OpenCV
    ImageProcessor() {
        cv::initModule_nonfree();
    }

    // Method to apply filters to an image
    void applyFilters(cv::Mat& input, cv::Mat& output) {
        // Gaussian blur filter
        cv::GaussianBlur(input, output, cv::Size(5, 5), 0);

        // Median blur filter
        cv::medianBlur(input, output, 3);
    }

    // Method to apply thresholding to an image
    void applyThresholding(cv::Mat& input, cv::Mat& output) {
        // Convert the image to grayscale
        cv::cvtColor(input, output, cv::COLOR_BGR2GRAY);

        // Apply Otsu's thresholding algorithm
        cv::threshold(output, output, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);
    }

    // Method to apply edge detection using Canny algorithm
    void applyEdgeDetection(cv::Mat& input, cv::Mat& output) {
        // Convert the image to grayscale
        cv::cvtColor(input, output, cv::COLOR_BGR2GRAY);

        // Apply Gaussian blur for better edge detection
        cv::GaussianBlur(output, output, cv::Size(5, 5), 0);

        // Apply Canny edge detection algorithm
        cv::Canny(output, output, 100, 200);
    }
};

int main() {
    // Load the input image
    cv::Mat input = cv::imread("input.png");

    // Check if the image is loaded correctly
    if (input.empty()) {
        std::cerr << "Error: Unable to load the input image." << std::endl;
        return -1;
    }

    // Create an instance of the ImageProcessor class
    ImageProcessor processor;

    // Create output matrices for filters, thresholding, and edge detection
    cv::Mat filterOutput, thresholdOutput, edgeDetectionOutput;

    // Apply filters to the input image
    processor.applyFilters(input, filterOutput);

    // Save the filtered output
    cv::imwrite("filtered.png", filterOutput);

    // Apply thresholding to the input image
    processor.applyThresholding(input, thresholdOutput);

    // Save the thresholded output
    cv::imwrite("thresholded.png", thresholdOutput);

    // Apply edge detection using Canny algorithm
    processor.applyEdgeDetection(input, edgeDetectionOutput);

    // Save the edge detected output
    cv::imwrite("edgeDetected.png", edgeDetectionOutput);

    return 0;
}