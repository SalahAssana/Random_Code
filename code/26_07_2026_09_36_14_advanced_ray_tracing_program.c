#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_OBJECTS 1000
#define MAX_LIGHTS 1000

// Structure to represent a point in 3D space
typedef struct {
    float x, y, z;
} Point;

// Structure to represent a vector in 3D space
typedef struct {
    float x, y, z;
} Vector;

// Structure to represent an object (e.g. sphere, plane)
typedef struct {
    int type; // 0 = sphere, 1 = plane
    float radius; // only applicable for spheres
    float normal_x, normal_y, normal_z; // normal vector for planes
    Point center; // center of the object
} Object;

// Structure to represent a light source
typedef struct {
    float x, y, z; // position of the light
    float intensity; // intensity of the light
} Light;

// Function to calculate the intersection between a ray and an object
Object intersect(Object* objects, int num_objects, Vector* ray_dir, Point* origin) {
    Object closest = (Object){-1, -1, -1};
    float min_distance = INFINITY;
    
    for (int i = 0; i < num_objects; i++) {
        if (objects[i].type == 0) { // sphere
            Vector v = {{origin->x + ray_dir->x * objects[i].radius},
                         {origin->y + ray_dir->y * objects[i].radius},
                         {origin->z + ray_dir->z * objects[i].radius}};
            float distance = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
            if (distance < min_distance && distance <= objects[i].radius) {
                closest = objects[i];
                min_distance = distance;
            }
        } else { // plane
            Vector v = {{origin->x - objects[i].center.x},
                         {origin->y - objects[i].center.y},
                         {origin->z - objects[i].center.z}};
            float dot_product = v.x * ray_dir->x + v.y * ray_dir->y + v.z * ray_dir->z;
            if (dot_product > 0 && sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)) < min_distance) {
                closest = objects[i];
                min_distance = dot_product / sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
            }
        }
    }
    
    return closest;
}

// Function to calculate the color of a pixel using ray tracing
void render(int width, int height, Object* objects, int num_objects, Light* lights, int num_lights) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Vector ray_dir = {{(float)x / width - 0.5},
                               {(float)y / height - 0.5},
                               sqrt(1 - pow((float)x / width - 0.5, 2) - pow((float)y / height - 0.5, 2))};
            Point origin = {{-0.5}, {-0.5}, {0}};
            
            Object hit_object = intersect(objects, num_objects, &ray_dir, &origin);
            
            if (hit_object.type == 0) { // sphere
                Vector v = {{origin.x + ray_dir.x * hit_object.radius},
                             {origin.y + ray_dir.y * hit_object.radius},
                             {origin.z + ray_dir.z * hit_object.radius}};
                float distance = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
                Vector normal = {{v.x / distance}, {v.y / distance}, {v.z / distance}};
                
                float diffuse_amount = (normal.x * ray_dir.x + normal.y * ray_dir.y + normal.z * ray_dir.z);
                float color = pow(diffuse_amount, 1.0f) * 255;
                
                // Write the color to the framebuffer
                printf("%c[2J%c[%d;%dH", 27, 27, y+1, x+1);
                for (int i = 0; i < color / 256; i++) {
                    puts(" ");
                }
                for (int i = 0; i < color % 256; i++) {
                    puts("#");
                }
            } else { // plane
                Vector v = {{origin.x - hit_object.center.x},
                             {origin.y - hit_object.center.y},
                             {origin.z - hit_object.center.z}};
                float distance = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
                
                // Calculate the ambient occlusion
                float ao = 1.0f;
                for (int i = 0; i < num_lights; i++) {
                    Vector light_dir = {{lights[i].x - origin.x},
                                         {lights[i].y - origin.y},
                                         {lights[i].z - origin.z}};
                    float dot_product = v.x * light_dir.x + v.y * light_dir.y + v.z * light_dir.z;
                    ao *= max(0.0f, 1.0f - pow(dot_product / distance, 2));
                }
                
                // Calculate the diffuse color
                float diffuse_amount = (v.x * ray_dir.x + v.y * ray_dir.y + v.z * ray_dir.z);
                float color = ao * pow(diffuse_amount, 1.0f) * 255;
                
                // Write the color to the framebuffer
                printf("%c[2J%c[%d;%dH", 27, 27, y+1, x+1);
                for (int i = 0; i < color / 256; i++) {
                    puts(" ");
                }
                for (int i = 0; i < color % 256; i++) {
                    puts("#");
                }
            }
        }
    }
}

int main() {
    Object objects[MAX_OBJECTS];
    int num_objects = 5;
    
    Object sphere1 = {{0, }, {1.0f}, {{0}}, {(float)0}};
    Object sphere2 = {{0, }, {1.0f}, {{0}}, {(float)0}};
    Object plane = {{1, }, {(float)1}, {{0, }, {0, }, {0}}};
    
    objects[0] = sphere1;
    objects[1] = sphere2;
    objects[2] = plane;
    
    num_objects = 3;
    
    Light lights[MAX_LIGHTS];
    int num_lights = 1;
    
    Light light = {{0, }, {(float)1}};
    lights[0] = light;
    
    num_lights = 1;
    
    render(WIDTH, HEIGHT, objects, num_objects, lights, num_lights);
    
    return 0;
}