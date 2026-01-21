#include <cuda_runtime.h>
#include <stdio.h>

// Define a struct to hold our random number generator state
struct RandState {
    int seed;
};

// Kernel to generate random numbers
__global__ void randKernel(RandState* state, float* output, int numSamples) {
    // Calculate the thread ID (x-coordinate)
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (tid < numSamples) {
        // Use the current seed and increment it for next time
        state->seed = (state->seed * 1103515245 + 12345) % 2147483647;
        output[tid] = (float)state->seed / 2147483647.0f;
    }
}

int main() {
    // Initialize CUDA runtime
    cudaError_t err = cudaSuccess;

    // Define the number of random numbers to generate
    int numSamples = 1000000;

    // Allocate memory on the host for our output array
    float* h_output = (float*)malloc(numSamples * sizeof(float));

    // Create a RandState struct and initialize it with a seed
    RandState state;
    state.seed = 123456789;

    // Allocate memory on the device for our RandState and output arrays
    RandState* d_state;
    float* d_output;

    err = cudaMalloc((void**)&d_state, sizeof(RandState));
    if (err != cudaSuccess) {
        printf("Error allocating memory for RandState: %s\n", cudaGetErrorString(err));
        return 1;
    }

    err = cudaMalloc((void**)&d_output, numSamples * sizeof(float));
    if (err != cudaSuccess) {
        printf("Error allocating memory for output array: %s\n", cudaGetErrorString(err));
        return 1;
    }

    // Copy our RandState struct to the device
    err = cudaMemcpy(d_state, &state, sizeof(RandState), cudaMemcpyHostToDevice);
    if (err != cudaSuccess) {
        printf("Error copying RandState to the device: %s\n", cudaGetErrorString(err));
        return 1;
    }

    // Launch our kernel
    int blockSize = 256;
    int numBlocks = (numSamples + blockSize - 1) / blockSize;

    randKernel<<<numBlocks, blockSize>>>(d_state, d_output, numSamples);

    // Synchronize the device to ensure our kernel has finished
    cudaDeviceSynchronize();

    // Copy the output array from the device back to the host
    err = cudaMemcpy(h_output, d_output, numSamples * sizeof(float), cudaMemcpyDeviceToHost);
    if (err != cudaSuccess) {
        printf("Error copying output array from the device: %s\n", cudaGetErrorString(err));
        return 1;
    }

    // Free memory on the host and device
    free(h_output);
    cudaFree(d_state);
    cudaFree(d_output);

    return 0;