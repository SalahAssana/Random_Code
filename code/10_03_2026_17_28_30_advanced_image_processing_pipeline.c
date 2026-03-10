#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Define constants for image processing
#define FILTER_SIZE 3
#define PIXEL_MAX 255

// Structure to represent an image pixel
typedef struct {
    unsigned char r, g, b;
} Pixel;

// Function to apply a filter to the image
void applyFilter(Pixel *image, int width, int height, int filter[FILTER_SIZE][FILTER_SIZE]) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Pixel pixel;
            for (int fy = -1; fy <= 1; fy++) {
                for (int fx = -1; fx <= 1; fx++) {
                    int ny = y + fy;
                    int nx = x + fx;
                    if (ny >= 0 && ny < height && nx >= 0 && nx < width) {
                        pixel.r += filter[fy + 1][fx + 1] * image[nx + width * ny].r;
                        pixel.g += filter[fy + 1][fx + 1] * image[nx + width * ny].g;
                        pixel.b += filter[fy + 1][fx + 1] * image[nx + width * ny].b;
                    }
                }
            }
            // Normalize the pixel values
            pixel.r /= FILTER_SIZE * FILTER_SIZE;
            pixel.g /= FILTER_SIZE * FILTER_SIZE;
            pixel.b /= FILTER_SIZE * FILTER_SIZE;
            // Ensure the pixel values are within the valid range
            pixel.r = (pixel.r > 0) ? pixel.r : 0;
            pixel.g = (pixel.g > 0) ? pixel.g : 0;
            pixel.b = (pixel.b > 0) ? pixel.b : 0;
            // Ensure the pixel values do not exceed the maximum value
            pixel.r = (pixel.r < PIXEL_MAX) ? pixel.r : PIXEL_MAX;
            pixel.g = (pixel.g < PIXEL_MAX) ? pixel.g : PIXEL_MAX;
            pixel.b = (pixel.b < PIXEL_MAX) ? pixel.b : PIXEL_MAX;
            // Set the processed pixel in the image array
            image[x + width * y].r = pixel.r;
            image[x + width * y].g = pixel.g;
            image[x + width * y].b = pixel.b;
        }
    }
}

// Function to load an image from a file
Pixel *loadImage(char *filename, int *width, int *height) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    rewind(file);
    Pixel *image = (Pixel *)malloc((fileSize / 3) * sizeof(Pixel));
    fread(image, 1, fileSize, file);
    fclose(file);
    *width = (int)sqrt((double)fileSize / 3);
    *height = *width;
    return image;
}

// Function to save an image to a file
void saveImage(char *filename, Pixel *image, int width, int height) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return;
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            fwrite(&image[x + width * y].r, 1, 3, file);
        }
    }
    fclose(file);
}

// Function to apply a blur filter
void applyBlur(Pixel *image, int width, int height) {
    int filter[FILTER_SIZE][FILTER_SIZE] = {
        {1/9.0, 1/9.0, 1/9.0},
        {1/9.0, 1/9.0, 1/9.0},
        {1/9.0, 1/9.0, 1/9.0}
    };
    applyFilter(image, width, height, filter);
}

// Function to apply a sharpen filter
void applySharpen(Pixel *image, int width, int height) {
    int filter[FILTER_SIZE][FILTER_SIZE] = {
        {-1/16.0, -2/16.0, -1/16.0},
        {-2/16.0, 12/16.0, -2/16.0},
        {-1/16.0, -2/16.0, -1/16.0}
    };
    applyFilter(image, width, height, filter);
}

int main() {
    Pixel *image = loadImage("input.ppm", &width, &height);
    if (image == NULL) {
        return 1;
    }
    // Apply filters to the image
    applyBlur(image, width, height);
    applySharpen(image, width, height);
    // Save the processed image to a file
    saveImage("output.ppm", image, width, height);
    free(image);
    return 0;
}