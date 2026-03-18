Here is the CUDA code for the 3D Physics Simulator:

```cuda
#include <iostream>
#include <cmath>
#include <cuda_runtime.h>

// Define constants
#define WIDTH 256
#define HEIGHT 256
#define DEPTH 256
#define TIME_STEPS 1000
#define EPSILON 1e-6

// Structure to represent a particle
struct Particle {
    float position[3];
    float velocity[3];
    float mass;
};

__global__ void updateParticles(Particle* particles, int numParticles) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < numParticles) {
        // Calculate acceleration due to gravity
        float dx = particles[idx].position[0] - 128.0f;
        float dy = particles[idx].position[1] - 128.0f;
        float dz = particles[idx].position[2] - 128.0f;
        float distanceSquared = dx * dx + dy * dy + dz * dz;
        float gravity = (float)1.0 / (distanceSquared + EPSILON);

        // Update velocity and position
        for (int i = 0; i < TIME_STEPS; i++) {
            particles[idx].velocity[0] += gravity * (dx > 128.0f ? -1.0f : 1.0f) / (distanceSquared + EPSILON);
            particles[idx].velocity[1] += gravity * (dy > 128.0f ? -1.0f : 1.0f) / (distanceSquared + EPSILON);
            particles[idx].velocity[2] += gravity * (dz > 128.0f ? -1.0f : 1.0f) / (distanceSquared + EPSILON);

            particles[idx].position[0] += particles[idx].velocity[0];
            particles[idx].position[1] += particles[idx].velocity[1];
            particles[idx].position[2] += particles[idx].velocity[2];

            // Check for collisions with the boundary
            if (particles[idx].position[0] < 0.0f || particles[idx].position[0] > WIDTH) {
                particles[idx].velocity[0] = -particles[idx].velocity[0];
            }
            if (particles[idx].position[1] < 0.0f || particles[idx].position[1] > HEIGHT) {
                particles[idx].velocity[1] = -particles[idx].velocity[1];
            }
            if (particles[idx].position[2] < 0.0f || particles[idx].position[2] > DEPTH) {
                particles[idx].velocity[2] = -particles[idx].velocity[2];
            }
        }

        // Apply friction
        for (int i = 0; i < TIME_STEPS; i++) {
            float magnitude = sqrt(pow(particles[idx].velocity[0], 2.0f) + pow(particles[idx].velocity[1], 2.0f) + pow(particles[idx].velocity[2], 2.0f));
            particles[idx].velocity[0] *= (float)(1.0f - 0.05f);
            particles[idx].velocity[1] *= (float)(1.0f - 0.05f);
            particles[idx].velocity[2] *= (float)(1.0f - 0.05f);

            // Normalize velocity
            magnitude = sqrt(pow(particles[idx].velocity[0], 2.0f) + pow(particles[idx].velocity[1], 2.0f) + pow(particles[idx].velocity[2], 2.0f));
            particles[idx].velocity[0] /= magnitude;
            particles[idx].velocity[1] /= magnitude;
            particles[idx].velocity[2] /= magnitude;
        }
    }
}

int main() {
    // Create and copy particle data to the device
    Particle* particles = new Particle[WIDTH * HEIGHT * DEPTH];
    for (int i = 0; i < WIDTH * HEIGHT * DEPTH; i++) {
        particles[i].position[0] = (float)(rand() % WIDTH);
        particles[i].position[1] = (float)(rand() % HEIGHT);
        particles[i].position[2] = (float)(rand() % DEPTH);
        particles[i].velocity[0] = 0.0f;
        particles[i].velocity[1] = 0.0f;
        particles[i].velocity[2] = 0.0f;
        particles[i].mass = 1.0f;
    }
    Particle* d_particles;
    cudaMalloc((void**)&d_particles, sizeof(Particle) * WIDTH * HEIGHT * DEPTH);

    cudaMemcpy(d_particles, particles, sizeof(Particle) * WIDTH * HEIGHT * DEPTH, cudaMemcpyHostToDevice);

    // Launch kernel
    int numParticles = WIDTH * HEIGHT * DEPTH;
    int blockSize = 256;
    int gridSizeX = (numParticles + blockSize - 1) / blockSize;
    dim3 block(blockSize);
    dim3 grid(gridSizeX);
    updateParticles<<<grid, block>>>(d_particles, numParticles);

    // Synchronize kernel execution
    cudaDeviceSynchronize();

    // Copy results back to the host
    Particle* h_particles = new Particle[WIDTH * HEIGHT * DEPTH];
    cudaMemcpy(h_particles, d_particles, sizeof(Particle) * WIDTH * HEIGHT * DEPTH, cudaMemcpyDeviceToHost);

    // Print particle data
    for (int i = 0; i < numParticles; i++) {
        std::cout << "Particle " << i << ": ";
        for (int j = 0; j < 3; j++) {
            std::cout << h_particles[i].position[j] << " ";
        }
        std::cout << std::endl;
    }

    // Free memory
    cudaFree(d_particles);
    delete[] particles;
    delete[] h_particles;

    return 0;
}
```