#include <cuda_runtime.h>
#include <stdio.h>

__global__ void printHello() {
    printf("Hello, world!\n");
}

int main() {
    int numThreads = 1;
    int numBlocks = 1;

    // Allocate memory on the host
    printf("Starting CUDA...\n");

    // Launch kernel
    printHello<<<numBlocks, numThreads>>>();

    // Synchronize threads
    cudaDeviceSynchronize();

    // Free memory
    printf("CUDA done.\n");
    return 0;
}