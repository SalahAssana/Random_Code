#include <iostream>
#include <vector>
#include <algorithm>
#include "ImageProcessingFilter.h"

int main() {
    // Load image
    Image image("input.jpg");

    // Apply filters
    image.applyBlur();
    image.applyGrayscale();
    image.applySharpen();

    // Save filtered image
    image.saveAs("output.jpg");

    return 0;
}