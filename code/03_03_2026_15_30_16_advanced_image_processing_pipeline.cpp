#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Filter {
public:
    virtual Mat apply(Mat image) = 0;
};

class BrightnessFilter : public Filter {
public:
    Mat apply(Mat image) override {
        Mat result;
        vector<double> brightnessValues = {1.5, 2.0, 3.0};
        for (double value : brightnessValues) {
            Mat brightenedImage;
            convertScaleAbs(image, brightenedImage, value);
            if (!result.empty()) {
                vconcat(result, brightenedImage, result);
            } else {
                result = brightenedImage;
            }
        }
        return result;
    }
};

class SharpenFilter : public Filter {
public:
    Mat apply(Mat image) override {
        Mat result;
        GaussianBlur(image, image, Size(0, 0), 2.5);
        Laplacian(image, image, CV_8U, 1);
        addWeighted(image, -1, image, 1, 0, result);
        return result;
    }
};

class ImageProcessor {
public:
    vector<Mat> processImage(vector<Filter*> filters, Mat image) {
        vector<Mat> results;
        for (Filter* filter : filters) {
            Mat filteredImage = filter->apply(image);
            results.push_back(filteredImage);
        }
        return results;
    }
};

int main() {
    // Load the input image
    Mat image = imread("input.jpg");

    // Create a list of filters to apply
    vector<Filter*> filters;
    filters.push_back(new BrightnessFilter());
    filters.push_back(new SharpenFilter());

    // Process the image with the filters
    ImageProcessor processor;
    vector<Mat> results = processor.processImage(filters, image);

    // Display the processed images
    for (int i = 0; i < results.size(); i++) {
        imshow("Filtered Image " + to_string(i), results[i]);
    }

    waitKey(0);
    return 0;
}
