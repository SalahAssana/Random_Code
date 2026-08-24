Here is the C code for the Ray Marching project:

```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define constants
#define WIDTH 800
#define HEIGHT 600
#define MAX_RAYS 1000000
#define MAX_STEPS 128
#define EPSILON 0.001

// Define structures
typedef struct {
    float x, y, z;
} Vec3;

typedef struct {
    Vec3 color;
    float diffuse, specular;
} Material;

typedef struct {
    Vec3 position;
    Vec3 normal;
    Material material;
} Object;

// Function prototypes
void renderScene();
Vec3 rayMarch(int, int);
Object* intersectRay(Vec3, Vec3, float*);
Material getMaterial(Object*, float);

int main() {
    // Initialize scene objects
    Object* objects[10];
    for (int i = 0; i < 10; i++) {
        objects[i] = (Object*)malloc(sizeof(Object));
        objects[i]->position.x = rand() % 100;
        objects[i]->position.y = rand() % 100;
        objects[i]->position.z = rand() % 100;
        objects[i]->normal.x = rand() % 2 - 1;
        objects[i]->normal.y = rand() % 2 - 1;
        objects[i]->normal.z = rand() % 2 - 1;
        objects[i]->material.color.x = (rand() % 256) / 255.0f;
        objects[i]->material.color.y = (rand() % 256) / 255.0f;
        objects[i]->material.color.z = (rand() % 256) / 255.0f;
        objects[i]->material.diffuse = rand() % 2 ? 1 : 0;
        objects[i]->material.specular = rand() % 2 ? 1 : 0;
    }

    // Render the scene
    renderScene();

    return 0;
}

void renderScene() {
    // Initialize rays
    Vec3* rays[MAX_RAYS];
    for (int i = 0; i < MAX_RAYS; i++) {
        rays[i] = (Vec3*)malloc(sizeof(Vec3));
        rays[i]->x = rand() % WIDTH;
        rays[i]->y = rand() % HEIGHT;
        rays[i]->z = 0.5f;
    }

    // March each ray
    for (int i = 0; i < MAX_RAYS; i++) {
        Vec3 color = Vec3{0, 0, 0};
        float t = EPSILON;
        Object* hitObject = NULL;

        for (int j = 0; j < MAX_STEPS; j++) {
            // Calculate ray position
            Vec3 pos = Vec3{
                rays[i]->x + t * (WIDTH - 1),
                rays[i]->y + t * (HEIGHT - 1),
                0.5f - t
            };

            // Intersect the ray with objects
            Object* intersectedObject = NULL;
            for (int k = 0; k < 10; k++) {
                if (intersectRay(rays[i]->x, rays[i]->y, &t) && t < EPSILON) {
                    intersectedObject = objects[k];
                    break;
                }
            }

            // If we hit an object
            if (intersectedObject) {
                // Calculate lighting
                Vec3 lightDir = Vec3{-1, -1, 0};
                float diffuseTerm = dot(intersectedObject->normal, lightDir);
                float specularTerm = pow(dot(normalize(intersectedObject->normal), normalize(lightDir)), 2);

                // Shade the hit object
                Material material = getMaterial(intersectedObject, diffuseTerm);
                color.x += material.color.x * (material.diffuse + material.specular * specularTerm);
                color.y += material.color.y * (material.diffuse + material.specular * specularTerm);
                color.z += material.color.z * (material.diffuse + material.specular * specularTerm);

                // Stop marching
                break;
            }

            t += EPSILON;
        }

        // Output the final color
        printf("%f %f %f\n", color.x, color.y, color.z);
    }
}

Vec3 rayMarch(int x, int y) {
    Vec3 origin = Vec3{(float)x, (float)y, 0.5f};
    Vec3 direction = Vec3{1 - 2 * (x / (float)WIDTH), 1 - 2 * (y / (float)HEIGHT), 0};
    return origin + direction * EPSILON;
}

Object* intersectRay(Vec3 start, Vec3 end, float* t) {
    // Calculate the intersection with objects
    // ...

    return NULL;
}

Material getMaterial(Object* object, float diffuseTerm) {
    // Calculate the material properties based on the object and lighting
    // ...

    return (Material){.color = {object->material.color.x * diffuseTerm, object->material.color.y * diffuseTerm, object->material.color.z * diffuseTerm}, .diffuse = object->material.diffuse, .specular = object->material.specular};
}

float dot(Vec3 v1, Vec3 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vec3 normalize(Vec3 v) {
    float len = sqrt(v.x * v.x + v.y * y + v.z * z);
    return Vec3{v.x / len, v.y / len, v.z / len};
}
```