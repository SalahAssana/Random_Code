Here is the CUDA code for K-Means Clustering:
```
#include <cuda_runtime.h>
#include <iostream>
#include <cmath>

// Structure to hold cluster information
struct Cluster {
    int id;
    float* center;
    int size;
};

__global__ void kmeansKernel(float* data, int* labels, int numPoints, int numClusters, float* centers, int* sizes) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= numPoints) return;

    // Calculate the distance to each center
    float minDist = FLT_MAX;
    int closestCluster = -1;
    for (int i = 0; i < numClusters; i++) {
        float dist = 0.0f;
        for (int j = 0; j < 2; j++) { // Assuming 2D data
            dist += pow(data[idx*2 + j] - centers[i*2], 2);
        }
        if (dist < minDist) {
            minDist = dist;
            closestCluster = i;
        }
    }

    atomicAdd(&sizes[closestCluster], 1);
    labels[idx] = closestCluster;
}

int main() {
    // Synthetic data
    int numPoints = 1000;
    float* data = new float[numPoints * 2]; // Assuming 2D data
    for (int i = 0; i < numPoints; i++) {
        data[i*2] = (float)i / 10.0f + sin((float)i / 5.0f);
        data[i*2 + 1] = (float)i / 20.0f + cos((float)i / 3.0f);
    }

    // K-Means parameters
    int numClusters = 5;
    float* centers = new float[numClusters * 2]; // Assuming 2D data
    for (int i = 0; i < numClusters; i++) {
        centers[i*2] = (float)i / numPoints + sin((float)i / numPoints);
        centers[i*2 + 1] = (float)i / numPoints + cos((float)i / numPoints);
    }
    int* sizes = new int[numClusters];

    // Allocate memory on GPU
    float* d_data;
    cudaMalloc((void**)&d_data, sizeof(float) * numPoints * 2);

    int* d_labels;
    cudaMalloc((void**)&d_labels, sizeof(int) * numPoints);

    float* d_centers = centers;
    int* d_sizes = sizes;

    // Copy data to GPU
    cudaMemcpy(d_data, data, sizeof(float) * numPoints * 2, cudaMemcpyHostToDevice);
    cudaMemcpy(d_labels, &labels[0], sizeof(int) * numPoints, cudaMemcpyHostToDevice);

    // Run K-Means algorithm
    int blockSize = 256;
    int numBlocks = (numPoints + blockSize - 1) / blockSize;
    kmeansKernel<<<numBlocks, blockSize>>>(d_data, d_labels, numPoints, numClusters, d_centers, d_sizes);

    cudaDeviceSynchronize();

    // Copy results from GPU
    cudaMemcpy(&labels[0], d_labels, sizeof(int) * numPoints, cudaMemcpyDeviceToHost);

    // Print results
    for (int i = 0; i < numPoints; i++) {
        std::cout << labels[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```