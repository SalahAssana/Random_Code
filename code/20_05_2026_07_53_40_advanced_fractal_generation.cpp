#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to generate fractal image
void generateFractal(int width, int height, vector<vector<int>>& pixels) {
    // Set seed for random number generation
    srand(time(0));

    // Initialize pixel values to 0 (black)
    fill(pixels.begin(), pixels.end(), vector<int>(width, 0));

    // Generate fractal image using Mandelbrot set algorithm
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double real = -2.5 + (x * 4) / width;
            double imag = 1.25 - (y * 3) / height;

            int maxIter = 255;
            for (int i = 0; i < maxIter && (real*real+imag*imag)<4; i++) {
                double tempReal = real*real - imag*imag;
                imag = 2*real*imag;
                real = tempReal;
            }

            // Color pixel based on the number of iterations
            int color = min(i, maxIter-1);
            pixels[y][x] = color;
        }
    }
}

int main() {
    // Set dimensions for fractal image
    int width = 800;
    int height = 600;

    // Initialize vector to store pixel values
    vector<vector<int>> pixels(height, vector<int>(width));

    // Generate and display fractal image
    generateFractal(width, height, pixels);

    // Print fractal image
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            cout << endl;
            if (pixels[y][x] > 10) {
                cout << "*";
            } else {
                cout << " ";
            }
        }
    }

    return 0;
}