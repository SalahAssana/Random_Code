#include <stdio.h>

// Define a CUDA kernel that prints 'Hello, World!' on a GPU
__global__ void helloWorldKernel() {
    // Each thread will print 'Hello, World!'
    printf("Hello, World!\n");
}

int main() {
    // Allocate memory for the kernel grid and block
    int numThreads = 1;
    dim3 blockSize(1);
    dim3 gridSize(1);

    // Launch the kernel on the GPU
    helloWorldKernel<<<gridSize, blockSize>>>();

    // Synchronize threads to ensure kernel execution is complete
    cudaDeviceSynchronize();

    return 0;
}