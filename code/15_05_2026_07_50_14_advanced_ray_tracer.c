#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float r, g, b;
} color;

typedef struct {
    float x, y, z;
} point3d;

color make_color(float r, float g, float b) {
    return (color){r, g, b};
}

point3d make_point3d(float x, float y, float z) {
    return (point3d){x, y, z};
}

// Ray structure
typedef struct {
    point3d origin;
    point3d direction;
} ray;

// Sphere structure
typedef struct {
    point3d center;
    float radius;
} sphere;

color trace_ray(ray r, sphere s) {
    // Calculate the distance from the ray's origin to the sphere's center
    float distance = sqrt(pow(r.origin.x - s.center.x, 2) + pow(r.origin.y - s.center.y, 2) + pow(r.origin.z - s.center.z, 2));
    
    // Check if the ray hits the sphere
    if (distance <= s.radius) {
        // Calculate the intersection point
        float t = sqrt(pow(s.radius, 2) - pow(distance, 2));
        point3d intersection = make_point3d(r.origin.x + r.direction.x * t, 
                                            r.origin.y + r.direction.y * t, 
                                            r.origin.z + r.direction.z * t);
        
        // Calculate the normal vector at the intersection point
        float nx = (intersection.x - s.center.x) / s.radius;
        float ny = (intersection.y - s.center.y) / s.radius;
        float nz = (intersection.z - s.center.z) / s.radius;
        
        return make_color(nx, ny, nz);
    } else {
        // Ray misses the sphere
        return make_color(0, 0, 0); // Black color
    }
}

int main() {
    // Create a ray object
    ray r = (ray){make_point3d(0.0f, 0.0f, -1.0f), 
                make_point3d(0.0f, 0.0f, 0.5f)};

    // Create a sphere object
    sphere s = (sphere){make_point3d(0.0f, 0.0f, 0.0f), 1.0f};
    
    color result = trace_ray(r, s);
    
    printf("Color: (%f, %f, %f)\n", result.r, result.g, result.b);

    return 0;
}