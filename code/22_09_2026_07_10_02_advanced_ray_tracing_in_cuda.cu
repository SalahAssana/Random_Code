#include <iostream>
#include <vector>

__global__ void kernel(float* pixelData, float* rayDir, float* objPos, int width, int height) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= width * height)
        return;

    int y = idx / width;
    int x = idx % width;

    // Calculate camera position
    float camX = 0.0f;
    float camY = 0.0f;
    float camZ = -5.0f;

    // Calculate ray direction
    float dx = (float(x) + 0.5) * 2.0 / width - 1.0;
    float dy = (float(y) + 0.5) * 2.0 / height - 1.0;

    float d = sqrt(dx * dx + dy * dy);
    dx /= d;
    dy /= d;

    // Calculate distance from camera to object
    float dist = 1.0f;

    // Ray tracing
    for (int i = 0; i < 100; i++) {
        float t = dist / ((float)i + 1e-3);
        float ox = camX + dx * t;
        float oy = camY + dy * t;
        float oz = camZ - 5.0f;

        // Check for intersection
        if (ox > objPos[0] && ox < objPos[2] &&
            oy > objPos[1] && oy < objPos[3] &&
            oz > objPos[4] && oz < objPos[6]) {
            pixelData[idx] = 1.0f;
            return;
        }
    }

    // No intersection
    pixelData[idx] = 0.0f;
}

int main() {
    int width = 1024, height = 1024;

    float* pixelData;
    cudaMalloc((void**)&pixelData, sizeof(float) * width * height);

    float* rayDir = new float[width * height];
    for (int i = 0; i < width * height; i++) {
        rayDir[i] = 1.0f;
    }

    float* objPos = new float[8]; // x, y, z, x+dx, y+dy, z+dz
    objPos[0] = -2.0f; objPos[1] = -2.0f; objPos[2] = 2.0f;
    objPos[3] = 2.0f; objPos[4] = -2.0f; objPos[5] = 2.0f;
    objPos[6] = 2.0f; objPos[7] = 2.0f;

    dim3 blockSize(1024);
    dim3 gridSize(width, height);

    kernel<<<gridSize, blockSize>>>(pixelData, rayDir, objPos, width, height);

    cudaDeviceSynchronize();

    for (int i = 0; i < width * height; i++) {
        std::cout << pixelData[i] << " ";
    }

    delete[] rayDir;
    delete[] objPos;

    cudaFree(pixelData);
}
