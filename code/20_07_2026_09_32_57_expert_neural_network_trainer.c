#include <cuda_runtime.h>
#include <curand_kernel.h>

// Define constants for the neural network architecture
#define NUM_INPUTS 784
#define HIDDEN_LAYERS 2
#define HIDDEN_NEURONS 256
#define OUTPUT_LAYER 10

// Define a struct to represent a neuron in the hidden layer
typedef struct {
    float weights[HIDDEN_NEURONS];
    float bias;
} HiddenNeuron;

// Define a struct to represent a neuron in the output layer
typedef struct {
    float weights[OUTPUT_LAYER];
    float bias;
} OutputNeuron;

__global__ void forwardPropagate(float *input, HiddenNeuron *hiddenLayers, OutputNeuron *outputLayer) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < NUM_INPUTS) {
        float sum = 0.0f;
        for (int i = 0; i < HIDDEN_NEURONS; i++) {
            sum += hiddenLayers[i].weights[idx] * input[idx];
        }
        sum += hiddenLayers[0].bias;
        __syncthreads();
        int idxHidden = blockIdx.x * blockDim.x + threadIdx.x;
        if (idxHidden < HIDDEN_LAYERS) {
            float output = sigmoid(sum);
            for (int i = 0; i < OUTPUT_LAYER; i++) {
                sum += outputLayer[i].weights[idx] * output;
            }
            sum += outputLayer[0].bias;
            input[idx] = sigmoid(sum);
        }
    }
}

__global__ void backPropagate(float *input, float *target, HiddenNeuron *hiddenLayers, OutputNeuron *outputLayer) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < NUM_INPUTS) {
        float error = 0.0f;
        for (int i = 0; i < OUTPUT_LAYER; i++) {
            error += (target[i] - input[idx]) * input[idx];
        }
        __syncthreads();
        int idxHidden = blockIdx.x * blockDim.x + threadIdx.x;
        if (idxHidden < HIDDEN_LAYERS) {
            float output = sigmoid(input[idx]);
            for (int i = 0; i < OUTPUT_LAYER; i++) {
                error += (target[i] - output) * outputLayer[i].weights[idx];
            }
            hiddenLayers[0].bias -= 0.01f * error;
        }
    }
}

__global__ void updateWeights(float *input, float *target, HiddenNeuron *hiddenLayers, OutputNeuron *outputLayer) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < NUM_INPUTS) {
        for (int i = 0; i < HIDDEN_NEURONS; i++) {
            hiddenLayers[i].weights[idx] -= 0.01f * (target[0] - sigmoid(input[idx])) * input[idx];
        }
        for (int i = 0; i < OUTPUT_LAYER; i++) {
            outputLayer[i].weights[idx] -= 0.01f * (target[0] - sigmoid(input[idx])) * input[idx];
        }
    }
}

__global__ void trainNetwork(float *input, float *target) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < NUM_INPUTS) {
        forwardPropagate<<<1, 256>>>(input, hiddenLayers, outputLayer);
        backPropagate<<<1, 256>>>(input, target, hiddenLayers, outputLayer);
        updateWeights<<<1, 256>>>(input, target, hiddenLayers, outputLayer);
    }
}

int main() {
    // Initialize CUDA
    cudaDeviceSynchronize();
    cudaMalloc((void**)&hiddenLayers, HIDDEN_LAYERS * sizeof(HiddenNeuron));
    cudaMalloc((void**)&outputLayer, OUTPUT_LAYER * sizeof(OutputNeuron));

    // Load synthetic data
    float *input = (float*)malloc(NUM_INPUTS * sizeof(float));
    float *target = (float*)malloc(OUTPUT_LAYER * sizeof(float));
    for (int i = 0; i < NUM_INPUTS; i++) {
        input[i] = (float)(rand() % 100) / 100.0f;
    }
    for (int i = 0; i < OUTPUT_LAYER; i++) {
        target[i] = (float)(rand() % 2);
    }

    // Train the network
    int numEpochs = 1000;
    for (int epoch = 0; epoch < numEpochs; epoch++) {
        trainNetwork<<<1, 256>>>(input, target);
        cudaDeviceSynchronize();
    }

    // Evaluate the network
    float *output = (float*)malloc(NUM_INPUTS * sizeof(float));
    forwardPropagate<<<1, 256>>>(input, hiddenLayers, outputLayer);
    for (int i = 0; i < NUM_INPUTS; i++) {
        printf("%f\n", sigmoid(output[i]));
    }

    // Clean up
    free(input);
    free(target);
    cudaFree(hiddenLayers);
    cudaFree(outputLayer);

    return 0;
}

float sigmoid(float x) {
    return 1.0f / (1.0f + exp(-x));
}