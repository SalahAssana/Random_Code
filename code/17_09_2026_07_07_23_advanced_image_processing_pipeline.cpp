#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

// Define a class to represent an image processing filter
class Filter {
public:
    virtual cv::Mat applyFilter(const cv::Mat& input) = 0;
};

// Define a concrete implementation of a filter for blurring the image
class BlurFilter : public Filter {
public:
    cv::Mat applyFilter(const cv::Mat& input) override {
        cv::Mat output(input.size(), CV_8UC3);
        for (int i = 1; i < input.rows - 1; ++i) {
            for (int j = 1; j < input.cols - 1; ++j) {
                float blue = 0.0, green = 0.0, red = 0.0;
                for (int k = -1; k <= 1; ++k) {
                    for (int l = -1; l <= 1; ++l) {
                        cv::Vec3b pixel = input.at<cv::Vec3b>(i + k, j + l);
                        blue += pixel[0];
                        green += pixel[1];
                        red += pixel[2];
                    }
                }
                blue /= 9.0;
                green /= 9.0;
                red /= 9.0;
                output.at<cv::Vec3b>(i, j)[0] = static_cast<uchar>(blue);
                output.at<cv::Vec3b>(i, j)[1] = static_cast<uchar>(green);
                output.at<cv::Vec3b>(i, j)[2] = static_cast<uchar>(red);
            }
        }
        return output;
    }
};

// Define a concrete implementation of a filter for thresholding the image
class ThresholdFilter : public Filter {
public:
    cv::Mat applyFilter(const cv::Mat& input) override {
        cv::Mat output(input.size(), CV_8UC3);
        for (int i = 0; i < input.rows; ++i) {
            for (int j = 0; j < input.cols; ++j) {
                cv::Vec3b pixel = input.at<cv::Vec3b>(i, j);
                if (pixel[0] > 128 && pixel[1] > 128 && pixel[2] > 128) {
                    output.at<cv::Vec3b>(i, j)[0] = static_cast<uchar>(255);
                    output.at<cv::Vec3b>(i, j)[1] = static_cast<uchar>(255);
                    output.at<cv::Vec3b>(i, j)[2] = static_cast<uchar>(255);
                } else {
                    output.at<cv::Vec3b>(i, j)[0] = static_cast<uchar>(0);
                    output.at<cv::Vec3b>(i, j)[1] = static_cast<uchar>(0);
                    output.at<cv::Vec3b>(i, j)[2] = static_cast<uchar>(0);
                }
            }
        }
        return output;
    }
};

// Define a class to represent the image processing pipeline
class Pipeline {
public:
    cv::Mat process(const cv::Mat& input) {
        cv::Mat output = input.clone();
        for (int i = 0; i < filters_.size(); ++i) {
            Filter* filter = filters_[i];
            output = filter->applyFilter(output);
        }
        return output;
    }

private:
    std::vector<Filter*> filters_;
};

// Define the main function to demonstrate the image processing pipeline
int main() {
    // Load an image
    cv::Mat input = cv::imread("image.jpg");

    // Create a pipeline with multiple filters
    Pipeline pipeline;
    pipeline.filters_.push_back(new BlurFilter());
    pipeline.filters_.push_back(new ThresholdFilter());

    // Process the image using the pipeline
    cv::Mat output = pipeline.process(input);

    // Display the processed image
    cv::imshow("Output", output);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}