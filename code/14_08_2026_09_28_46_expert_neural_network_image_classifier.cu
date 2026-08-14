Here is the CUDA code for the Neural Network Image Classifier:
```
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

__constant__ float8 weights[256]; // weights for convolutional layer
__global__ void convolutionKernel(float* input, float* output) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < 28 && y < 28) {
        float sum = 0.0f;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                int offset = (i * 28 + j);
                sum += input[offset] * weights[offset];
            }
        }
        output[y * 28 + x] = sum;
    }
}

__global__ void poolingKernel(float* input, float* output) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < 14 && y < 14) {
        float maxVal = -INFINITY;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                int offset = (i * 28 + j);
                maxVal = fmax(maxVal, input[offset]);
            }
        }
        output[y * 14 + x] = maxVal;
    }
}

__global__ void fullyConnectedKernel(float* input, float* weights, float* bias, float* output) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < 10) {
        float sum = 0.0f;
        for (int i = 0; i < 784; i++) {
            sum += input[i] * weights[idx * 784 + i];
        }
        output[idx] = sum + bias[idx];
    }
}

__global__ void softmaxKernel(float* input, float* output) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < 10) {
        float expVal = exp(input[idx]);
        float sum = 0.0f;
        for (int i = 0; i < 10; i++) {
            sum += exp(input[i]);
        }
        output[idx] = expVal / sum;
    }
}

__global__ void trainKernel(float* input, float* target, float* weights, float* bias) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < 10) {
        float predict = 0.0f;
        for (int i = 0; i < 784; i++) {
            predict += input[i] * weights[idx * 784 + i];
        }
        predict += bias[idx];

        float error = target[idx] - predict;
        for (int i = 0; i < 784; i++) {
            weights[idx * 784 + i] -= 0.1f * error * input[i];
        }
        bias[idx] -= 0.1f * error;

        // backpropagate error to convolutional layer
        float convError[256];
        for (int i = 0; i < 256; i++) {
            convError[i] = 0.0f;
        }
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 5; k++) {
                for (int l = 0; l < 5; l++) {
                    int offset = (k * 28 + l) * 256;
                    convError[offset] += error * weights[j * 784 + offset];
                }
            }
        }

        // update convolutional layer
        for (int i = 0; i < 256; i++) {
            weights[i] -= 0.1f * convError[i];
        }
    }
}

int main() {
    int numThreadsPerBlock = 16;
    int numBlocksX = 14;
    int numBlocksY = 14;

    float* inputDevice;
    float* outputDevice;
    float* weightsDevice;
    float* biasDevice;
    float* targetDevice;
    cudaMalloc((void**)&inputDevice, 784 * sizeof(float));
    cudaMalloc((void**)&outputDevice, 196 * sizeof(float));
    cudaMalloc((void**)&weightsDevice, 256 * 784 * sizeof(float));
    cudaMalloc((void**)&biasDevice, 10 * sizeof(float));
    cudaMalloc((void**)&targetDevice, 10 * sizeof(float));

    // copy data from host to device
    cudaMemcpy(inputDevice, input, 784 * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(targetDevice, target, 10 * sizeof(float), cudaMemcpyHostToDevice);

    // run convolutional layer
    dim3 block(numThreadsPerBlock, numThreadsPerBlock);
    dim3 grid(numBlocksX, numBlocksY);
    convolutionKernel<<<grid, block>>>(inputDevice, outputDevice);

    // run pooling layer
    cudaMalloc((void**)&outputDevice2, 196 * sizeof(float));
    convolutionKernel<<<grid, block>>>(outputDevice, outputDevice2);
    cudaFree(outputDevice);

    // run fully connected layer
    float* hiddenDevice;
    float* outputDevice3;
    cudaMalloc((void**)&hiddenDevice, 10 * sizeof(float));
    cudaMalloc((void**)&outputDevice3, 1 * sizeof(float));
    fullyConnectedKernel<<<grid, block>>>(outputDevice2, weightsDevice, biasDevice, hiddenDevice);
    softmaxKernel<<<grid, block>>>(hiddenDevice, outputDevice3);

    // run train kernel
    float* errorDevice;
    cudaMalloc((void**)&errorDevice, 10 * sizeof(float));
    trainKernel<<<grid, block>>>(inputDevice, targetDevice, weightsDevice, biasDevice);

    // copy data from device to host
    cudaMemcpy(input, inputDevice, 784 * sizeof(float), cudaMemcpyDeviceToHost);
    cudaMemcpy(target, targetDevice, 10 * sizeof(float), cudaMemcpyDeviceToHost);

    cudaFree(inputDevice);
    cudaFree(outputDevice2);
    cudaFree(hiddenDevice);
    cudaFree(outputDevice3);
    cudaFree(errorDevice);
}
```