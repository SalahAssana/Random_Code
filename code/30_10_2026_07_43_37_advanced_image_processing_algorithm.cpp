#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class Filter {
public:
    virtual Mat apply(Mat image) = 0;
};

class MeanFilter : public Filter {
public:
    Mat apply(Mat image) override {
        int kernelSize = 5; // Size of the mean filter
        Mat result;
        blur(image, result, Size(kernelSize, kernelSize));
        return result;
    }
};

class MedianFilter : public Filter {
public:
    Mat apply(Mat image) override {
        int kernelSize = 3; // Size of the median filter
        Mat result;
        medianBlur(image, result, kernelSize);
        return result;
    }
};

class SharpenFilter : public Filter {
public:
    Mat apply(Mat image) override {
        int amount = 2; // Amount of sharpening
        Mat result;
        vector<vector<float>> kernel = {{0, -1, 0}, {-1, amount + 5, -1}, {0, -1, 0}};
        filter2D(image, result, image.type(), Mat(kernel));
        return result;
    }
};

class ImageProcessor {
public:
    void processImage(Mat image) {
        // Apply filters in sequence
        Filter* meanFilter = new MeanFilter();
        Filter* medianFilter = new MedianFilter();
        Filter* sharpenFilter = new SharpenFilter();

        image = meanFilter->apply(image);
        image = medianFilter->apply(image);
        image = sharpenFilter->apply(image);

        // Display the processed image
        imshow("Processed Image", image);
    }
};

int main() {
    // Load an example image
    Mat image = imread("example.jpg");

    if (image.empty()) {
        cout << "Error: Could not load the image." << endl;
        return -1;
    }

    // Create an instance of the ImageProcessor class
    ImageProcessor processor;

    // Process the image
    processor.processImage(image);

    waitKey(0);
    return 0;
}