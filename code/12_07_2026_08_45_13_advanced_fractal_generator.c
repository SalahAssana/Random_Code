#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure to represent a complex number
typedef struct {
    double real;
    double imag;
} Complex;

// Function to add two complex numbers
Complex add_complex(Complex a, Complex b) {
    Complex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return result;
}

// Function to multiply two complex numbers
Complex multiply_complex(Complex a, Complex b) {
    Complex result;
    result.real = a.real * b.real - a.imag * b.imag;
    result.imag = a.real * b.imag + a.imag * b.real;
    return result;
}

// Function to generate the Mandelbrot set
void mandelbrot(int width, int height, FILE* output) {
    Complex c, z;
    double r, i;
    int x, y;

    // Initialize color palette
    const int num_colors = 256;
    unsigned char color_palette[num_colors][3];
    for (int i = 0; i < num_colors; i++) {
        color_palette[i][0] = (unsigned char)(i * 255 / num_colors);
        color_palette[i][1] = (unsigned char)(i * 255 / num_colors);
        color_palette[i][2] = (unsigned char)(i * 255 / num_colors);
    }

    // Generate the Mandelbrot set
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            c.real = -2.5 + (x * 4.0 / width) - 1.0;
            c.imag = -1.25 + (y * 2.5 / height);
            z.real = c.real;
            z.imag = c.imag;

            int iter = 0;
            while ((z.real * z.real + z.imag * z.imag < 4.0) && (iter < 255)) {
                z = multiply_complex(z, add_complex(c, z));
                iter++;
            }

            // Determine the color of the pixel based on the iteration count
            if (iter == 255) {
                fwrite(&color_palette[0], 1, 3, output);
            } else {
                int color_index = iter;
                fwrite(&color_palette[color_index][0], 1, 1, output);
                fwrite(&color_palette[color_index][1], 1, 1, output);
                fwrite(&color_palette[color_index][2], 1, 1, output);
            }
        }
    }
}

int main() {
    // Open the output file
    FILE* output = fopen("mandelbrot.ppm", "wb");

    // Write the PPM header
    fprintf(output, "P3\n");
    fprintf(output, "%d %d\n", 800, 600);
    fprintf(output, "255\n");

    // Generate and write the Mandelbrot set
    mandelbrot(800, 600, output);

    // Close the output file
    fclose(output);

    return 0;
}