#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <iostream>

// Define a constant string to print
const char* hello = "Hello World\n";

__global__ void printMessage(const char* message) {
    // Each thread prints the message
    printf("%s", message);
}

int main() {
    // Allocate memory on the host for the message
    const char* message = (const char*)malloc(strlen(hello) + 1);

    // Copy the message to the device
    cudaMemcpyToSymbol(printMessage, &hello, sizeof(char*));

    // Launch a kernel to print the message
    int numThreads = 1;
    dim3 blockSize(1);
    dim3 gridSize(1);
    printMessage<<<gridSize, blockSize>>>(message);

    // Synchronize the threads
    cudaDeviceSynchronize();

    // Free memory on the host
    free(message);

    return 0;
}