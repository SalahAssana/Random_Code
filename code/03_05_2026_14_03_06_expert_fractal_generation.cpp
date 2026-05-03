#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <chrono>
#include <thread>

// Fractal generation constants
const int MAX_ITERATIONS = 1000;
const double ESCAPE_RADIUS_SQ = 4.0;

// Mandelbrot set fractal generator
void generateMandelbrot(const std::complex<double>& center, const double scale, 
                         std::vector<std::vector<char>>& image) {
    for (int y = 0; y < image.size(); ++y) {
        for (int x = 0; x < image[y].size(); ++x) {
            double real = (x + 0.5) * scale - center.real();
            double imag = (y + 0.5) * scale - center.imag();

            std::complex<double> z(0, 0);
            int iterations = 0;
            while ((z.real() * z.real() + z.imag() * z.imag()) < ESCAPE_RADIUS_SQ && 
                   iterations < MAX_ITERATIONS) {
                z = z*z + complex<double>(real, imag);
                ++iterations;
            }

            if (iterations == MAX_ITERATIONS) {
                image[y][x] = ' ';  // Set pixel to black for escaped points
            } else {
                int brightness = 255 - static_cast<int>(iterations * 0.5); 
                image[y][x] = static_cast<char>(brightness);
            }
        }
    }
}

int main() {
    const std::complex<double> center(0, 0);
    double scale = 3.0;

    int width = 800;
    int height = 800;

    std::vector<std::vector<char>> image(height, std::vector<char>(width));

    auto start = std::chrono::high_resolution_clock::now();
    
    generateMandelbrot(center, scale, image);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Fractal generation took: " << duration.count() << " microseconds." << std::endl;

    return 0;
}