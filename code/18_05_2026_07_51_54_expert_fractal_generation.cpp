#include <iostream>
#include <vector>
#include <cmath>

// Constants for image dimensions
const int WIDTH = 800;
const int HEIGHT = 800;

// Constants for fractal parameters
const double X_MIN = -2.0;
const double X_MAX = 1.0;
const double Y_MIN = -1.5;
const double Y_MAX = 1.5;
const double MAX_ITERATIONS = 256;

// Function to calculate the Mandelbrot set
bool isMandelbrot(double x, double y) {
    double zx = 0.0, zy = 0.0;
    int iterations = 0;
    
    while (iterations < MAX_ITERATIONS && (zx * zx + zy * zy <= 4.0)) {
        double newZx = zx * zx - zy * zy + x;
        double newZy = 2.0 * zx * zy + y;
        zx = newZx;
        zy = newZy;
        iterations++;
    }
    
    return iterations < MAX_ITERATIONS;
}

// Function to generate the Mandelbrot set image
void generateMandelbrot(const std::vector<std::vector<bool>>& mandelbrotSet, const char* filename) {
    int width = WIDTH;
    int height = HEIGHT;
    unsigned char *imageBuffer = new unsigned char[width * height * 3];
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double real = X_MIN + (X_MAX - X_MIN) * (x / (double)width);
            double imag = Y_MIN + (Y_MAX - Y_MIN) * (y / (double)height);
            
            if (!isMandelbrot(real, imag)) {
                imageBuffer[(y * width * 3) + x*3] = 255;
                imageBuffer[(y * width * 3) + x*3+1] = 0;
                imageBuffer[(y * width * 3) + x*3+2] = 0;
            } else {
                imageBuffer[(y * width * 3) + x*3] = 0;
                imageBuffer[(y * width * 3) + x*3+1] = 0;
                imageBuffer[(y * width * 3) + x*3+2] = 255;
            }
        }
    }
    
    // Save the generated image
    FILE *file = fopen(filename, "wb");
    if (file != NULL) {
        fwrite(imageBuffer, sizeof(unsigned char), width * height * 3, file);
        fclose(file);
    } else {
        std::cerr << "Failed to save the image." << std::endl;
    }
    
    delete[] imageBuffer;
}

int main() {
    // Generate the Mandelbrot set
    std::vector<std::vector<bool>> mandelbrotSet(WIDTH, std::vector<bool>(HEIGHT));
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double real = X_MIN + (X_MAX - X_MIN) * (x / (double)WIDTH);
            double imag = Y_MIN + (Y_MAX - Y_MIN) * (y / (double)HEIGHT);
            
            if (!isMandelbrot(real, imag)) {
                mandelbrotSet[y][x] = true;
            } else {
                mandelbrotSet[y][x] = false;
            }
        }
    }
    
    // Save the Mandelbrot set
    generateMandelbrot(mandelbrotSet, "mandelbrot.png");
    
    return 0;
}