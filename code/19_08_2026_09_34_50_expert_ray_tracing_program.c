#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_LIGHTS 1000
#define MAX_OBJECTS 10000
#define MAX_MATERIALS 100

typedef struct {
    float x, y, z;
} Vec3;

typedef struct {
    Vec3 position;
    Vec3 normal;
    float diffuse, specular;
} Material;

typedef struct {
    Vec3 position;
    Vec3 center;
    float radius;
    Material material;
} Object;

typedef struct {
    float x, y, z;
} PointLight;

void traceRay(Vec3 *ray, int *depth, Vec3 *color, Object **objects, int num_objects,
             PointLight *lights, int num_lights) {
    for (int i = 0; i < num_objects; i++) {
        float distance = sqrt(pow(objects[i]->position.x - ray->x, 2) +
                               pow(objects[i]->position.y - ray->y, 2) +
                               pow(objects[i]->position.z - ray->z, 2));
        if (distance < objects[i]->radius && distance < 1000.0f) {
            Vec3 normal = normalize(cross(subtract(objects[i]->center, *ray),
                                           objects[i]->normal));
            float diffuse = dot(normal, ray->x > 0 ? lights[0].x - ray->x : lights[0].y - ray->y);
            if (diffuse > 0.5f) {
                color->x += objects[i]->material.diffuse;
                color->y += objects[i]->material.diffuse;
                color->z += objects[i]->material.diffuse;
            }
        }
    }
}

Vec3 normalize(Vec3 v) {
    float length = sqrt(v.x * v.x + v.y * y + v.z * z);
    return (Vec3){v.x / length, v.y / length, v.z / length};
}

Vec3 cross(Vec3 a, Vec3 b) {
    return (Vec3){a.y * b.z - a.z * b.y,
                   a.z * b.x - a.x * b.z,
                   a.x * b.y - a.y * b.x};
}

Vec3 subtract(Vec3 a, Vec3 b) {
    return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

float dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

int main() {
    int i, j;
    int num_objects = 10000;
    int num_lights = 1000;

    Object *objects = (Object *)malloc(sizeof(Object) * num_objects);
    PointLight *lights = (PointLight *)malloc(sizeof(PointLight) * num_lights);

    for (i = 0; i < num_objects; i++) {
        objects[i].position.x = (float)(rand() % 10000) - 5000.0f;
        objects[i].position.y = (float)(rand() % 10000) - 5000.0f;
        objects[i].position.z = (float)(rand() % 10000) - 5000.0f;
        objects[i].center.x = (float)(rand() % 10000) - 5000.0f;
        objects[i].center.y = (float)(rand() % 10000) - 5000.0f;
        objects[i].center.z = (float)(rand() % 10000) - 5000.0f;
        objects[i].radius = (float)(rand() % 10) + 1.0f;
        objects[i].material.diffuse = (float)(rand() % 255) / 255.0f;
    }

    for (j = 0; j < num_lights; j++) {
        lights[j].x = (float)(rand() % 10000) - 5000.0f;
        lights[j].y = (float)(rand() % 10000) - 5000.0f;
        lights[j].z = (float)(rand() % 10000) - 5000.0f;
    }

    Vec3 *colors = (Vec3 *)malloc(sizeof(Vec3) * WIDTH * HEIGHT);

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            Vec3 ray = {j - WIDTH / 2.0f, i - HEIGHT / 2.0f, 1.0f};
            int depth = 0;
            Vec3 color = {0.0f, 0.0f, 0.0f};

            traceRay(&ray, &depth, &color, objects, num_objects, lights, num_lights);

            colors[i * WIDTH + j] = color;
        }
    }

    FILE *fp = fopen("output.ppm", "w");
    fprintf(fp, "P3\n%d %d\n255\n", WIDTH, HEIGHT);
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            Vec3 color = colors[i * WIDTH + j];
            fprintf(fp, "%d %d %d ", (int)(color.x * 255), (int)(color.y * 255), (int)(color.z * 255));
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

    free(objects);
    free(lights);
    free(colors);

    return 0;
}