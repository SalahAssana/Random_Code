#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure to represent a 3D point
typedef struct {
    float x;
    float y;
    float z;
} vec3;

// Structure to represent a color
typedef struct {
    float r;
    float g;
    float b;
} color;

// Function to calculate the intersection of two lines
vec3 intersect_lines(vec3 p1, vec3 d1, vec3 p2, vec3 d2) {
    vec3 v = vec3_subtract(p2, p1);
    vec3 w = vec3_cross_product(d1, d2);
    float t = vec3_dot_product(v, w) / vec3_dot_product(d2, d2);
    return vec3_add(p1, vec3_scale(t, d1));
}

// Function to calculate the reflection of a vector
vec3 reflect(vec3 v, vec3 n) {
    return vec3_subtract(v, vec3_scale(2.0f * vec3_dot_product(v, n), n));
}

// Function to calculate the diffuse color of an object
color diffuse(vec3 normal, vec3 light_dir, color material_color) {
    float dot = vec3_dot_product(normal, light_dir);
    if (dot < 0.0f) return color_zero();
    return color_scale(dot, material_color);
}

// Function to calculate the specular color of an object
color specular(vec3 normal, vec3 view_dir, color material_color) {
    float dot = vec3_dot_product(normal, view_dir);
    if (dot < 0.0f) return color_zero();
    return color_scale(pow(dot, 5.0f), material_color);
}

// Function to calculate the ambient color of an object
color ambient(color material_color) {
    return material_color;
}

// Function to render a ray
void render_ray(vec3 origin, vec3 direction, int depth, color *color_buffer) {
    if (depth > 5) return; // Maximum recursion depth

    // Calculate the intersection point of the ray and the scene
    vec3 intersection = intersect_lines(origin, direction, vec3_zero(), vec3_one());
    float distance = vec3_distance(intersection, origin);

    if (distance < 0.01f) {
        // If we hit something, calculate the color
        color total_color;
        vec3 normal = vec3_normalize(vec3_subtract(intersection, origin));
        color material_color = color_new(1.0f, 0.5f, 0.5f);
        total_color.r += diffuse(normal, vec3_one(), material_color).r;
        total_color.g += diffuse(normal, vec3_one(), material_color).g;
        total_color.b += diffuse(normal, vec3_one(), material_color).b;
        color_buffer[depth] = total_color;

        // Calculate the reflection and add it to the color
        vec3 reflected_dir = reflect(direction, normal);
        render_ray(intersection, reflected_dir, depth + 1, color_buffer);

        return;
    }

    // If we didn't hit anything, just set the color to black
    color_buffer[depth] = color_zero();
}

// Function to initialize the ray tracing engine
void init(int width, int height) {
    printf("Initializing ray tracing engine with %dx%d resolution...\n", width, height);
}

// Function to render a frame
void render_frame(int width, int height) {
    printf("Rendering frame...\n");

    // Initialize the color buffer
    color *color_buffer = (color *)malloc(width * height * sizeof(color));
    for (int i = 0; i < width * height; i++) {
        color_buffer[i] = color_zero();
    }

    // Render each pixel in the frame
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            vec3 origin;
            origin.x = -1.5f + x * 2.0f / width;
            origin.y = -1.0f + y * 2.0f / height;
            origin.z = -7.0f;

            vec3 direction;
            direction.x = 0.0f;
            direction.y = 0.0f;
            direction.z = 1.0f;

            render_ray(origin, direction, 0, color_buffer);

            // Add the color of this pixel to the frame
            color total_color;
            for (int i = 0; i < 5; i++) {
                total_color.r += color_buffer[i].r;
                total_color.g += color_buffer[i].g;
                total_color.b += color_buffer[i].b;
            }
            total_color.r /= 5.0f;
            total_color.g /= 5.0f;
            total_color.b /= 5.0f;

            printf("Pixel (%d, %d) has color (%.2f, %.2f, %.2f)\n", x, y, total_color.r, total_color.g, total_color.b);
        }
    }

    free(color_buffer);
}

int main() {
    init(800, 600);
    render_frame(800, 600);

    return 0;
}