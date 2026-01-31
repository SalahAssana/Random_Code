#include <cuda_runtime.h>
#include <stdio.h>

__global__ void helloWorldKernel() {
    int id = threadIdx.x;
    printf("Hello from thread %d!\n", id);
}

int main() {
    // Allocate device memory
    int *d_data;
    cudaMalloc((void **)&d_data, sizeof(int) * 256);

    // Launch kernel on GPU
    helloWorldKernel<<<1, 256>>>();

    // Synchronize threads
    cudaDeviceSynchronize();

    // Free device memory
    cudaFree(d_data);
    return 0;