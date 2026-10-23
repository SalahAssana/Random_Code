#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Class to represent a 2D image
class Image {
public:
    int width;
    int height;
    vector<vector<double>> data; // Gray scale values (0-1)

    // Constructor to initialize the image
    Image(int w, int h) : width(w), height(h) {}

    // Function to print the image
    void print() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                cout << (int)(data[i][j] * 255) << " ";
            }
            cout << endl;
        }
    }
};

// Class to represent a wavelet coefficient
class WaveletCoefficient {
public:
    double value;
    int orientation;
    int position;

    // Constructor to initialize the wavelet coefficient
    WaveletCoefficient(double v, int o, int p) : value(v), orientation(o), position(p) {}
};

// Function to apply discrete wavelet transform (DWT)
vector<vector<WaveletCoefficient>> dwt(Image& image) {
    vector<vector<WaveletCoefficient>> coefficients;
    for (int i = 0; i < image.height; ++i) {
        vector<WaveletCoefficient> row;
        for (int j = 0; j < image.width; ++j) {
            double value = 0;
            if (i > 0 && j > 0) {
                // Haar wavelet filter
                value += (image.data[i-1][j-1] + image.data[i-1][j+1] - image.data[i+1][j-1] - image.data[i+1][j+1]) / 4;
            }
            if (i > 0) {
                value += (image.data[i-1][j]) * (1 - sqrt(2.0));
            }
            row.emplace_back(value, 0, i);
        }
        coefficients.emplace_back(row);
    }
    return coefficients;
}

// Function to apply inverse discrete wavelet transform (IDWT)
Image idwt(vector<vector<WaveletCoefficient>>& coefficients) {
    Image image(coefficients.size(), coefficients[0].size());
    for (int i = 0; i < image.height; ++i) {
        for (int j = 0; j < image.width; ++j) {
            double value = 0;
            if (i > 0 && j > 0) {
                // Haar wavelet filter
                value += coefficients[i-1][j-1].value + coefficients[i-1][j+1].value - coefficients[i+1][j-1].value - coefficients[i+1][j+1].value;
            }
            if (i > 0) {
                value += coefficients[i-1][j].value * sqrt(2.0);
            }
            image.data[i][j] = clamp(value, 0.0, 1.0);
        }
    }
    return image;
}

// Function to apply thresholding
vector<vector<WaveletCoefficient>> threshold(vector<vector<WaveletCoefficient>>& coefficients) {
    vector<vector<WaveletCoefficient>> result;
    for (int i = 0; i < coefficients.size(); ++i) {
        vector<WaveletCoefficient> row;
        for (int j = 0; j < coefficients[0].size(); ++j) {
            if (coefficients[i][j].value > 0.5) { // Thresholding
                row.emplace_back(coefficients[i][j].value, coefficients[i][j].orientation, coefficients[i][j].position);
            } else {
                row.emplace_back(0.0, -1, -1); // Zero out the coefficient
            }
        }
        result.emplace_back(row);
    }
    return result;
}

// Function to reconstruct the denoised image from wavelet coefficients
Image denoise(Image& original, vector<vector<WaveletCoefficient>>& coefficients) {
    Image denoised(original.width, original.height);
    for (int i = 0; i < original.height; ++i) {
        for (int j = 0; j < original.width; ++j) {
            double value = 0;
            if (coefficients[i][j].value > 0.5) { // Thresholding
                value += coefficients[i][j].value;
            }
            denoised.data[i][j] = clamp(value, 0.0, 1.0);
        }
    }
    return denoised;
}

// Function to clamp the value between 0 and 1
double clamp(double value, double min, double max) {
    if (value < min)
        return min;
    else if (value > max)
        return max;
    return value;
}

int main() {
    Image original(512, 512);
    for (int i = 0; i < original.height; ++i) {
        for (int j = 0; j < original.width; ++j) {
            original.data[i][j] = static_cast<double>(rand()) / RAND_MAX;
        }
    }

    vector<vector<WaveletCoefficient>> coefficients = dwt(original);
    coefficients = threshold(coefficients);

    Image denoised = idwt(coefficients);

    denoised.print();

    return 0;
}