Here is the C code for the 3D Rendering Engine:

```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define some constants
#define WIDTH 640
#define HEIGHT 480
#define MAX_OBJECTS 1000
#define MAX_LIGHTS 10

// Structure to represent a 3D object
typedef struct {
    float x, y, z; // Position
    float rx, ry, rz; // Rotation
    float sx, sy, sz; // Scale
} Object;

// Structure to represent a light source
typedef struct {
    float x, y, z; // Position
    float intensity; // Intensity of the light
} Light;

// Function to calculate the normal vector of an object at a given point
float* calcNormal(Object* obj, float* point) {
    float epsilon = 0.0001;
    float dx = (obj->rx == 0) ? 1 : cos(obj->ry);
    float dy = (obj->ry == 0) ? 1 : sin(obj->ry) / cos(obj->ry);
    float dz = (obj->rz == 0) ? 1 : sin(obj->ry);

    float epx = point[0] + epsilon * dx;
    float epy = point[1] + epsilon * dy;
    float epz = point[2] + epsilon * dz;

    float* n = (float*)malloc(3 * sizeof(float));
    n[0] = (epx - point[0]) / epsilon;
    n[1] = (epy - point[1]) / epsilon;
    n[2] = (epz - point[2]) / epsilon;

    return n;
}

// Function to calculate the intersection of a ray with an object
int intersect(Object* obj, float* origin, float* direction, float* t) {
    // Calculate the bounding box of the object
    float minx = obj->x - obj->sx;
    float maxx = obj->x + obj->sx;
    float miny = obj->y - obj->sy;
    float maxy = obj->y + obj->sy;
    float minz = obj->z - obj->sz;
    float maxz = obj->z + obj->sz;

    // Calculate the ray's bounding box
    float rx = origin[0] - (direction[0] * t);
    float ry = origin[1] - (direction[1] * t);
    float rz = origin[2] - (direction[2] * t);

    if ((rx < minx || rx > maxx) && (ry < miny || ry > maxy) && (rz < minz || rz > maxz)) {
        return 0; // Ray misses the object
    }

    // Calculate the normal vector of the object at the intersection point
    float* n = calcNormal(obj, origin);
    float dotProduct = n[0] * direction[0] + n[1] * direction[1] + n[2] * direction[2];

    if (dotProduct > 0) {
        return 1; // Ray hits the object
    } else {
        return -1; // Ray is behind the object
    }
}

// Function to render a scene using ray tracing
void render(float* image, Object objects[], Light lights[]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            float px = (float)x / WIDTH - 1;
            float py = (float)y / HEIGHT - 1;

            // Calculate the ray direction
            float dirx = px * 2.0f;
            float diry = py * 2.0f;
            float dirz = sqrt(1.0f - (dirx * dirx + diry * diry));

            float* origin = (float*)malloc(3 * sizeof(float));
            origin[0] = 0; origin[1] = 0; origin[2] = 0;
            float* direction = (float*)malloc(3 * sizeof(float));
            direction[0] = dirx; direction[1] = diry; direction[2] = dirz;

            // Calculate the intersection of the ray with each object
            for (int i = 0; i < MAX_OBJECTS; i++) {
                if (intersect(&objects[i], origin, direction, &t)) {
                    // Perform shading and lighting calculations
                    float* normal = calcNormal(&objects[i], origin);
                    float diffuse = dotProduct(normal[0], lights[i].intensity);

                    image[(y * WIDTH) + x] = (float)(diffuse * 255.0f);
                }
            }

            free(origin); free(direction);
        }
    }
}

// Main function
int main() {
    // Define some sample objects and lights
    Object objects[MAX_OBJECTS];
    Light lights[MAX_LIGHTS];

    for (int i = 0; i < MAX_OBJECTS; i++) {
        objects[i].x = (float)i * 2.0f;
        objects[i].y = 0;
        objects[i].z = 0;
        objects[i].rx = 0;
        objects[i].ry = 0;
        objects[i].rz = 0;
        objects[i].sx = 1;
        objects[i].sy = 1;
        objects[i].sz = 1;
    }

    for (int i = 0; i < MAX_LIGHTS; i++) {
        lights[i].x = (float)i * 10.0f;
        lights[i].y = 5;
        lights[i].z = 0;
        lights[i].intensity = 1.0f / (i + 1);
    }

    // Render the scene
    float* image = (float*)malloc(HEIGHT * WIDTH * sizeof(float));
    render(image, objects, lights);

    // Display the rendered image
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%f ", image[(y * WIDTH) + x]);
        }
        printf("\n");
    }

    free(image);
    return 0;
}
```