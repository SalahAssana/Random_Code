#include <cuda_runtime.h>
#include <stdio.h>

// Define a structure to hold our data
struct Data {
    int id;
};

__global__ void printHelloWorld(struct Data* data) {
    // Get the block and thread IDs
    int bid = blockIdx.x;
    int tid = threadIdx.x;

    // Print 'Hello World' for each thread in the grid
    if (tid == 0 && bid == 0) {
        printf("Hello World\n");
    }
}

int main() {
    // Allocate memory on the host
    struct Data* dataHost = (struct Data*)malloc(sizeof(struct Data));

    // Allocate memory on the device
    struct Data* dataDevice;
    cudaMalloc((void**)&dataDevice, sizeof(struct Data));

    // Set the ID of our synthetic data
    dataHost->id = 0;

    // Copy the host data to the device
    cudaMemcpy(dataDevice, &dataHost, sizeof(struct Data), cudaMemcpyHostToDevice);

    // Launch the kernel
    int blockSize = 1;
    int gridSize = 1;
    printHelloWorld<<<gridSize, blockSize>>>(dataDevice);

    // Synchronize the GPU
    cudaDeviceSynchronize();

    // Free memory on the device and host
    cudaFree(dataDevice);
    free(dataHost);

    return 0;
}