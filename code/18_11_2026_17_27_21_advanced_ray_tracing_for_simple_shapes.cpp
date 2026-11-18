#include <iostream>
#include <vector>
#include <cmath>

// Simple Shape Class
class Shape {
public:
    virtual float intersect(const float* rayOrigin, const float* rayDirection) = 0;
};

// Sphere Class
class Sphere : public Shape {
private:
    float radius;
    float x, y, z;

public:
    Sphere(float r, float cx, float cy, float cz) : radius(r), x(cx), y(cy), z(cz) {}

    float intersect(const float* rayOrigin, const float* rayDirection) override {
        // Calculate the distance from the origin of the ray to the center of the sphere
        float a = dot(rayOrigin, rayOrigin);
        float b = 2 * (dot(rayOrigin, rayDirection));
        float c = dot(rayDirection, rayDirection) - 1;

        // Solve the quadratic equation for t
        float t0 = (-b - sqrt(b*b - 4*a*c)) / (2*a);
        float t1 = (-b + sqrt(b*b - 4*a*c)) / (2*a);

        // Check if the intersection is valid (i.e., within the bounds of the ray)
        if (t0 < 0 && t1 < 0) return FLT_MAX;
        if (t0 > 0 && t1 < 0) return t0;
        if (t0 < 0 && t1 > 0) return t1;

        // Calculate the intersection point
        float3 intersectionPoint;
        intersectionPoint.x = rayOrigin[0] + t1 * rayDirection[0];
        intersectionPoint.y = rayOrigin[1] + t1 * rayDirection[1];
        intersectionPoint.z = rayOrigin[2] + t1 * rayDirection[2];

        // Check if the intersection point is within the bounds of the sphere
        float distanceSquared = pow(intersectionPoint.x - x, 2) + pow(intersectionPoint.y - y, 2) + pow(intersectionPoint.z - z, 2);
        return (distanceSquared < radius*radius ? t1 : FLT_MAX);
    }

    // Helper function to calculate the dot product of two vectors
    float dot(const float* v1, const float* v2) {
        return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
    }
};

// Box Class
class Box : public Shape {
private:
    float width, height, depth;
    float x, y, z;

public:
    Box(float w, float h, float d, float cx, float cy, float cz) : width(w), height(h), depth(d), x(cx), y(cy), z(cz) {}

    float intersect(const float* rayOrigin, const float* rayDirection) override {
        // Calculate the distance from the origin of the ray to the center of the box
        float a = dot(rayOrigin, rayOrigin);
        float b = 2 * (dot(rayOrigin, rayDirection));
        float c = dot(rayDirection, rayDirection) - 1;

        // Solve the quadratic equation for t
        float t0 = (-b - sqrt(b*b - 4*a*c)) / (2*a);
        float t1 = (-b + sqrt(b*b - 4*a*c)) / (2*a);

        // Check if the intersection is valid (i.e., within the bounds of the ray)
        if (t0 < 0 && t1 < 0) return FLT_MAX;
        if (t0 > 0 && t1 < 0) return t0;
        if (t0 < 0 && t1 > 0) return t1;

        // Calculate the intersection point
        float3 intersectionPoint;
        intersectionPoint.x = rayOrigin[0] + t1 * rayDirection[0];
        intersectionPoint.y = rayOrigin[1] + t1 * rayDirection[1];
        intersectionPoint.z = rayOrigin[2] + t1 * rayDirection[2];

        // Check if the intersection point is within the bounds of the box
        float minx, maxx, miny, maxy, minz, maxz;
        minx = x; maxx = x + width;
        miny = y; maxy = y + height;
        minz = z; maxz = z + depth;

        if (intersectionPoint.x < minx || intersectionPoint.x > maxx ||
            intersectionPoint.y < miny || intersectionPoint.y > maxy ||
            intersectionPoint.z < minz || intersectionPoint.z > maxz) {
            return FLT_MAX;
        }

        // Calculate the distance from the intersection point to the center of the box
        float distanceSquared = pow(intersectionPoint.x - x, 2) + pow(intersectionPoint.y - y, 2) + pow(intersectionPoint.z - z, 2);

        return (distanceSquared < (width*0.5)*(width*0.5) ? t1 : FLT_MAX);
    }
};

// CUDA Kernel
__global__ void rayTrace(float* image, float3* objects, int numObjects, float3* rays, int numRays) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < numRays) {
        float3 ray = rays[idx];
        for (int i = 0; i < numObjects; i++) {
            Shape* shape = &objects[i];
            if (shape->intersect(ray)) {
                // Set the pixel color based on the object's material
                image[3 * idx + 0] = 1.0f;
                image[3 * idx + 1] = 0.5f;
                image[3 * idx + 2] = 0.25f;
            }
        }
    }
}

int main() {
    // Initialize the CUDA device
    cudaDeviceInit();

    // Define the objects and rays
    int numObjects = 2;
    float3* objects = new float3[numObjects];
    for (int i = 0; i < numObjects; i++) {
        if (i == 0) {
            Shape* sphere = new Sphere(1.0f, 0.5f, 0.5f, 0.5f);
            objects[i] = {sphere->x, sphere->y, sphere->z};
        } else {
            Shape* box = new Box(2.0f, 2.0f, 1.0f, -1.0f, -1.0f, -1.0f);
            objects[i] = {box->x, box->y, box->z};
        }
    }
    int numRays = 10000;
    float3* rays = new float3[numRays];
    for (int i = 0; i < numRays; i++) {
        rays[i].x = (float)rand() / RAND_MAX - 1.0f;
        rays[i].y = (float)rand() / RAND_MAX - 1.0f;
        rays[i].z = (float)rand() / RAND_MAX - 1.0f;
    }

    // Allocate memory on the GPU
    float* image = new float[3 * numRays];
    cudaMalloc((void**)&image, 3 * numRays * sizeof(float));

    // Launch the CUDA kernel
    int blockSize = 256;
    int numBlocks = (numRays + blockSize - 1) / blockSize;
    rayTrace<<<numBlocks, blockSize>>>(image, objects, numObjects, rays, numRays);

    // Synchronize and retrieve the results
    cudaDeviceSynchronize();
    float* imageGPU;
    cudaMalloc((void**)&imageGPU, 3 * numRays * sizeof(float));
    cudaMemcpy(imageGPU, image, 3 * numRays * sizeof(float), cudaMemcpyDeviceToHost);

    // Print the resulting image
    for (int i = 0; i < numRays; i++) {
        printf("%f %f %f\n", imageGPU[3*i+0], imageGPU[3*i+1], imageGPU[3*i+2]);
    }

    // Clean up
    cudaFree(image);
    delete[] objects;
    delete[] rays;
    return 0;
}
