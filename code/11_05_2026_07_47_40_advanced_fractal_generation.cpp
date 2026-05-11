#include <iostream>
#include <cmath>
#include <vector>
#include <complex>
#include <algorithm>

using namespace std;

// Function to calculate the absolute value of a complex number
complex<double> abs(complex<double> z) {
    return sqrt(pow(z.real(), 2) + pow(z.imag(), 2));
}

// Class to represent a point in the complex plane
class Point {
public:
    double x, y;
};

// Function to generate the Mandelbrot set
vector<vector<int>> mandelbrot(int width, int height, double xmin, double xmax, double ymin, double ymax) {
    vector<vector<int>> image(width, vector<int>(height));
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            double cReal = xmin + (xmax - xmin) * i / width;
            double cImag = ymin + (ymax - ymin) * j / height;
            complex<double> z(0, 0), c(cReal, cImag);
            int maxIter = 255;
            for (int k = 0; k < maxIter && abs(z) <= 2.0; ++k) {
                z = z*z + c;
            }
            image[i][j] = k;
        }
    }
    return image;
}

// Function to generate the Julia set
vector<vector<int>> julia(int width, int height, double xmin, double xmax, double ymin, double ymax, complex<double> c) {
    vector<vector<int>> image(width, vector<vector<int>>(height));
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            double x = xmin + (xmax - xmin) * i / width;
            double y = ymin + (ymax - ymin) * j / height;
            complex<double> z(x, y), c2(c.real(), c.imag());
            int maxIter = 255;
            for (int k = 0; k < maxIter && abs(z) <= 2.0; ++k) {
                z = z*z + c2;
            }
            image[i][j] = k;
        }
    }
    return image;
}

// Function to display the generated fractal
void displayFractal(const vector<vector<int>>& image, const string& title) {
    for (int i = 0; i < image.size(); ++i) {
        for (int j = 0; j < image[0].size(); ++j) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // Generate the Mandelbrot set
    vector<vector<int>> mandelbrotImage = mandelbrot(800, 800, -2.5, 1.0, -1.5, 1.5);
    displayFractal(mandelbrotImage, "Mandelbrot Set");

    // Generate the Julia set
    complex<double> c(0.285, 0.01); // Choose a value for 'c'
    vector<vector<int>> juliaImage = julia(800, 800, -2.5, 1.0, -1.5, 1.5, c);
    displayFractal(juliaImage, "Julia Set");

    return 0;
}