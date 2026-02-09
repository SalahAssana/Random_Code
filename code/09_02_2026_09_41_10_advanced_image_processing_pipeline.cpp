#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_copy.h>

using namespace cv;
using namespace std;

class ImageProcessingPipeline {
public:
    Mat applyFilters(Mat input) {
        // Apply filters (Blur, Canny)
        Mat blurred = blur(input, Size(5, 5));
        Mat edges = Canny(blurred, 50, 150);
        return edges;
    }

    Mat detectEdges(Mat input) {
        // Detect edges using Laplacian of Gaussian
        Mat edges;
        LaplacianOfGaussian(input, edges);
        return edges;
    }

    Mat threshold(Mat input) {
        // Apply thresholding using Otsu's algorithm
        Mat thresh;
        threshold(input, thresh, 0, 255, THRESH_BINARY | THRESH_OTSU);
        return thresh;
    }

    void processImage(Mat& img) {
        // Main pipeline: apply filters, detect edges, and threshold
        Mat filtered = applyFilters(img);
        Mat edges = detectEdges(filtered);
        Mat threshed = threshold(edges);
        img = threshed;
    }
};

int main() {
    Mat input = imread("input.jpg");
    if (input.empty()) {
        cout << "Failed to load image." << endl;
        return -1;
    }

    ImageProcessingPipeline pipeline;
    pipeline.processImage(input);

    imwrite("output.jpg", input);
    return 0;
}