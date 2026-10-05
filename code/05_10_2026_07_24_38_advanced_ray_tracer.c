#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_DEPTH 10

// Structure to represent a 3D object (triangle)
typedef struct {
    float x1, y1, z1;
    float x2, y2, z2;
    float x3, y3, z3;
} Triangle;

// Function to calculate the intersection of a ray with a triangle
float intersect(Triangle t, float ox, float oy, float oz, float dx, float dy, float dz) {
    float v1x = t.x2 - t.x1;
    float v1y = t.y2 - t.y1;
    float v1z = t.z2 - t.z1;
    float v2x = t.x3 - t.x1;
    float v2y = t.y3 - t.y1;
    float v2z = t.z3 - t.z1;

    float p1x = ox - t.x1;
    float p1y = oy - t.y1;
    float p1z = oz - t.z1;
    float denominator = v1x * (v2y * p1z - v2z * p1y) + 
                        v1y * (v2z * p1x - v2x * p1z) + 
                        v1z * (v2x * p1y - v2y * p1x);

    if (denominator == 0.0f)
        return -1.0f;

    float t = ((p1x * v1x + p1y * v1y + p1z * v1z) / denominator);
    if (t < 0.0f || t > MAX_DEPTH)
        return -1.0f;

    float u = ((p2x * v1x + p2y * v1y + p2z * v1z) / denominator);
    if (u < 0.0f || u > 1.0f)
        return -1.0f;
    if ((p3x * v1x + p3y * v1y + p3z * v1z) / denominator > 1.0f)
        return -1.0f;

    float x = ox + t * dx;
    float y = oy + t * dy;
    float z = oz + t * dz;

    return sqrtf((x - ox) * (x - ox) + (y - oy) * (y - oy) + (z - oz) * (z - oz));
}

int main() {
    // Initialize the canvas
    float **canvas = malloc(HEIGHT * sizeof(float *));
    for (int i = 0; i < HEIGHT; i++)
        canvas[i] = malloc(WIDTH * sizeof(float));

    // Define the camera position and direction
    float ox = WIDTH / 2;
    float oy = HEIGHT / 2;
    float oz = -1.5f;
    float dx = 0.0f;
    float dy = 0.0f;
    float dz = 1.0f;

    // Define the light position
    float lx = ox + 3.0f;
    float ly = oy + 2.0f;
    float lz = oz - 4.5f;

    // Define the objects in the scene
    Triangle t1 = {{-1.0f, -1.0f, -1.0f}, {-1.0f, 1.0f, -1.0f}, {1.0f, -1.0f, -1.0f}};
    Triangle t2 = {{-1.0f, -1.0f, 1.0f}, {-1.0f, 1.0f, 1.0f}, {1.0f, -1.0f, 1.0f}};

    // Ray tracing loop
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            float x = ox + (j * dx) / (float)WIDTH;
            float y = oy + (i * dy) / (float)HEIGHT;
            float z = oz;

            // Calculate the intersection of the ray with the objects
            if (intersect(t1, x, y, z, dx, dy, dz) > 0.0f)
                canvas[i][j] = 255.0f;
            else if (intersect(t2, x, y, z, dx, dy, dz) > 0.0f)
                canvas[i][j] = 128.0f;
            else
                canvas[i][j] = 0.0f;
        }
    }

    // Display the rendered image
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", canvas[i][j] > 128.0f ? '*' : ' ');
        }
        printf("\n");
    }

    // Free the memory
    for (int i = 0; i < HEIGHT; i++)
        free(canvas[i]);
    free(canvas);

    return 0;
}