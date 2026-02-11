#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure to represent a 3D point
typedef struct {
    float x, y, z;
} Vector;

// Function to calculate the distance between two points
float distance(Vector p1, Vector p2) {
    return sqrtf((p2.x - p1.x) * (p2.x - p1.x) + 
                 (p2.y - p1.y) * (p2.y - p1.y) + 
                 (p2.z - p1.z) * (p2.z - p1.z));
}

// Function to ray cast a 3D scene
void ray_cast(Vector camera, Vector direction, int width, int height, float* pixels) {
    // Calculate the viewing plane normal and offset
    Vector view_plane_normal = {direction.x, direction.y, -1.0f};
    float view_plane_offset = distance(camera, (Vector){camera.x + direction.x, camera.y + direction.y, 0.0f});

    // Initialize the pixel array
    for(int i = 0; i < height * width; i++) {
        pixels[i] = -1.0f;
    }

    // Cast rays and render the scene
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            // Calculate the ray origin and direction
            Vector ray_origin = {camera.x + (x - width / 2) * direction.x / (float)(width - 1), 
                                   camera.y + (y - height / 2) * direction.y / (float)(height - 1), 
                                   camera.z};
            Vector ray_direction = normalize(Vector{direction.x, direction.y, -0.5f});

            // Perform ray intersection and rendering
            float t = -1.0f;
            for(int i = 0; i < 100; i++) {
                Vector p = {ray_origin.x + i * ray_direction.x, 
                            ray_origin.y + i * ray_direction.y, 
                            ray_origin.z + i * ray_direction.z};
                if(distance(p, (Vector){0.0f, 0.0f, 0.0f}) < view_plane_offset) {
                    t = distance(p, camera);
                    break;
                }
            }

            // If a hit is found, render the pixel
            if(t > -1.0f) {
                int index = y * width + x;
                pixels[index] = t;
            }
        }
    }
}

// Function to normalize a vector
Vector normalize(Vector v) {
    float length = sqrtf(v.x * v.x + v.y * y + v.z * v.z);
    return (Vector){v.x / length, v.y / length, v.z / length};
}

int main() {
    // Initialize the camera position and direction
    Vector camera = {0.0f, 0.0f, -5.0f};
    Vector direction = {1.0f, 0.0f, 0.0f};

    // Set the image dimensions
    int width = 800;
    int height = 600;

    // Allocate memory for the pixel array
    float* pixels = (float*)malloc(width * height * sizeof(float));

    // Ray cast and render the scene
    ray_cast(camera, direction, width, height, pixels);

    // Print the rendered image
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            printf("%f ", pixels[i * width + j]);
        }
        printf("\n");
    }

    // Free memory
    free(pixels);

    return 0;
}