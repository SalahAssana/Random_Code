#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure to represent a 3D point
typedef struct {
    float x;
    float y;
    float z;
} Point3f;

// Structure to represent a vector
typedef struct {
    float x;
    float y;
    float z;
} Vector3f;

// Function to calculate the dot product of two vectors
float vec_dot(Vector3f v1, Vector3f v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Function to calculate the magnitude (length) of a vector
float vec_magnitude(Vector3f v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Structure to represent a light source
typedef struct {
    Point3f position; // Position of the light in 3D space
    float intensity; // Intensity of the light (0-1)
} Light;

// Function to perform ray-math intersection on a triangle
int ray_triangle_intersect(Point3f p, Vector3f direction, Point3f v0, Point3f v1, Point3f v2) {
    Vector3f edge1 = {v1.x - v0.x, v1.y - v0.y, v1.z - v0.z};
    Vector3f edge2 = {v2.x - v0.x, v2.y - v0.y, v2.z - v0.z};
    Vector3f h = {direction.x, direction.y, direction.z};
    float a = vec_dot(edge1, edge1);
    float b = 2.0 * (vec_dot(edge1, edge2) + vec_dot(h, edge1));
    float c = vec_dot(edge2, edge2) + 2.0 * vec_dot(h, edge2);

    if (a > 0.00001 && b > a && c > a) {
        float t = (-b - sqrt(b*b - 4*a*c)) / (2*a);
        return 1;
    } else {
        return 0;
    }
}

// Function to perform ray-math intersection on a sphere
int ray_sphere_intersect(Point3f p, Vector3f direction, Point3f center, float radius) {
    Vector3f v = {p.x - center.x, p.y - center.y, p.z - center.z};
    float a = vec_dot(v, v);
    float b = 2.0 * (vec_dot(direction, v));
    float c = vec_magnitude(direction) * vec_magnitude(direction) - radius*radius;
    float t = (-b - sqrt(b*b - 4*a*c)) / (2*a);

    if (t > 0.00001) {
        return 1;
    } else {
        return 0;
    }
}

// Function to perform ray-math intersection on a plane
int ray_plane_intersect(Point3f p, Vector3f direction, Point3f normal, float distance) {
    float a = vec_dot(direction, normal);
    float b = 2.0 * (vec_dot(normal, p) - distance);
    float c = vec_magnitude(p) - distance;

    if (a > 0.00001 && b > a && c > a) {
        float t = (-b - sqrt(b*b - 4*a*c)) / (2*a);
        return 1;
    } else {
        return 0;
    }
}

// Function to render the scene using ray tracing
void render_scene() {
    // Initialize the camera position, direction and up vector
    Point3f camera_position = {0.0, 0.0, -5.0};
    Vector3f camera_direction = {-1.0, 0.0, 0.0};
    Vector3f camera_up = {0.0, 1.0, 0.0};

    // Initialize the light sources
    Light lights[2];
    lights[0].position.x = -5.0; lights[0].position.y = 0.0; lights[0].position.z = 0.0;
    lights[0].intensity = 1.0;
    lights[1].position.x = 5.0; lights[1].position.y = 0.0; lights[1].position.z = 0.0;
    lights[1].intensity = 1.0;

    // Initialize the objects in the scene
    Point3f v0 = {0.0, 0.0, 0.0}; // Triangle vertex 1
    Point3f v1 = {1.0, 0.0, 0.0}; // Triangle vertex 2
    Point3f v2 = {0.5, 0.8660254, 0.0}; // Triangle vertex 3
    Point3f center = {0.0, 0.0, -1.0}; // Sphere center
    float radius = 0.5; // Sphere radius
    Point3f normal = {0.0, 0.0, -1.0}; // Plane normal

    int i;
    for (i = 0; i < 640; i++) {
        for (int j = 0; j < 480; j++) {
            // Initialize the ray origin and direction
            Point3f p = {i + 320, j + 240, 0.0};
            Vector3f direction = {(p.x - camera_position.x) / 100.0, (p.y - camera_position.y) / 100.0, (p.z - camera_position.z) / 100.0};

            // Perform ray-math intersection on the objects in the scene
            int hit = 0;
            for (int k = 0; k < 2; k++) {
                if (ray_triangle_intersect(p, direction, v0, v1, v2)) {
                    hit = 1;
                    break;
                }
            }

            // Perform ray-math intersection on the sphere
            if (!hit) {
                hit = ray_sphere_intersect(p, direction, center, radius);
            }

            // Perform ray-math intersection on the plane
            if (!hit) {
                hit = ray_plane_intersect(p, direction, normal, 0.5);
            }

            // Render the scene
            if (hit) {
                printf("\033[40;20f");
            } else {
                printf("\033[40;20 ");
            }
        }
    }
}

int main() {
    render_scene();
    return 0;
}