#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define constants for color values
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF

// Structure to represent a 3D point in space
typedef struct {
    float x, y, z;
} Vector3;

// Structure to represent a ray (line) in 3D space
typedef struct {
    Vector3 origin; // starting point of the ray
    Vector3 direction; // direction vector
} Ray;

// Function to generate a random vector
Vector3 generateRandomVector(float min, float max) {
    return (Vector3){(float)rand() / RAND_MAX * (max - min) + min,
                     (float)rand() / RAND_MAX * (max - min) + min,
                     (float)rand() / RAND_MAX * (max - min) + min};
}

// Function to calculate the intersection of a ray with a plane
Vector3 intersectRayPlane(Ray r, Vector3 normal, float distance) {
    Vector3 p = r.origin;
    Vector3 v = r.direction;

    // Calculate the dot product of the ray direction and the plane normal
    float dotProduct = (v.x * normal.x + v.y * normal.y + v.z * normal.z);

    // Check if the ray is parallel to the plane
    if (fabs(dotProduct) < 0.0001f) {
        return (Vector3){INFINITY, INFINITY, INFINITY}; // Ray is parallel, no intersection
    }

    // Calculate the distance from the origin to the intersection point
    float t = -dotProduct + distance / dotProduct;

    // Calculate the intersection point coordinates
    p.x += v.x * t;
    p.y += v.y * t;
    p.z += v.z * t;

    return p;
}

// Function to calculate the color of a pixel based on ray tracing
int getColorOfPixel(Vector3 point, Vector3 normal) {
    // Generate a random vector for the light direction
    Vector3 lightDirection = generateRandomVector(-1.0f, 1.0f);

    // Calculate the dot product of the light direction and the plane normal
    float lightDotProduct = (lightDirection.x * normal.x + lightDirection.y * normal.y + lightDirection.z * normal.z);

    // Check if the light is behind the surface
    if (fabs(lightDotProduct) < 0.0001f) {
        return RED; // No light, use red as default color
    }

    // Calculate the distance from the origin to the intersection point
    float t = -lightDotProduct;

    // Calculate the intersection point coordinates
    Vector3 intersectionPoint;
    intersectionPoint.x += normal.x * t;
    intersectionPoint.y += normal.y * t;
    intersectionPoint.z += normal.z * t;

    // Calculate the distance from the intersection point to the light source
    float distance = sqrtf((intersectionPoint.x - lightDirection.x) * (intersectionPoint.x - lightDirection.x) +
                            (intersectionPoint.y - lightDirection.y) * (intersectionPoint.y - lightDirection.y) +
                            (intersectionPoint.z - lightDirection.z) * (intersectionPoint.z - lightDirection.z));

    // Calculate the color based on the distance and light intensity
    int color = RED;
    if (distance < 5.0f) {
        color = GREEN; // Close to the light source, use green as default color
    }

    return color;
}

int main() {
    // Initialize random number generator
    srand(time(NULL));

    // Define a plane with normal and distance from origin
    Vector3 normal = (Vector3){0.0f, 0.0f, 1.0f};
    float distance = 10.0f;

    // Define a ray starting at the origin with direction to infinity
    Ray r = (Ray){(Vector3){0.0f, 0.0f, 0.0f}, generateRandomVector(-1.0f, 1.0f)};

    // Calculate the intersection point of the ray and plane
    Vector3 intersectionPoint = intersectRayPlane(r, normal, distance);

    // Calculate the color of the pixel at the intersection point
    int pixelColor = getColorOfPixel(intersectionPoint, normal);

    // Print the calculated pixel color
    printf("Pixel Color: %x\n", pixelColor);

    return 0;
}