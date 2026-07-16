Here is the CUDA code for the Neural Network for Handwritten Digits Recognition:

```cuda
#include <iostream>
#include <cuda_runtime.h>

#define THREADS_PER_BLOCK 16
#define BLOCKS_PER_GRID 32

__global__ void kernel(float *input, float *weights, float *biases, float *output) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (idx >= output.size()) return;
    
    float sum = 0.0f;
    for (int i = 0; i < weights.size(); i += THREADS_PER_BLOCK) {
        int start = i;
        int end = min(i+THREADS_PER_BLOCK, weights.size());
        
        __shared__ float w[THREADS_PER_BLOCK];
        __shared__ float in[THREADS_PER_BLOCK];
        __shared__ float b[THREADS_PER_BLOCK];
        
        for (int j = 0; j < end-start; j++) {
            int k = start+j;
            w[j] = weights[k];
            in[j] = input[idx*k];
            b[j] = biases[k];
        }
        
        __syncthreads();
        
        float val = 0.0f;
        for (int j = 0; j < end-start; j++) {
            val += w[j]*in[j] + b[j];
        }
        
        sum += val;
    }
    
    output[idx] = sigmoid(sum);
}

float sigmoid(float x) {
    return 1.0f / (1.0f + exp(-x));
}

int main() {
    float *input, *weights, *biases, *output;
    int size = 784; // input features
    int numLayers = 2; // number of hidden layers
    int neuronsPerLayer[] = {256, 10}; // number of neurons per layer
    
    // allocate memory on host
    cudaMalloc((void **)&input, sizeof(float)*size);
    cudaMalloc((void **)&weights, sizeof(float)*size*neuronsPerLayer[0]);
    cudaMalloc((void **)&biases, sizeof(float)*neuronsPerLayer[0]);
    cudaMalloc((void **)&output, sizeof(float)*neuronsPerLayer[numLayers-1]);
    
    // initialize data
    float *data = new float[size];
    for (int i = 0; i < size; i++) {
        data[i] = rand() % 2;
    }
    
    // copy data to device
    cudaMemcpy(input, data, sizeof(float)*size, cudaMemcpyHostToDevice);
    
    // launch kernel
    int blocksPerGrid = ceil((float)size / THREADS_PER_BLOCK);
    int threadsPerBlock = THREADS_PER_BLOCK;
    dim3 grid(blocksPerGrid, 1), block(threadsPerBlock, 1);
    kernel<<<grid, block>>>(input, weights, biases, output);
    
    // copy results back to host
    float *results = new float[neuronsPerLayer[numLayers-1]];
    cudaMemcpy(results, output, sizeof(float)*neuronsPerLayer[numLayers-1], cudaMemcpyDeviceToHost);
    
    for (int i = 0; i < neuronsPerLayer[numLayers-1]; i++) {
        std::cout << results[i] << " ";
    }
    
    // free memory
    delete[] data;
    cudaFree(input);
    cudaFree(weights);
    cudaFree(biases);
    cudaFree(output);
    
    return 0;
}
```