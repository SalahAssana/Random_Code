#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the pixel data type
typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Pixel;

// Define the image data structure
typedef struct {
    int width;
    int height;
    Pixel** pixels;
} Image;

// Function to create a new image with the given dimensions and fill it with zeros
Image* create_image(int width, int height) {
    Image* img = (Image*) malloc(sizeof(Image));
    img->width = width;
    img->height = height;
    img->pixels = (Pixel**) malloc(width * sizeof(Pixel*));
    for (int i = 0; i < width; i++) {
        img->pixels[i] = (Pixel*) malloc(height * sizeof(Pixel));
        for (int j = 0; j < height; j++) {
            img->pixels[i][j].red = 0;
            img->pixels[i][j].green = 0;
            img->pixels[i][j].blue = 0;
        }
    }
    return img;
}

// Function to apply a convolutional filter to the image
void convolve(Image* img, float** kernel) {
    int width = img->width;
    int height = img->height;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Pixel* pixel = &img->pixels[i][j];
            float red = 0, green = 0, blue = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    int x = i + k;
                    int y = j + l;
                    if (x >= 0 && x < width && y >= 0 && y < height) {
                        Pixel* neighbor = &img->pixels[x][y];
                        red += kernel[k+1][l+1] * neighbor->red;
                        green += kernel[k+1][l+1] * neighbor->green;
                        blue += kernel[k+1][l+1] * neighbor->blue;
                    }
                }
            }
            pixel->red = (unsigned char) (red + 0.5);
            pixel->green = (unsigned char) (green + 0.5);
            pixel->blue = (unsigned char) (blue + 0.5);
        }
    }
}

// Function to apply a threshold filter to the image
void threshold(Image* img, int threshold) {
    int width = img->width;
    int height = img->height;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Pixel* pixel = &img->pixels[i][j];
            if ((pixel->red + pixel->green + pixel->blue) / 3 > threshold) {
                pixel->red = 255;
                pixel->green = 255;
                pixel->blue = 255;
            } else {
                pixel->red = 0;
                pixel->green = 0;
                pixel->blue = 0;
            }
        }
    }
}

// Function to apply a blur filter to the image
void blur(Image* img) {
    int width = img->width;
    int height = img->height;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Pixel* pixel = &img->pixels[i][j];
            float red = 0, green = 0, blue = 0;
            int count = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    int x = i + k;
                    int y = j + l;
                    if (x >= 0 && x < width && y >= 0 && y < height) {
                        Pixel* neighbor = &img->pixels[x][y];
                        red += neighbor->red;
                        green += neighbor->green;
                        blue += neighbor->blue;
                        count++;
                    }
                }
            }
            pixel->red = (unsigned char) (red / count);
            pixel->green = (unsigned char) (green / count);
            pixel->blue = (unsigned char) (blue / count);
        }
    }
}

// Function to display the image
void display_image(Image* img) {
    int width = img->width;
    int height = img->height;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Pixel* pixel = &img->pixels[i][j];
            printf("%c%c%c", pixel->red, pixel->green, pixel->blue);
        }
        printf("\n");
    }
}

// Main function
int main() {
    // Create a new image with dimensions 10x10
    Image* img = create_image(10, 10);

    // Set the initial pixel values
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            Pixel* pixel = &img->pixels[i][j];
            pixel->red = rand() % 256;
            pixel->green = rand() % 256;
            pixel->blue = rand() % 256;
        }
    }

    // Apply a convolutional filter to the image
    float** kernel = (float**) malloc(3 * sizeof(float*));
    for (int i = 0; i < 3; i++) {
        kernel[i] = (float*) malloc(3 * sizeof(float));
        for (int j = 0; j < 3; j++) {
            kernel[i][j] = (i == 1) ? -1 : (i == 0) ? 1 : 2;
        }
    }
    convolve(img, kernel);
    free(kernel);

    // Apply a threshold filter to the image
    int threshold = 128;
    threshold(img, threshold);

    // Apply a blur filter to the image
    blur(img);

    // Display the final image
    display_image(img);

    return 0;
}