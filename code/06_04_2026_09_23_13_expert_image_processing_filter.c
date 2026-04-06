#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Define constants for image processing filters
#define FILTER_SIZE 3
#define IMG_WIDTH 512
#define IMG_HEIGHT 512
#define PIXELS_PER_BYTE 4

// Structure to represent an RGB pixel
typedef struct {
    unsigned char r, g, b;
} Pixel;

// Function to apply a filter to an image
void applyFilter(Pixel* img, int width, int height) {
    // Initialize the output image with zeros
    Pixel* out = (Pixel*)malloc(width * height * sizeof(Pixel));
    memset(out, 0, width * height * sizeof(Pixel));

    // Apply the filter to each pixel in the image
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Pixel p = img[y * width + x];
            int sumR = 0, sumG = 0, sumB = 0;
            for (int fy = -1; fy <= 1; fy++) {
                for (int fx = -1; fx <= 1; fx++) {
                    Pixel neighbor = img[(y + fy) * width + x + fx];
                    sumR += neighbor.r;
                    sumG += neighbor.g;
                    sumB += neighbor.b;
                }
            }
            out[y * width + x].r = (sumR / FILTER_SIZE);
            out[y * width + x].g = (sumG / FILTER_SIZE);
            out[y * width + x].b = (sumB / FILTER_SIZE);
        }
    }

    // Copy the filtered image to the original image
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            img[y * width + x] = out[y * width + x];
        }
    }

    free(out);
}

// Function to read an image from a file
Pixel* loadImage(const char* filename, int* width, int* height) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        return NULL;
    }

    // Read the image header
    char header[12];
    fread(header, 1, 6);
    *width = *(int*)&header[4];
    *height = *(int*)&header[8];

    // Allocate memory for the image pixels
    Pixel* img = (Pixel*)malloc(*width * *height * sizeof(Pixel));

    // Read the image pixels
    fread(img, PIXELS_PER_BYTE, *width * *height);
    fclose(file);

    return img;
}

// Function to save an image to a file
void saveImage(const char* filename, Pixel* img, int width, int height) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        return;
    }

    // Write the image header
    char header[12];
    *(int*)&header[4] = width;
    *(int*)&header[8] = height;
    fwrite(header, 1, 6);
    fwrite(img, PIXELS_PER_BYTE, width * height);

    fclose(file);
}

// Function to apply a filter to an image and save it
void processImage(const char* input, const char* output) {
    Pixel* img = loadImage(input, &IMG_WIDTH, &IMG_HEIGHT);
    if (!img) {
        printf("Error reading image: %s\n", input);
        return;
    }

    applyFilter(img, IMG_WIDTH, IMG_HEIGHT);

    saveImage(output, img, IMG_WIDTH, IMG_HEIGHT);

    free(img);
}

int main() {
    processImage("input.png", "output.png");
    return 0;
}