#include <iostream>
#include <vector>
#include <omp.h>

#define NUM_THREADS 4
#define BLOCK_SIZE 16
#define THREADS_PER_BLOCK 128

__global__ void matrixMulKernel(float *A, float *B, float *C) {
    int threadId = threadIdx.x;
    int blockId = blockIdx.x;

    __shared__ float As[BLOCK_SIZE][BLOCK_SIZE];
    __shared__ float Bs[BLOCK_SIZE][BLOCK_SIZE];

    for (int i = 0; i < BLOCK_SIZE / THREADS_PER_BLOCK; i++) {
        if (threadId < THREADS_PER_BLOCK) {
            int row = i * THREADS_PER_BLOCK + threadId;
            As[threadId][i] = A[row * BLOCK_SIZE + blockId];
        }
        __syncthreads();

        for (int j = 0; j < BLOCK_SIZE / THREADS_PER_BLOCK; j++) {
            if (threadId < THREADS_PER_BLOCK) {
                int col = j * THREADS_PER_BLOCK + threadId;
                Bs[threadId][j] = B[blockId * BLOCK_SIZE + col];
            }
            __syncthreads();

            for (int k = 0; k < BLOCK_SIZE / THREADS_PER_BLOCK; k++) {
                if (threadId < THREADS_PER_BLOCK) {
                    int rowA = i * THREADS_PER_BLOCK + k;
                    int colB = j * THREADS_PER_BLOCK + k;
                    C[rowA * BLOCK_SIZE + blockId] += As[threadId][k] * Bs[threadId][j];
                }
            }
        }
    }
}

int main() {
    int M = 1024, N = 2048; // Matrix dimensions
    float *A, *B, *C;

    cudaMalloc((void **)&A, M * N * sizeof(float));
    cudaMalloc((void **)&B, N * M * sizeof(float));
    cudaMalloc((void **)&C, M * M * sizeof(float));

    std::vector<float> A_data(M * N), B_data(N * M);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            A_data[i * N + j] = (float)(i + j) / 100.0f;
            B_data[i * M + j] = (float)(i - j) / 100.0f;
        }
    }

    cudaMemcpy(A, &A_data[0], M * N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(B, &B_data[0], N * M * sizeof(float), cudaMemcpyHostToDevice);

    dim3 block(BLOCK_SIZE, BLOCK_SIZE);
    dim3 grid(M / BLOCK_SIZE + 1, N / BLOCK_SIZE + 1);

    matrixMulKernel<<<grid, block>>>(A, B, C);

    cudaDeviceSynchronize();

    float *C_host;
    cudaMalloc((void **)&C_host, M * M * sizeof(float));
    cudaMemcpy(C_host, C, M * M * sizeof(float), cudaMemcpyDeviceToHost);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            std::cout << C_host[i * M + j] << " ";
        }
        std::cout << std::endl;
    }

    cudaFree(A);
    cudaFree(B);
    cudaFree(C);
    cudaFree(C_host);

    return 0;
}
```