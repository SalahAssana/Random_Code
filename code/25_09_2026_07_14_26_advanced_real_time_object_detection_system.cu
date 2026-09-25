Here is the CUDA code for the Real-time Object Detection System:
```
#include <iostream>
#include <cuda_runtime.h>

// Define the object detection structure
struct ObjectDetection {
    int x;
    int y;
    int width;
    int height;
    float confidence;
};

// Define the kernel function for object detection
__global__ void detectObjects(float* image, int* classes, int numClasses,
                                 int* boxes, int* classIds, float* scores) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < numClasses) {
        // Calculate the bounding box coordinates and class ID
        int x1 = boxes[idx] % 3;
        int y1 = boxes[idx] / 3;
        int x2 = (boxes[idx] % 3) + boxes[idx + 1] % 3;
        int y2 = (boxes[idx] / 3) + boxes[idx + 1] / 3;

        // Calculate the object detection results
        ObjectDetection objDetect;
        objDetect.x = x1;
        objDetect.y = y1;
        objDetect.width = x2 - x1;
        objDetect.height = y2 - y1;
        objDetect.confidence = scores[idx];

        // Store the object detection results in the output arrays
        classIds[0] = idx;
        boxes[0] = x1 * 3 + y1;
        scores[0] = objDetect.confidence;

        // Synchronize threads
        __syncthreads();
    }
}

int main() {
    int numClasses = 10;
    int numObjects = 5;

    // Allocate memory on the host and device for image data
    float* h_image = new float[1024 * 768 * 3];
    float* d_image;
    cudaMalloc((void**)&d_image, sizeof(float) * 1024 * 768 * 3);

    // Allocate memory on the host and device for class labels
    int* h_classes = new int[numClasses];
    int* d_classes;
    cudaMalloc((void**)&d_classes, sizeof(int) * numClasses);

    // Allocate memory on the host and device for bounding box coordinates
    int* h_boxes = new int[2 * numObjects];
    int* d_boxes;
    cudaMalloc((void**)&d_boxes, sizeof(int) * 2 * numObjects);

    // Allocate memory on the host and device for class IDs and scores
    int* h_classIds = new int[numObjects];
    float* h_scores = new float[numObjects];
    int* d_classIds;
    float* d_scores;
    cudaMalloc((void**)&d_classIds, sizeof(int) * numObjects);
    cudaMalloc((void**)&d_scores, sizeof(float) * numObjects);

    // Copy host memory to device memory
    cudaMemcpy(d_image, h_image, sizeof(float) * 1024 * 768 * 3,
               cudaMemcpyHostToDevice);
    cudaMemcpy(d_classes, h_classes, sizeof(int) * numClasses,
               cudaMemcpyHostToDevice);
    cudaMemcpy(d_boxes, h_boxes, sizeof(int) * 2 * numObjects,
               cudaMemcpyHostToDevice);

    // Launch the kernel function
    int blockSize = 256;
    int gridSize = (numClasses + blockSize - 1) / blockSize;
    detectObjects<<<gridSize, blockSize>>>(d_image, d_classes, numClasses,
                                            d_boxes, d_classIds, d_scores);

    // Copy device memory to host memory
    cudaMemcpy(h_classIds, d_classIds, sizeof(int) * numObjects,
               cudaMemcpyDeviceToHost);
    cudaMemcpy(h_scores, d_scores, sizeof(float) * numObjects,
               cudaMemcpyDeviceToHost);

    // Print the object detection results
    for (int i = 0; i < numObjects; i++) {
        std::cout << "Object " << i + 1 << ": ";
        std::cout << "Class ID: " << h_classIds[i] << ", Score: "
                  << h_scores[i] << std::endl;
    }

    // Free device memory
    cudaFree(d_image);
    cudaFree(d_classes);
    cudaFree(d_boxes);
    cudaFree(d_classIds);
    cudaFree(d_scores);

    // Free host memory
    delete[] h_image;
    delete[] h_classes;
    delete[] h_boxes;
    delete[] h_classIds;
    delete[] h_scores;

    return 0;
}
```