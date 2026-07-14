#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define some constants
#define WIDTH 800
#define HEIGHT 600
#define MAX_LIGHTS 5
#define MATERIALS_COUNT 3
#define RAY_MAX_DEPTH 10

typedef struct {
    float x, y, z;
} Vector;

typedef enum { DIFFUSE, SPECULAR } MaterialType;

typedef struct {
    MaterialType type;
    float diffuseReflectance;
    float specularReflectance;
    float specularity;
} Material;

typedef struct {
    float r, g, b;
    int materialId;
} Color;

// Function to calculate the normal vector of a triangle
Vector* triangleNormal(Vector v1, Vector v2, Vector v3) {
    Vector n = {(v2.y - v1.y)*(v3.z - v1.z) - (v2.z - v1.z)*(v3.y - v1.y),
                (v2.z - v1.z)*(v3.x - v1.x) - (v2.x - v1.x)*(v3.z - v1.z),
                (v2.x - v1.x)*(v3.y - v1.y) - (v2.y - v1.y)*(v3.x - v1.x)};
    return &n;
}

// Function to calculate the intersection of a ray with an object
int intersection(float* rayOrigin, float* rayDirection, Vector** objects, int objectsCount, Vector* result) {
    for(int i = 0; i < objectsCount; i++) {
        Vector objNormal = {objects[i]->normal.x, objects[i]->normal.y, objects[i]->normal.z};
        Vector objCenter = {objects[i]->center.x, objects[i]->center.y, objects[i]->center.z};
        float dist = (rayOrigin[0] - objCenter.x) * rayDirection[0] + 
                      (rayOrigin[1] - objCenter.y) * rayDirection[1] + 
                      (rayOrigin[2] - objCenter.z) * rayDirection[2];
        if(dist < 0.00001f) {
            float t = dist / (rayDirection[0]*objNormal.x + rayDirection[1]*objNormal.y + rayDirection[2]*objNormal.z);
            if(t > 0.00001f && t <= RAY_MAX_DEPTH) {
                result->x = objCenter.x + t * rayDirection[0];
                result->y = objCenter.y + t * rayDirection[1];
                result->z = objCenter.z + t * rayDirection[2];
                return 1;
            }
        }
    }
    return 0;
}

// Function to perform the actual ray tracing
void render(float* pixels, Vector** objects, int objectsCount, Material* materials, float* lights) {
    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            Vector origin = {(float)x - (WIDTH / 2), -(float)y - (HEIGHT / 2), 1};
            Vector direction = {cos((float)x/WIDTH * 2 * M_PI) , sin((float)y/HEIGHT * 2 * M_PI), 0};
            int hits = intersection(origin, direction, objects, objectsCount, &origin);
            if(hits) {
                Color c;
                // Calculate the final color based on material and lighting
                for(int i = 0; i < MAX_LIGHTS; i++) {
                    float distance = sqrt(pow((origin.x - lights[i*3+0]),2) + pow((origin.y - lights[i*3+1]),2) + pow((origin.z - lights[i*3+2]),2));
                    c.r += materials[objects[hits-1]->materialId].diffuseReflectance * (float)sqrt(pow((lights[i*3+0] - origin.x),2) + pow((lights[i*3+1] - origin.y),2) + pow((lights[i*3+2] - origin.z),2)) / distance;
                    c.g += materials[objects[hits-1]->materialId].diffuseReflectance * (float)sqrt(pow((lights[i*3+0] - origin.x),2) + pow((lights[i*3+1] - origin.y),2) + pow((lights[i*3+2] - origin.z),2)) / distance;
                    c.b += materials[objects[hits-1]->materialId].diffuseReflectance * (float)sqrt(pow((lights[i*3+0] - origin.x),2) + pow((lights[i*3+1] - origin.y),2) + pow((lights[i*3+2] - origin.z),2)) / distance;
                }
                // Calculate the final color based on material and lighting
                pixels[y * WIDTH + x].r = (c.r > 1.0f) ? 1.0f : c.r;
                pixels[y * WIDTH + x].g = (c.g > 1.0f) ? 1.0f : c.g;
                pixels[y * WIDTH + x].b = (c.b > 1.0f) ? 1.0f : c.b;
            } else {
                // Default color for background
                pixels[y * WIDTH + x].r = 0.2f;
                pixels[y * WIDTH + x].g = 0.3f;
                pixels[y * WIDTH + x].b = 0.4f;
            }
        }
    }
}

int main() {
    // Initialize the scene
    Vector* objects[5] = {&(Vector){-1, -1, -1}, &(Vector){1, -1, -1}, &(Vector){1, 1, -1}, &(Vector){-1, 1, -1}, &(Vector){0, 0, 0}};
    for(int i = 0; i < objectsCount; i++) {
        objects[i]->materialId = (i % MATERIALS_COUNT);
    }
    
    // Initialize the materials
    Material* materials = (Material*)malloc(sizeof(Material) * MATERIALS_COUNT);
    for(int i = 0; i < MATERIALS_COUNT; i++) {
        materials[i].type = DIFFUSE;
        materials[i].diffuseReflectance = (float)(i % 2 == 0 ? 0.5 : 0.8);
        materials[i].specularReflectance = (float)(i % 2 == 0 ? 0.3 : 0.6);
        materials[i].specularity = (float)(i % 2 == 0 ? 0.4 : 0.7);
    }
    
    // Initialize the lights
    float* lights = (float*)malloc(sizeof(float) * MAX_LIGHTS * 3);
    for(int i = 0; i < MAX_LIGHTS; i++) {
        lights[i*3+0] = (float)(i % 2 == 0 ? -1 : 1);
        lights[i*3+1] = (float)(i % 2 == 0 ? -1 : 1);
        lights[i*3+2] = (float)5;
    }
    
    // Initialize the pixels
    float* pixels = (float*)malloc(sizeof(float) * WIDTH * HEIGHT * 3);
    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            pixels[y * WIDTH + x].r = 0.2f;
            pixels[y * WIDTH + x].g = 0.3f;
            pixels[y * WIDTH + x].b = 0.4f;
        }
    }
    
    // Perform the ray tracing
    render(pixels, objects, objectsCount, materials, lights);
    
    // Display the result
    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            printf("%.2f %.2f %.2f\n", pixels[y * WIDTH + x].r, pixels[y * WIDTH + x].g, pixels[y * WIDTH + x].b);
        }
    }
    
    // Clean up
    free(lights);
    free(materials);
    free(pixels);
    return 0;
}