#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class WaveletDenoiser {
public:
    WaveletDenoiser(const Mat& img) : img_(img) {}

    void denoise(int level, double threshold) {
        // Apply wavelet transform
        Mat coeffs;
        wavedec(img_, coeffs, 1, 3, true);

        // Threshold the coefficients
        vector<double> threshCoeffs(coeffs.begin(), coeffs.end());
        for (auto& coeff : threshCoeffs) {
            if (abs(coeff) > threshold) {
                coeff = 0;
            }
        }

        // Apply inverse wavelet transform
        Mat denoisedImg;
        imwriteec(coeffs, denoisedImg);

        // Convert the coefficients back to image data type
        vector<uchar> pixData(denoisedImg.begin(), denoisedImg.end());
        img_.convertTo(img_, -1);
    }

private:
    const Mat& img_;
};

int main() {
    // Load the input image
    Mat img = imread("input.jpg");

    if (img.empty()) {
        cerr << "Error: Unable to load input image." << endl;
        return 1;
    }

    // Create a WaveletDenoiser object and denoise the image
    WaveletDenoiser denoiser(img);
    denoiser.denoise(3, 0.5);

    // Save the denoised image
    imwrite("denoised.jpg", img);

    return 0;
}