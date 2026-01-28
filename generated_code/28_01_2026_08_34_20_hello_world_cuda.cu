#include <stdio.h>
#include <cuda_runtime.h>

__global__ void printHelloWorld(char* message) {
    int idx = threadIdx.x;
    if (idx == 0) {
        // The first thread in each block prints the entire message
        for (int i = 0; i < strlen(message); i++) {
            printf("%c", message[i]);
        }
        printf("\n");
    }
}

int main() {
    char* message = "Hello, World!";
    int messageLength = strlen(message);

    // Allocate memory on the host
    char* h_message;
    cudaMallocHost((void**)&h_message, messageLength + 1);

    // Copy the message to the device
    cudaMemcpy(h_message, message, messageLength + 1, cudaMemcpyHostToDevice);

    // Launch the kernel
    int numThreads = 1024;
    int numBlocks = (messageLength + numThreads - 1) / numThreads;
    printHelloWorld<<<numBlocks, numThreads>>>(h_message);

    // Synchronize threads
    cudaDeviceSynchronize();

    // Print the message on the host
    printf("Host: ");
    for (int i = 0; i < messageLength; i++) {
        printf("%c", h_message[i]);
    }
    printf("\n");

    // Free memory on the host and device
    cudaFreeHost(h_message);
    return 0;
}