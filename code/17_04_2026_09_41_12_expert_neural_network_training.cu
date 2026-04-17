Here is the CUDA code for the Neural Network Training project:

```cuda
#include <iostream>
#include <vector>
#include <cuda_runtime.h>

#define NUM_CLASSES 10
#define HIDDEN_UNITS 256
#define INPUT_UNITS 784
#define EPOCHS 10
#define BATCH_SIZE 32
#define LEARNING_RATE 0.1

__global__ void forwardPropogate(float* input, float* weights, float* output) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < INPUT_UNITS) {
        for (int i = 0; i < HIDDEN_UNITS; i++) {
            output[idx * HIDDEN_UNITS + i] = sigmoid(dot(input + idx, weights + idx * HIDDEN_UNITS + i));
        }
    }
}

__global__ void backPropogate(float* input, float* hidden, float* labels, float* output, float* weights, float* delta) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < INPUT_UNITS) {
        for (int i = 0; i < HIDDEN_UNITS; i++) {
            delta[idx * HIDDEN_UNITS + i] = sigmoidPrime(output[idx * HIDDEN_UNITS + i]) * (labels[idx] - output[idx * HIDDEN_UNITS + i]);
        }
    }
}

__global__ void updateWeights(float* weights, float* hidden, float* labels, float* output, float learningRate) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < INPUT_UNITS) {
        for (int i = 0; i < HIDDEN_UNITS; i++) {
            weights[idx * HIDDEN_UNITS + i] += learningRate * hidden[idx * HIDDEN_UNITS + i] * (labels[idx] - output[idx * HIDDEN_UNITS + i]);
        }
    }
}

float sigmoid(float x) {
    return 1.0 / (1.0 + exp(-x));
}

float sigmoidPrime(float x) {
    return x * (1.0 - x);
}

float dot(float* a, float* b, int length) {
    float sum = 0;
    for (int i = 0; i < length; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}

int main() {
    // Initialize data
    std::vector<float> inputs(INPUT_UNITS * EPOCHS);
    std::vector<float> labels(NUM_CLASSES * EPOCHS);
    std::vector<float> weights(INPUT_UNITS * HIDDEN_UNITS);

    // Allocate memory on GPU
    float* d_inputs;
    float* d_labels;
    float* d_weights;

    cudaMalloc((void**)&d_inputs, INPUT_UNITS * EPOCHS * sizeof(float));
    cudaMalloc((void**)&d_labels, NUM_CLASSES * EPOCHS * sizeof(float));
    cudaMalloc((void**)&d_weights, INPUT_UNITS * HIDDEN_UNITS * sizeof(float));

    // Copy data to GPU
    cudaMemcpy(d_inputs, inputs.data(), INPUT_UNITS * EPOCHS * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_labels, labels.data(), NUM_CLASSES * EPOCHS * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_weights, weights.data(), INPUT_UNITS * HIDDEN_UNITS * sizeof(float), cudaMemcpyHostToDevice);

    // Perform training
    for (int epoch = 0; epoch < EPOCHS; epoch++) {
        for (int batch = 0; batch < BATCH_SIZE; batch++) {
            float* d_hidden;
            cudaMalloc((void**)&d_hidden, INPUT_UNITS * HIDDEN_UNITS * sizeof(float));

            // Forward pass
            forwardPropogate<<<(INPUT_UNITS + 255) / 256, 256>>>(d_inputs, d_weights, d_hidden);

            // Backward pass
            backPropogate<<<(NUM_CLASSES + 255) / 256, 256>>>(d_inputs, d_hidden, d_labels, d_hidden, d_weights, d_hidden);

            // Update weights
            updateWeights<<<(INPUT_UNITS + 255) / 256, 256>>>(d_weights, d_hidden, d_labels, d_hidden, LEARNING_RATE);

            // Free memory on GPU
            cudaFree(d_hidden);
        }
    }

    // Copy results back to host
    cudaMemcpy(weights.data(), d_weights, INPUT_UNITS * HIDDEN_UNITS * sizeof(float), cudaMemcpyDeviceToHost);

    // Print results
    std::cout << "Weights: ";
    for (int i = 0; i < INPUT_UNITS * HIDDEN_UNITS; i++) {
        std::cout << weights[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```