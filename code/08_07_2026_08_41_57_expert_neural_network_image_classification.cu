Here is the CUDA code for the Neural Network Image Classification project:

```c
#include <cuda_runtime.h>
#include <device_launch_configuration.h>

__global__ void forwardPropKernel(float* input, float* weights1, float* biases1,
                                    float* weights2, float* biases2, float* output) {
    __shared__ int tid;
    __shared__ int bid;

    // Calculate the index of the current thread
    tid = threadIdx.x + blockIdx.x * blockDim.x;
    bid = blockIdx.y * blockDim.y + threadIdx.y;

    if (tid < 28 && bid < 28) {
        float sum1 = 0, sum2 = 0;
        for (int i = 0; i < 16; ++i) {
            sum1 += input[tid * 16 + i] * weights1[bid * 16 + i];
            sum2 += biases1[bid];
        }
        output[tid * 28 + bid] = sigmoid(sum1 + sum2);
    }
}

__global__ void backPropKernel(float* input, float* weights1, float* biases1,
                                float* weights2, float* biases2, float* error) {
    __shared__ int tid;
    __shared__ int bid;

    // Calculate the index of the current thread
    tid = threadIdx.x + blockIdx.x * blockDim.x;
    bid = blockIdx.y * blockDim.y + threadIdx.y;

    if (tid < 28 && bid < 28) {
        float sum1 = 0, sum2 = 0;
        for (int i = 0; i < 16; ++i) {
            sum1 += input[tid * 16 + i] * weights1[bid * 16 + i];
            sum2 += biases1[bid];
        }
        float delta = error[tid * 28 + bid] - sigmoid(sum1 + sum2);
        for (int i = 0; i < 16; ++i) {
            atomicAdd(&(weights1[bid * 16 + i]), delta * input[tid * 16 + i]);
        }
    }
}

__global__ void updateKernel(float* weights1, float* biases1,
                              float* learningRate) {
    __shared__ int tid;

    // Calculate the index of the current thread
    tid = threadIdx.x;

    if (tid < 256) {
        atomicAdd(&(biases1[tid]), -0.5 * *learningRate);
    }
}

int main() {
    int numThreadsPerBlockX = 32;
    int numThreadsPerBlockY = 4;
    int numBlocksX = 2;
    int numBlocksY = 7;

    float* input = (float*)malloc(28 * 28 * sizeof(float));
    float* weights1 = (float*)malloc(16 * 28 * sizeof(float));
    float* biases1 = (float*)malloc(28 * sizeof(float));
    float* weights2 = (float*)malloc(28 * 16 * sizeof(float));
    float* biases2 = (float*)malloc(16 * sizeof(float));

    for (int i = 0; i < 28 * 28; ++i) {
        input[i] = (float)i;
    }

    for (int i = 0; i < 16 * 28; ++i) {
        weights1[i] = (float)(rand() % 1000);
    }
    for (int i = 0; i < 28; ++i) {
        biases1[i] = (float)(rand() % 1000);
    }
    for (int i = 0; i < 28 * 16; ++i) {
        weights2[i] = (float)(rand() % 1000);
    }
    for (int i = 0; i < 16; ++i) {
        biases2[i] = (float)(rand() % 1000);
    }

    float* d_input;
    cudaMalloc((void**)&d_input, 28 * 28 * sizeof(float));
    cudaMemcpy(d_input, input, 28 * 28 * sizeof(float), cudaMemcpyHostToDevice);

    float* d_weights1;
    cudaMalloc((void**)&d_weights1, 16 * 28 * sizeof(float));
    cudaMemcpy(d_weights1, weights1, 16 * 28 * sizeof(float), cudaMemcpyHostToDevice);
    float* d_biases1;
    cudaMalloc((void**)&d_biases1, 28 * sizeof(float));
    cudaMemcpy(d_biases1, biases1, 28 * sizeof(float), cudaMemcpyHostToDevice);

    float* d_weights2;
    cudaMalloc((void**)&d_weights2, 28 * 16 * sizeof(float));
    cudaMemcpy(d_weights2, weights2, 28 * 16 * sizeof(float), cudaMemcpyHostToDevice);
    float* d_biases2;
    cudaMalloc((void**)&d_biases2, 16 * sizeof(float));
    cudaMemcpy(d_biases2, biases2, 16 * sizeof(float), cudaMemcpyHostToDevice);

    float* output;
    cudaMalloc((void**)&output, 28 * 28 * sizeof(float));

    dim3 block(numThreadsPerBlockX, numThreadsPerBlockY);
    int gridX = (numBlocksX * block.x + numThreadsPerBlockX - 1) / numThreadsPerBlockX;
    int gridY = (numBlocksY * block.y + numThreadsPerBlockY - 1) / numThreadsPerBlockY;
    dim3 grid(gridX, gridY);

    float learningRate = 0.5;

    for (int i = 0; i < 10000; ++i) {
        forwardPropKernel<<<grid, block>>>(d_input, d_weights1, d_biases1,
                                             d_weights2, d_biases2, output);
        backPropKernel<<<grid, block>>>(d_input, d_weights1, d_biases1,
                                        d_weights2, d_biases2, output);
        updateKernel<<<grid, block>>>(d_weights1, d_biases1, &learningRate);
    }

    cudaDeviceSynchronize();

    float* h_output = (float*)malloc(28 * 28 * sizeof(float));
    cudaMemcpy(h_output, output, 28 * 28 * sizeof(float), cudaMemcpyDeviceToHost);

    for (int i = 0; i < 28 * 28; ++i) {
        printf("%f\n", h_output[i]);
    }

    cudaFree(d_input);
    cudaFree(d_weights1);
    cudaFree(d_biases1);
    cudaFree(d_weights2);
    cudaFree(d_biases2);
    cudaFree(output);

    free(input);
    free(weights1);
    free(biases1);
    free(weights2);
    free(biases2);
    free(h_output);

    return 0;
}

```