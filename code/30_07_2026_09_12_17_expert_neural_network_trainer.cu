Here is the CUDA code for the Neural Network Trainer:

```cuda
#include <iostream>
#include <cuda_runtime.h>

// Define constants
#define NUM_LAYERS 3
#define INPUT_SIZE 784
#define HIDDEN_SIZE 256
#define OUTPUT_SIZE 10
#define BATCH_SIZE 32
#define MAX_ITERS 1000

// Struct for a neural network layer
struct Layer {
    float* weights;
    float* bias;
};

// Kernel to compute the forward pass
__global__ void forward(float* input, float* hidden, float* output, Layer layers[], int numLayers) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < INPUT_SIZE) {
        for (int i = 0; i < numLayers - 1; i++) {
            int layerIdx = i;
            float sum = 0.0f;
            for (int j = 0; j < layers[layerIdx].weightSize; j++) {
                sum += input[idx] * layers[layerIdx].weights[j];
            }
            sum += layers[layerIdx].bias[0];
            output[idx] = sigmoid(sum);
        }
    }
}

// Kernel to compute the backward pass
__global__ void backward(float* error, float* deltaHidden, Layer layers[], int numLayers) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < INPUT_SIZE) {
        for (int i = numLayers - 1; i > 0; i--) {
            int layerIdx = i;
            float sum = 0.0f;
            for (int j = 0; j < layers[layerIdx].weightSize; j++) {
                sum += deltaHidden[idx] * layers[layerIdx].weights[j];
            }
            error[idx] = sigmoidPrime(error[idx]) * sum;
        }
    }
}

// Kernel to update the weights and bias
__global__ void update(float* input, float* hidden, float* output, Layer* layers, int numLayers) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < INPUT_SIZE) {
        for (int i = 0; i < numLayers - 1; i++) {
            int layerIdx = i;
            float dw = 0.0f;
            float db = 0.0f;
            for (int j = 0; j < layers[layerIdx].weightSize; j++) {
                dw += error[idx] * input[idx];
            }
            dw *= learningRate;
            db = error[idx];
            __syncthreads();
            if (idx < INPUT_SIZE) {
                layers[layerIdx].weights[idx] -= dw;
                layers[layerIdx].bias[0] -= db;
            }
        }
    }
}

// Main function
int main() {
    // Allocate memory on the host
    float* input = new float[BATCH_SIZE * INPUT_SIZE];
    float* hidden = new float[BATCH_SIZE * HIDDEN_SIZE];
    float* output = new float[BATCH_SIZE * OUTPUT_SIZE];

    // Initialize neural network layers
    Layer layers[NUM_LAYERS];
    for (int i = 0; i < NUM_LAYERS; i++) {
        layers[i].weights = new float[HIDDEN_SIZE];
        layers[i].bias = new float[1];
    }

    // Initialize synthetic data
    for (int i = 0; i < BATCH_SIZE * INPUT_SIZE; i++) {
        input[i] = (float)i / 100.0f;
    }
    for (int i = 0; i < BATCH_SIZE * HIDDEN_SIZE; i++) {
        hidden[i] = (float)i / 100.0f;
    }
    for (int i = 0; i < BATCH_SIZE * OUTPUT_SIZE; i++) {
        output[i] = (float)i / 100.0f;
    }

    // Set up CUDA
    int numBlocks = (BATCH_SIZE * INPUT_SIZE + 255) / 256;
    int numThreads = 256;

    // Launch kernels
    forward<<<numBlocks, numThreads>>>(input, hidden, output, layers, NUM_LAYERS);
    backward<<<numBlocks, numThreads>>>(output, hidden, layers, NUM_LAYERS);
    update<<<numBlocks, numThreads>>>(input, hidden, output, layers, NUM_LAYERS);

    // Synchronize
    cudaDeviceSynchronize();

    // Clean up
    delete[] input;
    delete[] hidden;
    delete[] output;
    for (int i = 0; i < NUM_LAYERS; i++) {
        delete[] layers[i].weights;
        delete[] layers[i].bias;
    }

    return 0;
}

// Sigmoid function
float sigmoid(float x) {
    return 1.0f / (1.0f + exp(-x));
}

// Sigmoid prime function
float sigmoidPrime(float x) {
    return x * (1.0f - x);
}
```

This code trains a neural network on synthetic data using backpropagation and gradient descent.