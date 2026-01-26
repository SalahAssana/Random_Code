#include <cuda_runtime.h>
#include <stdio.h>

__global__ void printHello() {
    printf("Hello, World!\n");
}

int main() {
    // Allocate memory on host for device copy
    char *deviceMessage;
    cudaMalloc((void **)&deviceMessage, 13 * sizeof(char));

    // Copy string to device
    cudaMemcpy(deviceMessage, "Hello, World!", 12, cudaMemcpyHostToDevice);

    // Launch kernel
    printHello<<<1,1>>>();

    // Synchronize threads
    cudaDeviceSynchronize();

    // Print message from device
    printf("%s\n", deviceMessage);

    // Free memory on host and device
    cudaFree(deviceMessage);
    return 0;
}