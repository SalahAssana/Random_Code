#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Structure to represent 3D vertices
typedef struct {
    float x, y, z;
} vec3;

// Structure to represent a triangle mesh
typedef struct {
    int numTriangles;
    vec3* triangles[1000];
} mesh_t;

// Function to calculate the intersection of a ray with a triangle
int intersectTriangle(vec3* triangle, vec3* origin, vec3* direction) {
    // Calculate the edge vectors and normal vector
    vec3 e1 = {triangle[1].x - triangle[0].x, triangle[1].y - triangle[0].y, triangle[1].z - triangle[0].z};
    vec3 e2 = {triangle[2].x - triangle[0].x, triangle[2].y - triangle[0].y, triangle[2].z - triangle[0].z};
    vec3 normal = {e2.y * e1.z - e2.z * e1.y, e2.z * e1.x - e2.x * e1.z, e2.x * e1.y - e2.y * e1.x};

    // Calculate the ray's direction vector
    vec3 rayDirection = {direction.x, direction.y, direction.z};

    // Calculate the dot product of the ray and normal vectors
    float dotProduct = rayDirection.x * normal.x + rayDirection.y * normal.y + rayDirection.z * normal.z;

    // Check if the triangle is visible from the origin
    if (dotProduct < 0) return -1; // Not visible

    // Calculate the intersection distance using the formula:
    // t = (edge1 dot p - edge1 dot o) / (edge1 dot n)
    float t = ((e1.x * normal.x + e1.y * normal.y + e1.z * normal.z) - (triangle[0].x - origin->x)) /
              (normal.x * rayDirection.x + normal.y * rayDirection.y + normal.z * rayDirection.z);

    // Check if the intersection point is inside the triangle
    vec3 p = {origin->x + t * direction.x, origin->y + t * direction.y, origin->z + t * direction.z};
    float barycentric[3];
    barycentric[0] = (p.x - triangle[0].x) / e1.x;
    barycentric[1] = (p.y - triangle[0].y) / e2.y;
    barycentric[2] = 1 - barycentric[0] - barycentric[1];

    if (barycentric[0] > 0 && barycentric[1] > 0 && barycentric[2] > 0) {
        return t;
    } else {
        return -1; // Not inside
    }
}

// Function to render a scene using ray marching
void renderScene(mesh_t* mesh, int width, int height, float fov, float near, float far) {
    // Initialize the camera
    vec3 cameraPos = {0, 0, 0};
    vec3 cameraDirection = {0, 0, -1};

    // Initialize the image buffer
    char* imageBuffer = (char*)malloc(width * height * sizeof(char));

    // Set up the ray marching loop
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Calculate the ray's origin and direction
            vec3 origin = {cameraPos.x, cameraPos.y, cameraPos.z};
            vec3 direction = {x * 2.0 / width - 1.0 + (y * 2.0 / height - 1.0) * tan(fov), y * 2.0 / height - 1.0, near};

            // March the ray
            float distance = far;
            for (int i = 0; i < mesh->numTriangles; i++) {
                vec3* triangle = mesh->triangles[i];
                int t = intersectTriangle(triangle, &origin, &direction);
                if (t > 0) {
                    distance = t;
                    break;
                }
            }

            // Calculate the color based on the intersection point
            float r, g, b;
            if (distance < far) {
                r = sin(distance * distance * 2.0) * 0.5 + 0.5;
                g = cos(distance * distance * 4.0) * 0.5 + 0.5;
                b = sin(distance * distance * 8.0) * 0.5 + 0.5;
            } else {
                r = 0;
                g = 0;
                b = 0;
            }

            // Store the color in the image buffer
            int index = (y * width * 4) + (x * 4);
            imageBuffer[index] = r * 255;
            imageBuffer[index + 1] = g * 255;
            imageBuffer[index + 2] = b * 255;
            imageBuffer[index + 3] = 255;
        }
    }

    // Write the image buffer to a file
    FILE* file = fopen("output.ppm", "wb");
    fprintf(file, "P6\n");
    fprintf(file, "%d %d\n", width, height);
    fprintf(file, "255\n");
    fwrite(imageBuffer, 1, width * height * 4, file);
    fclose(file);

    free(imageBuffer);
}

int main() {
    // Create a mesh with some triangles
    mesh_t mesh;
    mesh.numTriangles = 3;
    mesh.triangles[0] = (vec3*)malloc(sizeof(vec3) * 3);
    mesh.triangles[1] = (vec3*)malloc(sizeof(vec3) * 3);
    mesh.triangles[2] = (vec3*)malloc(sizeof(vec3) * 3);

    // Set the triangle vertices
    mesh.triangles[0][0].x = -1; mesh.triangles[0][0].y = -1; mesh.triangles[0][0].z = 0;
    mesh.triangles[0][1].x = 1; mesh.triangles[0][1].y = -1; mesh.triangles[0][1].z = 0;
    mesh.triangles[0][2].x = 0; mesh.triangles[0][2].y = 1; mesh.triangles[0][2].z = 0;

    mesh.triangles[1][0].x = -1; mesh.triangles[1][0].y = 1; mesh.triangles[1][0].z = 0;
    mesh.triangles[1][1].x = 1; mesh.triangles[1][1].y = 1; mesh.triangles[1][1].z = 0;
    mesh.triangles[1][2].x = 0; mesh.triangles[1][2].y = -1; mesh.triangles[1][2].z = 0;

    mesh.triangles[2][0].x = -1; mesh.triangles[2][0].y = -1; mesh.triangles[2][0].z = 0;
    mesh.triangles[2][1].x = 1; mesh.triangles[2][1].y = -1; mesh.triangles[2][1].z = 0;
    mesh.triangles[2][2].x = 0; mesh.triangles[2][2].y = 1; mesh.triangles[2][2].z = 0;

    // Render the scene
    renderScene(&mesh, 640, 480, 45.0, 0.1, 100);

    return 0;
}