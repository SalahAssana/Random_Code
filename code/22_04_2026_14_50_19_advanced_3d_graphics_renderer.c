#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define WIDTH 640
#define HEIGHT 480
#define MAX_OBJECTS 1000
#define MAX_LIGHTS 10
#define EPSILON 1e-6

typedef struct {
    float x, y, z;
} Vector3D;

typedef struct {
    Vector3D position;
    Vector3D normal;
} Object;

typedef struct {
    Vector3D direction;
    float intensity;
} Light;

void renderScene(Object* objects, int numObjects, Light* lights, int numLights) {
    // Initialize the frame buffer
    unsigned char* frameBuffer = (unsigned char*)malloc(WIDTH * HEIGHT * 4);
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        frameBuffer[i * 4] = 255;
        frameBuffer[i * 4 + 1] = 255;
        frameBuffer[i * 4 + 2] = 255;
        frameBuffer[i * 4 + 3] = 0;
    }

    // Iterate over each pixel in the screen
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            Vector3D cameraPosition = {0, 0, -5};
            Vector3D rayOrigin = {(float)x / WIDTH * 2.0f - 1.0f, (float)y / HEIGHT * 2.0f - 1.0f, 0};
            Vector3D rayDirection = normalizeVector3D(subtractVectors(cameraPosition, rayOrigin));

            // Perform a ray intersection test
            Object* closestObject = NULL;
            float closestDistance = INFINITY;
            for (int i = 0; i < numObjects; i++) {
                if (rayIntersectsObject(&objects[i], &rayOrigin, &rayDirection, &closestDistance)) {
                    closestObject = &objects[i];
                    break;
                }
            }

            // Calculate the material properties
            float diffuse, specular;
            Vector3D materialColor;

            // Shade the object
            if (closestObject) {
                // Calculate the normal at the intersection point
                Vector3D normal = normalizeVector3D(subtractVectors(&closestObject->position, &closestObject->normal));

                // Perform a lighting calculation
                for (int i = 0; i < numLights; i++) {
                    Light light = lights[i];
                    float distanceToLight = lengthVector3D(subtractVectors(&light.position, &closestObject->position));
                    if (distanceToLight > EPSILON) {
                        Vector3D lightDirection = normalizeVector3D(subtractVectors(&light.position, &closestObject->position));
                        float diffuseFactor = dotProduct(normal, lightDirection);
                        diffuse += max(diffuseFactor, 0.0f);

                        // Calculate the specular term
                        float halfAngle = dotProduct(normal, lightDirection) / (1 + lengthVector3D(lightDirection));
                        float specularFactor = pow(halfAngle, 16.0f);
                        specular += min(specularFactor, 1.0f);
                    }
                }

                // Combine the diffuse and specular terms
                materialColor = closestObject->materialColor * (diffuse + specular);

                // Draw the object at the intersection point
                frameBuffer[(x + y * WIDTH) * 4] = (unsigned char)(materialColor.x * 255.0f);
                frameBuffer[(x + y * WIDTH) * 4 + 1] = (unsigned char)(materialColor.y * 255.0f);
                frameBuffer[(x + y * WIDTH) * 4 + 2] = (unsigned char)(materialColor.z * 255.0f);
                frameBuffer[(x + y * WIDTH) * 4 + 3] = 255;
            }
        }
    }

    // Write the frame buffer to a PPM file
    FILE* ppmFile = fopen("output.ppm", "wb");
    fprintf(ppmFile, "P3\n");
    fprintf(ppmFile, "%d %d\n", WIDTH, HEIGHT);
    fprintf(ppmFile, "255\n");
    fwrite(frameBuffer, 1, WIDTH * HEIGHT * 4, ppmFile);
    fclose/ppmFile;

    free(frameBuffer);
}

int main() {
    // Define the objects in the scene
    Object objects[MAX_OBJECTS];
    for (int i = 0; i < MAX_OBJECTS; i++) {
        objects[i].position.x = (float)i * 2.0f - 10.0f;
        objects[i].position.y = 0;
        objects[i].position.z = 0;
        objects[i].normal.x = 1;
        objects[i].normal.y = 1;
        objects[i].normal.z = 1;
    }

    // Define the lights in the scene
    Light lights[MAX_LIGHTS];
    for (int i = 0; i < MAX_LIGHTS; i++) {
        lights[i].position.x = (float)i * 2.0f - 10.0f;
        lights[i].position.y = 0;
        lights[i].position.z = 0;
        lights[i].direction.x = 1;
        lights[i].direction.y = 1;
        lights[i].direction.z = 1;
        lights[i].intensity = (float)i * 2.0f - 10.0f;
    }

    // Render the scene
    renderScene(objects, MAX_OBJECTS, lights, MAX_LIGHTS);

    return 0;
}

Vector3D addVectors(Vector3D a, Vector3D b) {
    return (Vector3D){a.x + b.x, a.y + b.y, a.z + b.z};
}

Vector3D subtractVectors(Vector3D a, Vector3D b) {
    return (Vector3D){a.x - b.x, a.y - b.y, a.z - b.z};
}

float dotProduct(Vector3D a, Vector3D b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3D normalizeVector3D(Vector3D vector) {
    float length = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    return (Vector3D){vector.x / length, vector.y / length, vector.z / length};
}

float lengthVector3D(Vector3D vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}