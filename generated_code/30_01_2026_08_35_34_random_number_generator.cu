#include <iostream>
#include <cuda_runtime.h>

const int numBlocks = 1;
const int blockSize = 256;

__global__ void randomNumberGenerator(float* result) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < 10000) { // generate 10,000 numbers
        float randNum = static_cast<float>(rand()) / RAND_MAX; // generate random number between 0 and 1
        result[index] = randNum; // store in global memory
    }
}

int main() {
    cudaDeviceSynchronize();

    int numElements = 10000;
    float* h_result = new float[numElements];
    float* d_result;

    cudaMalloc((void**)&d_result, numElements * sizeof(float));

    for (int i = 0; i < numElements; i++) {
        // generate random numbers on the host
        h_result[i] = static_cast<float>(rand()) / RAND_MAX;
    }

    randomNumberGenerator<<<numBlocks, blockSize>>>(d_result);

    cudaDeviceSynchronize();
    cudaMemcpy(h_result, d_result, numElements * sizeof(float), cudaMemcpyDeviceToHost);

    for (int i = 0; i < numElements; i++) {
        std::cout << h_result[i] << " ";
    }
    std::cout << std::endl;

    cudaFree(d_result);
    delete[] h_result;
    return 0;
}