#include <cuda_runtime.h>
#include <device_launch_configuration.h>

// Define a constant for the size of the kernel (radius of blur)
#define KERNEL_RADIUS 3

// Define a constant for the number of threads per block
#define BLOCK_THREADS 8

// Define a struct to hold the image data and dimensions
typedef struct {
    int width;
    int height;
    unsigned char* pixels;
} Image;

// Kernel function to apply Gaussian blur
__global__ void gaussianBlurKernel(float* input, float* output, int channels) {
    // Calculate the thread ID
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    // Check if we are within the image boundaries
    if (x < 0 || x >= input[0].width || y < 0 || y >= input[0].height) return;

    float sumR = 0.0f;
    float sumG = 0.0f;
    float sumB = 0.0f;

    // Loop over the neighboring pixels
    for (int i = -KERNEL_RADIUS; i <= KERNEL_RADIUS; i++) {
        for (int j = -KERNEL_RADIUS; j <= KERNEL_RADIUS; j++) {
            int neighborX = x + i;
            int neighborY = y + j;

            // Check if we are within the image boundaries
            if (neighborX >= 0 && neighborX < input[0].width &&
                neighborY >= 0 && neighborY < input[0].height) {
                float weight = expf(-((i * i) + (j * j)) / (2.0f * KERNEL_RADIUS * KERNEL_RADIUS));
                sumR += input[neighborY * input[0].width * channels + x * channels + 0] * weight;
                sumG += input[neighborY * input[0].width * channels + x * channels + 1] * weight;
                sumB += input[neighborY * input[0].width * channels + x * channels + 2] * weight;
            }
        }
    }

    // Store the blurred pixel values
    output[y * input[0].width * channels + x * channels + 0] = sumR / (float)pow((2.0f * KERNEL_RADIUS + 1), 2);
    output[y * input[0].width * channels + x * channels + 1] = sumG / (float)pow((2.0f * KERNEL_RADIUS + 1), 2);
    output[y * input[0].width * channels + x * channels + 2] = sumB / (float)pow((2.0f * KERNEL_RADIUS + 1), 2);
}

int main() {
    // Create an image with width 512, height 512, and 3 color channels
    Image image;
    image.width = 512;
    image.height = 512;
    image.pixels = (unsigned char*)malloc(image.width * image.height * 3);

    // Initialize the image pixels to random values
    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            int index = i * image.width * 3 + j * 3;
            image.pixels[index] = rand() % 256;
            image.pixels[index + 1] = rand() % 256;
            image.pixels[index + 2] = rand() % 256;
        }
    }

    // Allocate memory on the GPU
    float* d_input;
    cudaMalloc((void**)&d_input, image.width * image.height * 3 * sizeof(float));

    // Copy the image pixels to the GPU
    cudaMemcpy(d_input, image.pixels, image.width * image.height * 3 * sizeof(unsigned char), cudaMemcpyHostToDevice);

    // Create an output array on the GPU
    float* d_output;
    cudaMalloc((void**)&d_output, image.width * image.height * 3 * sizeof(float));

    // Launch the kernel
    int blocksX = (image.width + BLOCK_THREADS - 1) / BLOCK_THREADS;
    int blocksY = (image.height + BLOCK_THREADS - 1) / BLOCK_THREADS;
    dim3 blockSize(BLOCK_THREADS, BLOCK_THREADS);
    dim3 gridSize(blocksX, blocksY);
    gaussianBlurKernel<<<gridSize, blockSize>>>(d_input, d_output, 3);

    // Copy the output back to the host
    float* output = (float*)malloc(image.width * image.height * 3 * sizeof(float));
    cudaMemcpy(output, d_output, image.width * image.height * 3 * sizeof(float), cudaMemcpyDeviceToHost);

    // Print the blurred pixel values
    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            int index = i * image.width * 3 + j * 3;
            printf("Pixel %d: (%f, %f, %f)\n", index, output[index], output[index + 1], output[index + 2]);
        }
    }

    // Free memory on the GPU
    cudaFree(d_input);
    cudaFree(d_output);

    // Free memory on the host
    free(image.pixels);
    free(output);

    return 0;
}