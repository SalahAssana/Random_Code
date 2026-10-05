#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class ImageSegmentation {
public:
    Mat edgeMap;
    Mat thresholdedMap;
    Mat segmentedImage;

    void detectEdges(Mat image) {
        // Canny Edge Detection
        vector<vector<int>> gradX, gradY;
        int apertureSize = 3;
        double lowThreshold = 50;
        double highThreshold = 150;
        Canny(image, edgeMap, lowThreshold, highThreshold);
    }

    void threshold(Mat image) {
        // Thresholding
        Mat thresh;
        threshold(edgeMap, thresh, 0, 255, THRESH_BINARY_INV | CV_THRESH_OTSU);
        thresholdedMap = thresh;
    }

    void morphologicalOperations(Mat image) {
        // Morphological Operations (Erosion and Dilation)
        Mat erosion, dilation;
        int iterations = 2;
        Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
        erode(thresholdedMap, erosion, kernel);
        dilate(erosion, dilation, kernel);
        segmentedImage = dilation;
    }

    void displayResults() {
        // Display the edge map and segmented image
        imshow("Edge Map", edgeMap);
        imshow("Segmented Image", segmentedImage);
        waitKey(0);
        destroyAllWindows();
    }

    int main(int argc, char** argv) {
        // Load the input image
        Mat image = imread("input.jpg");

        if (image.empty()) {
            cout << "Error: Unable to load the input image." << endl;
            return -1;
        }

        detectEdges(image);
        threshold(image);
        morphologicalOperations(image);
        displayResults();

        return 0;
    }
```
