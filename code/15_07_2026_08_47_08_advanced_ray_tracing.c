#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure for 3D vectors
typedef struct {
    float x;
    float y;
    float z;
} Vec3;

// Function to calculate the distance between two points
float distance(Vec3 a, Vec3 b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
}

// Structure for a sphere
typedef struct {
    Vec3 center;
    float radius;
} Sphere;

// Structure for a light source
typedef struct {
    Vec3 position;
    float intensity;
} Light;

// Function to calculate the color of a pixel
Vec3 ray_trace(Vec3 camera, Vec3 direction, Vec3 *spheres, int num_spheres, Light light) {
    Vec3 intersection_point = camera;
    for (int i = 0; i < num_spheres; i++) {
        Sphere sphere = spheres[i];
        float distance_to_sphere = distance(intersection_point, sphere.center);
        if (distance_to_sphere <= sphere.radius) {
            // Calculate the color of the pixel
            Vec3 normal = normalize(Vec3Subtract(sphere.center, intersection_point));
            float dot_product = dot(normal, direction);
            if (dot_product > 0.5f) {
                return Vec3Make(light.intensity * 255, light.intensity * 255, light.intensity * 255);
            } else {
                return Vec3Make(0, 0, 0);
            }
        }
    }
    // If no intersection is found, return a black pixel
    return Vec3Make(0, 0, 0);
}

int main() {
    int width = 800;
    int height = 600;

    // Initialize the camera position and direction
    Vec3 camera = Vec3Make(-5.0f, 2.0f, -10.0f);
    Vec3 direction = Vec3Normalize(Vec3Subtract(Vec3Make(0.0f, 0.0f, 0.0f), camera));

    // Initialize the spheres
    Sphere spheres[4];
    spheres[0].center = Vec3Make(-2.0f, -1.5f, 0.0f);
    spheres[0].radius = 1.0f;
    spheres[1].center = Vec3Make(2.0f, -1.5f, 0.0f);
    spheres[1].radius = 1.0f;
    spheres[2].center = Vec3Make(-2.0f, 1.5f, 0.0f);
    spheres[2].radius = 1.0f;
    spheres[3].center = Vec3Make(2.0f, 1.5f, 0.0f);
    spheres[3].radius = 1.0f;

    // Initialize the light source
    Light light;
    light.position = Vec3Make(-4.0f, -2.0f, 0.0f);
    light.intensity = 100.0f;

    // Create an image buffer
    Vec3 *image = malloc(width * height * sizeof(Vec3));
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = y * width + x;
            Vec3 pixel_color = ray_trace(camera, direction, spheres, 4, light);
            image[index].x = pixel_color.x / 255.0f;
            image[index].y = pixel_color.y / 255.0f;
            image[index].z = pixel_color.z / 255.0f;
        }
    }

    // Write the image to a file
    FILE *file = fopen("image.ppm", "wb");
    fprintf(file, "P3\n");
    fprintf(file, "%d %d\n", width, height);
    fprintf(file, "255\n");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = y * width + x;
            Vec3 pixel_color = image[index];
            fprintf(file, "%d %d %d ", (int)pixel_color.x * 255.0f, (int)pixel_color.y * 255.0f, (int)pixel_color.z * 255.0f);
        }
        fprintf(file, "\n");
    }
    fclose(file);

    // Free the image buffer
    free(image);

    return 0;
}

// Helper functions for vector operations
Vec3 Vec3Add(Vec3 a, Vec3 b) {
    return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

Vec3 Vec3Subtract(Vec3 a, Vec3 b) {
    return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

float dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 normalize(Vec3 vector) {
    float length = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
    return (Vec3){vector.x / length, vector.y / length, vector.z / length};
}