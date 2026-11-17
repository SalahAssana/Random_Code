Here is the CUDA code for the 3D Ray Tracing Engine:

```c
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

// Structure to represent a ray
struct Ray {
    float origin[3];
    float direction[3];
};

// Structure to represent a triangle
struct Triangle {
    float vertices[9]; // 3D coordinates of the 3 vertices
};

// Function to check if a point is inside a triangle
__device__ bool InsideTriangle(float *point, float *vertex1, float *vertex2, float *vertex3) {
    float v0v1 = vertex2[0] - vertex1[0];
    float v0v2 = vertex3[0] - vertex1[0];
    float v01x = point[0] - vertex1[0];
    float v01y = point[1] - vertex1[1];
    float v01z = point[2] - vertex1[2];

    bool b1 = (v01x > 0) ? (v01x > v0v1) : ((v01x < 0) ? (v01x < v0v1) : true);
    bool b2 = (v01y > 0) ? (v01y > v0v2 - v0v1) : ((v01y < 0) ? (v01y < v0v2 - v0v1) : true);
    bool b3 = (v01z > 0) ? (v01z > v0v3 - v0v2 - v0v1) : ((v01z < 0) ? (v01z < v0v3 - v0v2 - v0v1) : true);

    return b1 && b2 && b3;
}

// Kernel to perform ray tracing
__global__ void RayTracingKernel(float *scene, float *lightPosition, float *cameraPosition, float *rayOrigin, float *rayDirection, float *result) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < 1024) { // Assuming a small number of rays
        Ray ray;
        ray.origin[0] = rayOrigin[idx * 3];
        ray.origin[1] = rayOrigin[idx * 3 + 1];
        ray.origin[2] = rayOrigin[idx * 3 + 2];

        ray.direction[0] = rayDirection[idx * 3];
        ray.direction[1] = rayDirection[idx * 3 + 1];
        ray.direction[2] = rayDirection[idx * 3 + 2];

        float closestDistance = FLT_MAX;
        for (int i = 0; i < 1024; i++) { // Assuming a small number of triangles
            Triangle triangle;
            triangle.vertices[0] = scene[i * 9];
            triangle.vertices[1] = scene[i * 9 + 3];
            triangle.vertices[2] = scene[i * 9 + 6];

            triangle.vertices[3] = scene[i * 9 + 1];
            triangle.vertices[4] = scene[i * 9 + 4];
            triangle.vertices[5] = scene[i * 9 + 7];

            triangle.vertices[6] = scene[i * 9 + 2];
            triangle.vertices[7] = scene[i * 9 + 5];
            triangle.vertices[8] = scene[i * 9 + 8];

            float distance = FLT_MAX;
            if (InsideTriangle(ray.origin, &triangle.vertices[0], &triangle.vertices[3], &triangle.vertices[6])) {
                distance = sqrtf(powf(triangle.vertices[0] - ray.origin[0], 2) +
                    powf(triangle.vertices[1] - ray.origin[1], 2) +
                    powf(triangle.vertices[2] - ray.origin[2], 2));
            }

            if (distance < closestDistance) {
                closestDistance = distance;
            }
        }

        result[idx] = closestDistance;
    }
}

int main() {
    int numRays = 1024;
    float *rayOrigin, *rayDirection;

    // Allocate memory on host
    cudaMalloc((void **)&rayOrigin, sizeof(float) * numRays * 3);
    cudaMalloc((void **)&rayDirection, sizeof(float) * numRays * 3);

    // Initialize data
    for (int i = 0; i < numRays; i++) {
        rayOrigin[i * 3] = rand() / (float)RAND_MAX;
        rayOrigin[i * 3 + 1] = rand() / (float)RAND_MAX;
        rayOrigin[i * 3 + 2] = rand() / (float)RAND_MAX;

        rayDirection[i * 3] = sin((i + 1) * M_PI / 180);
        rayDirection[i * 3 + 1] = cos((i + 1) * M_PI / 180);
        rayDirection[i * 3 + 2] = 0;
    }

    // Run kernel
    int blockSize = 256;
    int gridSize = (numRays + blockSize - 1) / blockSize;

    float *scene, *lightPosition, *cameraPosition, *result;
    cudaMalloc((void **)&scene, sizeof(float) * 1024 * 9);
    cudaMalloc((void **)&lightPosition, sizeof(float) * 3);
    cudaMalloc((void **)&cameraPosition, sizeof(float) * 3);
    cudaMalloc((void **)&result, sizeof(float) * numRays);

    // Initialize data
    for (int i = 0; i < 1024; i++) {
        scene[i * 9] = rand() / (float)RAND_MAX;
        scene[i * 9 + 1] = rand() / (float)RAND_MAX;
        scene[i * 9 + 2] = rand() / (float)RAND_MAX;

        scene[i * 9 + 3] = rand() / (float)RAND_MAX;
        scene[i * 9 + 4] = rand() / (float)RAND_MAX;
        scene[i * 9 + 5] = rand() / (float)RAND_MAX;

        scene[i * 9 + 6] = rand() / (float)RAND_MAX;
        scene[i * 9 + 7] = rand() / (float)RAND_MAX;
        scene[i * 9 + 8] = rand() / (float)RAND_MAX;
    }

    lightPosition[0] = 1.0f; lightPosition[1] = 2.0f; lightPosition[2] = 3.0f;
    cameraPosition[0] = 0.0f; cameraPosition[1] = 0.0f; cameraPosition[2] = 4.0f;

    RayTracingKernel<<<gridSize, blockSize>>>(scene, lightPosition, cameraPosition, rayOrigin, rayDirection, result);

    cudaDeviceSynchronize();

    // Copy result back to host
    float *hostResult;
    hostResult = (float *)malloc(sizeof(float) * numRays);
    cudaMemcpy(hostResult, result, sizeof(float) * numRays, cudaMemcpyDeviceToHost);

    // Print results
    for (int i = 0; i < numRays; i++) {
        printf("Ray %d: %f\n", i, hostResult[i]);
    }

    free(hostResult);
    cudaFree(scene);
    cudaFree(lightPosition);
    cudaFree(cameraPosition);
    cudaFree(result);
    cudaFree(rayOrigin);
    cudaFree(rayDirection);

    return 0;
}
```