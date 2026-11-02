#include <cuda_runtime.h>
#include <curand_kernel.h>

// Structure to hold scene data
struct Scene {
    float* materials; // Array of material indices
    float3* positions; // Array of object positions
    float3* directions; // Array of object directions
    int numObjects;
};

// Structure to hold ray data
struct Ray {
    float3 origin;
    float3 direction;
    int materialIndex;
};

// Helper function to calculate reflection vector
__device__ float3 reflect(float3 incoming, float3 normal) {
    return incoming - 2 * dot(incoming, normal) * normal;
}

// Helper function to calculate refraction vector
__device__ float3 refract(float3 incoming, float3 normal, float n1, float n2) {
    float cosI = dot(incoming, normal);
    float sinI = sqrt(1 - cosI * cosI);
    float sinT2 = n1 * n1 * (1 - cosI * cosI);
    float cosT = sqrt(1 - sinT2);
    return (n1 * incoming + (n2 * cosI - n1 * cosT) / (n2 * sinI + n1 * cosT));
}

// Helper function to calculate shadow ray
__device__ float3 castShadow(float3 position, float3 direction, float3 lightPosition, float materialIndex) {
    Ray ray;
    ray.origin = position;
    ray.direction = direction;
    ray.materialIndex = materialIndex;

    // Initialize and sample the scene
    curandState state;
    int seed = (int)materialIndex;
    curand_init(seed, 0, 1, &state);
    float3 intersection = curand_next_intersection(&state);

    if (intersection.x == -FLT_MAX) {
        return lightPosition; // No intersection found
    }

    return intersection;
}

// Kernel to perform ray tracing
__global__ void traceRay(float* pixels, Scene scene, int width, int height, float3 cameraPosition, float3 cameraDirection) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x >= width || y >= height) return; // Out of bounds

    Ray ray;
    ray.origin = make_float3(cameraPosition);
    ray.direction = normalize(make_float3(cameraDirection));
    ray.materialIndex = 0; // Default material index

    float3 intersection = make_float3(FLT_MAX, FLT_MAX, FLT_MAX);

    for (int i = 0; i < scene.numObjects; i++) {
        if (isoccluded(scene.positions[i], scene.directions[i], &ray, &intersection)) continue;

        // Calculate material properties
        float3 normal = normalize(intersection - scene.positions[i]);
        float reflectivity = 1.0f;
        float transparency = 0.5f; // Default transparency

        if (i < 2) { // First two objects have different materials
            reflectivity = 0.8f;
            transparency = 0.2f;
        }

        // Perform lighting calculation
        float3 lightPosition = make_float3(1, 1, 1);
        float3 lightDirection = normalize(lightPosition - intersection);
        float3 diffuse = max(dot(normal, lightDirection), 0) * reflectivity;

        if (transparency > 0.5f) {
            // Perform shadow ray calculation
            float3 shadowPosition = castShadow(intersection, lightDirection, lightPosition, i);
            float3 shadowNormal = normalize(shadowPosition - intersection);
            diffuse *= max(dot(shadowNormal, lightDirection), 0);

            if (diffuse.x < 1.0f) {
                // Perform refraction calculation
                float n1 = 1.5f;
                float n2 = 1.3f;
                float3 refracted = refract(lightDirection, shadowNormal, n1, n2);
                diffuse += max(dot(refracted, normal), 0);

                if (diffuse.x > 1.0f) {
                    // Perform reflection calculation
                    float3 reflected = reflect(lightDirection, shadowNormal);
                    diffuse += max(dot(reflected, normal), 0);
                }
            }
        }

        // Update pixel color
        pixels[y * width + x] = make_float4(diffuse.x, diffuse.y, diffuse.z, 1.0f);
    }
}

int main() {
    int width = 512;
    int height = 512;

    // Initialize the scene and materials
    Scene scene;
    float* materials = (float*)malloc(width * height * sizeof(float));
    float3* positions = (float3*)malloc(6 * sizeof(float3));
    float3* directions = (float3*)malloc(6 * sizeof(float3));

    for (int i = 0; i < 2; i++) {
        positions[i] = make_float3(-1.5f + i * 3.0f, -0.5f, 0);
        directions[i] = normalize(make_float3(0, 1, 0));
    }

    for (int i = 2; i < 4; i++) {
        positions[i] = make_float3(-1.5f + (i - 2) * 3.0f, 0.5f, 0);
        directions[i] = normalize(make_float3(0, -1, 0));
    }

    scene.materials = materials;
    scene.positions = positions;
    scene.directions = directions;
    scene.numObjects = 4;

    // Initialize the pixel array
    float* pixels = (float*)malloc(width * height * sizeof(float));

    // Launch the kernel
    int blockSize = 16;
    int gridSizeX = (width + blockSize - 1) / blockSize;
    int gridSizeY = (height + blockSize - 1) / blockSize;

    traceRay<<<gridSizeX, gridSizeY>>>(pixels, scene, width, height, make_float3(0, 0, -5), normalize(make_float3(0, 0, 1)));

    // Synchronize the kernel
    cudaDeviceSynchronize();

    // Print the pixel array
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf("%.4f ", pixels[y * width + x]);
        }
        printf("\n");
    }

    return 0;
}