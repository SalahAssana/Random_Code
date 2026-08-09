Here is the CUDA code for K-Means Clustering:
```
#include <cuda_runtime.h>
#include <device_launch_configuration.h>

// Define constants
#define NUM_CLUSTERS 5
#define DATA_SIZE 1000
#define ITERATIONS 10

// Data structure to hold cluster information
struct Cluster {
    float* centroids;
    int* membership;
};

// Kernel function for K-Means Clustering
__global__ void kmeansKernel(float* data, int* labels, float* newCentroids, int numPoints, int numFeatures) {
    __shared__ float sharedData[256];
    __shared__ int sharedLabels[256];

    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index >= numPoints) return;

    // Calculate distance from each point to centroids
    float minDist = FLT_MAX;
    int closestCluster = -1;
    for (int i = 0; i < NUM_CLUSTERS; ++i) {
        float dist = 0.0f;
        for (int j = 0; j < numFeatures; ++j) {
            dist += pow(data[index * numFeatures + j] - newCentroids[i * numFeatures], 2);
        }
        if (dist < minDist) {
            minDist = dist;
            closestCluster = i;
        }
    }

    // Update cluster membership
    labels[index] = closestCluster;

    // Synchronize threads
    __syncthreads();

    // Calculate new centroids
    for (int i = 0; i < NUM_CLUSTERS; ++i) {
        int sumX = 0, sumY = 0;
        int count = 0;
        for (int j = 0; j < numPoints; ++j) {
            if (labels[j] == i) {
                sumX += data[j * numFeatures];
                sumY += data[j * numFeatures + 1];
                count++;
            }
        }
        newCentroids[i * numFeatures] = (float)sumX / count;
        newCentroids[i * numFeatures + 1] = (float)sumY / count;
    }
}

// Host function to launch kernel and perform K-Means Clustering
void kmeans(float* data, int* labels, float* centroids, int numPoints, int numFeatures) {
    // Allocate memory on host and device
    float* newCentroids = (float*)malloc(NUM_CLUSTERS * numFeatures * sizeof(float));
    int* d_labels;
    cudaMalloc((void**)&d_labels, numPoints * sizeof(int));

    // Copy data to device
    cudaMemcpy(d_labels, labels, numPoints * sizeof(int), cudaMemcpyHostToDevice);

    // Launch kernel
    int blockSize = 256;
    int gridSize = (numPoints + blockSize - 1) / blockSize;
    kmeansKernel<<<gridSize, blockSize>>>(data, d_labels, newCentroids, numPoints, numFeatures);

    // Synchronize threads
    cudaDeviceSynchronize();

    // Copy results back to host
    cudaMemcpy(labels, d_labels, numPoints * sizeof(int), cudaMemcpyDeviceToHost);

    // Free memory
    free(newCentroids);
    cudaFree(d_labels);
}

int main() {
    // Synthetic data generation
    float* data = (float*)malloc(DATA_SIZE * 2 * sizeof(float));
    for (int i = 0; i < DATA_SIZE; ++i) {
        data[i * 2] = rand() / (float)RAND_MAX;
        data[i * 2 + 1] = rand() / (float)RAND_MAX;
    }

    // Initialize cluster membership
    int* labels = (int*)malloc(DATA_SIZE * sizeof(int));
    for (int i = 0; i < DATA_SIZE; ++i) {
        labels[i] = -1;
    }

    // Perform K-Means Clustering
    float* centroids = (float*)malloc(NUM_CLUSTERS * 2 * sizeof(float));
    for (int i = 0; i < NUM_CLUSTERS; ++i) {
        centroids[i * 2] = rand() / (float)RAND_MAX;
        centroids[i * 2 + 1] = rand() / (float)RAND_MAX;
    }
    kmeans(data, labels, centroids, DATA_SIZE, 2);

    // Print results
    for (int i = 0; i < DATA_SIZE; ++i) {
        printf("%f %f %d\n", data[i * 2], data[i * 2 + 1], labels[i]);
    }

    // Free memory
    free(data);
    free(labels);
    free(centroids);

    return 0;
}
```