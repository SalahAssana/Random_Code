#include <opencv2/opencv.hpp>
#include <iostream>

// Class for filtering images using OpenCV
class ImageFilter {
public:
    // Constructor to initialize filter type and kernel size
    ImageFilter(int filterType, int kernelSize) : filterType(filterType), kernelSize(kernelSize) {}

    // Apply the filter to an image
    void apply(cv::Mat& img) {
        if (filterType == 0) { // Blur filter
            cv::GaussianBlur(img, img, cv::Size(kernelSize, kernelSize), 0);
        } else if (filterType == 1) { // Threshold filter
            cv::threshold(img, img, 127, 255, cv::THRESH_BINARY);
        }
    }

private:
    int filterType;
    int kernelSize;
};

// Class for processing images using OpenCV
class ImageProcessor {
public:
    // Constructor to initialize image and filters
    ImageProcessor(cv::Mat& img) : img(img), filters({}) {}

    // Add a filter to the pipeline
    void addFilter(ImageFilter* filter) { filters.push_back(filter); }

    // Process the image using all filters in the pipeline
    void process() {
        for (auto& filter : filters) {
            filter->apply(img);
        }
    }

private:
    cv::Mat& img;
    std::vector<ImageFilter*> filters;
};

int main() {
    // Load an example image
    cv::Mat img = cv::imread("image.jpg");

    // Create an image processor with the image and some filters
    ImageProcessor processor(img);
    processor.addFilter(new ImageFilter(0, 5)); // Blur filter with kernel size 5
    processor.addFilter(new ImageFilter(1, 3)); // Threshold filter with threshold 127

    // Process the image using all filters in the pipeline
    processor.process();

    // Display the processed image
    cv::imshow("Processed Image", img);
    cv::waitKey(0);

    return 0;
}