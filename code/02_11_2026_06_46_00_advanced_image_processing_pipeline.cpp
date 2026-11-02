#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

class ImageProcessor {
public:
    Mat processImage(const Mat& image) {
        // Apply Gaussian Blur
        Mat blurred = Mat::zeros(image.size(), CV_8UC3);
        GaussianBlur(image, blurred, Size(5, 5), 0);

        // Threshold the image
        threshold(blurred, blurred, 127, 255, THRESH_BINARY);

        // Detect edges using Canny algorithm
        vector<vector<uchar>> grad_x, grad_y;
        Mat grad;
        gradient(blurred, grad_x, grad_y);
        Canny(grad_x, grad_y, 100, 200, grad);

        return grad;
    }

private:
    void gradient(const Mat& image, vector<vector<uchar>>& grad_x, vector<vector<uchar>>& grad_y) {
        int rows = image.rows;
        int cols = image.cols;

        grad_x.resize(rows);
        for (int i = 0; i < rows; ++i) {
            grad_x[i].resize(cols);
        }

        grad_y.resize(rows);
        for (int i = 0; i < rows; ++i) {
            grad_y[i].resize(cols);
        }

        for (int i = 1; i < rows - 1; ++i) {
            for (int j = 1; j < cols - 1; ++j) {
                int Gx = abs((image.at<uchar>(i, j + 1) - image.at<uchar>(i, j - 1)));
                int Gy = abs((image.at<uchar>(i + 1, j) - image.at<uchar>(i - 1, j)));

                grad_x[i][j] = Gx;
                grad_y[i][j] = Gy;
            }
        }
    }
};

int main() {
    ImageProcessor processor;

    // Load an example image
    Mat image = imread("image.jpg", IMREAD_COLOR);

    if (image.empty()) {
        cout << "Error: Could not load the image." << endl;
        return -1;
    }

    // Process the image
    Mat processed = processor.processImage(image);

    // Display the processed image
    imshow("Processed Image", processed);
    waitKey(0);
    destroyAllWindows();

    return 0;
}