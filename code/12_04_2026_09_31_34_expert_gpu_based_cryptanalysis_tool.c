#include <cuda_runtime.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CUDA_CHECK_ERROR() { \
    cudaError_t err = cudaGetLastError(); \
    if (err != cudaSuccess) { \
        printf("CUDA error: %s\n", cudaGetErrorString(err)); \
        exit(EXIT_FAILURE); \
    } \
}

__global__ void aes_decrypt_kernel(unsigned char *data, unsigned char *key, int length) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < length) {
        data[idx] ^= key[idx % 16];
    }
}

int main() {
    // Initialize CUDA
    cudaDeviceSynchronize();
    cudaSetDevice(0);

    // Allocate memory on GPU
    unsigned char *data_gpu, *key_gpu;
    int size = 1024 * 1024; // 1MB
    cudaMalloc((void **)&data_gpu, size);
    cudaMalloc((void **)&key_gpu, 16); // 128-bit key

    // Initialize data and key
    srand(time(NULL));
    unsigned char *data_host = new unsigned char[size];
    for (int i = 0; i < size; i++) {
        data_host[i] = rand() % 256;
    }
    unsigned char *key_host = new unsigned char[16];
    for (int i = 0; i < 16; i++) {
        key_host[i] = rand() % 256;
    }

    // Copy data and key to GPU
    cudaMemcpy(data_gpu, data_host, size, cudaMemcpyHostToDevice);
    cudaMemcpy(key_gpu, key_host, 16, cudaMemcpyHostToDevice);

    // Launch AES decryption kernel
    int blockSize = 32; // 32 threads per block
    int gridSize = (size + blockSize - 1) / blockSize;
    aes_decrypt_kernel<<<gridSize, blockSize>>>(data_gpu, key_gpu, size);

    // Synchronize GPU and copy results back to host
    cudaDeviceSynchronize();
    unsigned char *results_host = new unsigned char[size];
    cudaMemcpy(results_host, data_gpu, size, cudaMemcpyDeviceToHost);

    // Print decrypted data
    for (int i = 0; i < size; i++) {
        printf("%02x", results_host[i]);
    }
    printf("\n");

    // Free GPU memory and exit
    cudaFree(data_gpu);
    cudaFree(key_gpu);
    delete[] data_host;
    delete[] key_host;
    delete[] results_host;

    return 0;
}