#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_OBJECTS 1000
#define MAX_LIGHTS 1000

typedef struct {
    float x, y, z;
} vec3;

typedef struct {
    vec3 position;
    vec3 direction;
} light_t;

typedef struct {
    vec3 position;
    vec3 color;
    float diffuse;
    float specular;
} material_t;

typedef struct {
    material_t material;
    vec3 bounding_box[2];
} object_t;

object_t objects[MAX_OBJECTS];
light_t lights[MAX_LIGHTS];

void raytrace(float* pixels, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            vec3 camera_position = {0.0f, 0.0f, 0.0f};
            vec3 ray_direction = {(float)x / width * 2 - 1.0f,
                                   (float)y / height * 2 - 1.0f,
                                   1.5f};
            float distance = 0.0f;
            int hit_object = -1;

            for (int i = 0; i < MAX_OBJECTS; i++) {
                if (distance > objects[i].bounding_box[0].z) {
                    continue;
                }

                vec3 ray_origin = camera_position;
                vec3 direction = normalize(ray_direction);
                float t = 0.0f;

                for (int j = 0; j < MAX_OBJECTS; j++) {
                    if (i == j) {
                        continue;
                    }

                    if (distance <= objects[j].bounding_box[1].z) {
                        break;
                    }

                    vec3 intersection = ray_intersection(ray_origin, direction,
                                                         objects[j].position,
                                                         objects[j].bounding_box);
                    t = distance + 0.00001f;
                    if (t > intersection.z && t < distance) {
                        distance = t;
                        hit_object = i;
                    }
                }

                if (hit_object != -1) {
                    break;
                }
            }

            if (distance > 5.0f) {
                pixels[y * width + x] = 255.0f;
                continue;
            }

            vec3 color = {0.0f, 0.0f, 0.0f};
            for (int i = 0; i < MAX_LIGHTS; i++) {
                light_t current_light = lights[i];
                vec3 light_position = current_light.position;
                vec3 light_direction = normalize(light_position - camera_position);
                float t = distance + 0.00001f;
                if (t > light_direction.z) {
                    continue;
                }

                vec3 shadow_ray_origin = light_position;
                vec3 shadow_direction = normalize(camera_position - light_position);
                float t_shadow = 0.0f;

                for (int j = 0; j < MAX_OBJECTS; j++) {
                    if (j == hit_object) {
                        continue;
                    }

                    vec3 intersection = ray_intersection(shadow_ray_origin,
                                                         shadow_direction,
                                                         objects[j].position,
                                                         objects[j].bounding_box);
                    t_shadow = distance + 0.00001f;
                    if (t_shadow > intersection.z && t_shadow < t) {
                        t = t_shadow;
                    }
                }

                vec3 ambient = {0.2f, 0.2f, 0.2f};
                float diffuse_intensity = 1.0f - pow(1.0f - t / distance,
                                                        objects[hit_object].material.diffuse);
                color.x += (ambient.x + current_light.direction.x * diffuse_intensity) *
                           objects[hit_object].material.color.x;
                color.y += (ambient.y + current_light.direction.y * diffuse_intensity) *
                           objects[hit_object].material.color.y;
                color.z += (ambient.z + current_light.direction.z * diffuse_intensity) *
                           objects[hit_object].material.color.z;
            }

            pixels[y * width + x] = color.x > 1.0f ? 255.0f : color.x;
        }
    }
}

vec3 normalize(vec3 v) {
    float length = sqrt(v.x * v.x + v.y * y + v.z * z);
    return (vec3){v.x / length, v.y / length, v.z / length};
}

vec3 ray_intersection(float x1, float y1, float z1,
                       vec3 p, vec3 bounding_box[2]) {
    vec3 normal = {0.0f, 0.0f, 0.0f};

    if (p.x > bounding_box[0].x) {
        normal.x = -1.0f;
    } else if (p.x < bounding_box[0].x) {
        normal.x = 1.0f;
    }

    if (p.y > bounding_box[0].y) {
        normal.y = -1.0f;
    } else if (p.y < bounding_box[0].y) {
        normal.y = 1.0f;
    }

    if (p.z > bounding_box[0].z) {
        normal.z = -1.0f;
    } else if (p.z < bounding_box[0].z) {
        normal.z = 1.0f;
    }

    vec3 intersection = {x1, y1, z1};
    float distance = 0.0f;

    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (i == 0) {
            continue;
        }

        vec3 direction = normalize(p - objects[i].position);
        float t = 0.0f;

        for (int j = 0; j < MAX_OBJECTS; j++) {
            if (i == j) {
                continue;
            }

            vec3 intersection = ray_intersection(x1, y1, z1,
                                                 objects[j].position,
                                                 objects[j].bounding_box);
            t = distance + 0.00001f;
            if (t > intersection.z && t < distance) {
                distance = t;
                hit_object = i;
            }
        }

        if (distance > 5.0f) {
            return (vec3){x1, y1, z1};
        }
    }

    return (vec3){-1.0f, -1.0f, -1.0f};
}

int main() {
    for (int i = 0; i < MAX_OBJECTS; i++) {
        objects[i].position.x = rand() % 100;
        objects[i].position.y = rand() % 100;
        objects[i].position.z = rand() % 100;

        objects[i].bounding_box[0] = (vec3){rand() % 10 - 5,
                                             rand() % 10 - 5,
                                             rand() % 10 - 5};
        objects[i].bounding_box[1] = (vec3){rand() % 10 - 5 + 10,
                                             rand() % 10 - 5 + 10,
                                             rand() % 10 - 5 + 10};

        objects[i].material.color.x = rand() % 255;
        objects[i].material.color.y = rand() % 255;
        objects[i].material.color.z = rand() % 255;

        objects[i].material.diffuse = (float)rand() / RAND_MAX;
    }

    for (int i = 0; i < MAX_LIGHTS; i++) {
        lights[i].position.x = rand() % 100;
        lights[i].position.y = rand() % 100;
        lights[i].position.z = rand() % 100;

        lights[i].direction.x = rand() % 2 - 1.0f;
        lights[i].direction.y = rand() % 2 - 1.0f;
        lights[i].direction.z = rand() % 2 - 1.0f;
    }

    float pixels[WIDTH * HEIGHT];

    raytrace(pixels, WIDTH, HEIGHT);

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%02x ", (unsigned int)pixels[i * WIDTH + j]);
        }
        printf("\n");
    }

    return 0;
}