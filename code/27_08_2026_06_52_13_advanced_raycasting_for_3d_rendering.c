#include <stdio.h>
#include <stdlib.h>

// Structure to represent a 3D point
typedef struct {
    float x, y, z;
} Vector3;

// Structure to represent a 2D texture coordinate
typedef struct {
    float u, v;
} TexCoord;

// Structure to represent a raycasted pixel
typedef struct {
    Vector3 position;
    TexCoord texCoord;
    int hit;
} Pixel;

// Function to calculate the distance between two points
float distance(Vector3 p1, Vector3 p2) {
    return sqrtf((p2.x - p1.x) * (p2.x - p1.x) +
                  (p2.y - p1.y) * (p2.y - p1.y) +
                  (p2.z - p1.z) * (p2.z - p1.z));
}

// Function to perform raycasting
Pixel* raycast(float fov, int width, int height, Vector3 cameraPos, Vector3 targetPos, float** textureMap, int textureWidth, int textureHeight) {
    Pixel* pixels = (Pixel*)malloc(width * height * sizeof(Pixel));
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Vector3 rayDir = {(targetPos.x - cameraPos.x) / distance(cameraPos, targetPos),
                              (targetPos.y - cameraPos.y) / distance(cameraPos, targetPos),
                              (targetPos.z - cameraPos.z) / distance(cameraPos, targetPos)};
            Vector3 rayOrigin = cameraPos;
            float t = 0.0f;
            int hit = 0;
            for (float z = 0.0f; z < 10.0f && !hit; z += 0.1f) {
                Vector3 rayEnd = {cameraPos.x + rayDir.x * z, cameraPos.y + rayDir.y * z, cameraPos.z + rayDir.z * z};
                if (rayEnd.z > targetPos.z) {
                    hit = 1;
                    break;
                }
            }
            if (!hit) {
                pixels[y * width + x].position.x = cameraPos.x;
                pixels[y * width + x].position.y = cameraPos.y;
                pixels[y * width + x].position.z = targetPos.z;
                pixels[y * width + x].texCoord.u = 0.5f;
                pixels[y * width + x].texCoord.v = 0.5f;
                pixels[y * width + x].hit = 1;
            } else {
                Vector3 diff = {targetPos.x - rayEnd.x, targetPos.y - rayEnd.y, targetPos.z - rayEnd.z};
                float mag = sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
                diff.x /= mag;
                diff.y /= mag;
                diff.z /= mag;
                Vector3 rayDir2D = {diff.x, diff.y, 0.0f};
                float dotProd = rayDir2D.x * rayDir2D.x + rayDir2D.y * rayDir2D.y;
                if (dotProd > 1.0f) {
                    dotProd = 1.0f;
                } else if (dotProd < -1.0f) {
                    dotProd = -1.0f;
                }
                float angle = acosf(dotProd);
                if (angle > fov / 2.0f) {
                    pixels[y * width + x].position.x = cameraPos.x;
                    pixels[y * width + x].position.y = cameraPos.y;
                    pixels[y * width + x].position.z = targetPos.z;
                    pixels[y * width + x].texCoord.u = 0.5f;
                    pixels[y * width + x].texCoord.v = 0.5f;
                    pixels[y * width + x].hit = 1;
                } else {
                    float distToWall = distance(cameraPos, rayEnd);
                    int wallX = (int)((rayEnd.x - cameraPos.x) / distToWall * textureWidth);
                    int wallY = (int)((rayEnd.y - cameraPos.y) / distToWall * textureHeight);
                    pixels[y * width + x].position.x = rayEnd.x;
                    pixels[y * width + x].position.y = rayEnd.y;
                    pixels[y * width + x].position.z = targetPos.z;
                    pixels[y * width + x].texCoord.u = (float)wallX / textureWidth;
                    pixels[y * width + x].texCoord.v = (float)wallY / textureHeight;
                    pixels[y * width + x].hit = 1;
                }
            }
        }
    }
    return pixels;
}

int main() {
    float fov = 45.0f;
    int width = 800, height = 600;
    Vector3 cameraPos = {0.0f, 0.0f, -5.0f};
    Vector3 targetPos = {0.0f, 0.0f, 0.0f};
    float** textureMap = (float**)malloc(1024 * sizeof(float*));
    for (int i = 0; i < 1024; i++) {
        textureMap[i] = (float*)malloc(1024 * sizeof(float));
    }
    int textureWidth = 1024, textureHeight = 1024;
    Pixel* pixels = raycast(fov, width, height, cameraPos, targetPos, textureMap, textureWidth, textureHeight);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf("%f %f %i\n", pixels[y * width + x].position.x, pixels[y * width + x].position.y,
                   pixels[y * width + x].hit);
        }
    }
    free(pixels);
    for (int i = 0; i < 1024; i++) {
        free(textureMap[i]);
    }
    free(textureMap);
    return 0;
}