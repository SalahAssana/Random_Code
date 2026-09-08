#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure to represent a 3D point
typedef struct {
    float x;
    float y;
    float z;
} Point3D;

// Structure to represent a vector
typedef struct {
    float x;
    float y;
    float z;
} Vector3D;

// Function to calculate the dot product of two vectors
float dotProduct(Vector3D v1, Vector3D v2) {
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

// Function to calculate the magnitude of a vector
float magnitude(Vector3D v) {
    return sqrt((v.x * v.x + v.y * v.y + v.z * v.z));
}

// Structure to represent a ray
typedef struct {
    Vector3D origin;
    Vector3D direction;
} Ray;

// Function to cast a ray and detect collisions with 3D objects
void castRay(Ray r, Point3D** objects, int numObjects) {
    float t = 0.0f; // Time of intersection

    for (int i = 0; i < numObjects; i++) {
        Vector3D v1 = vectorSubtract(&objects[i]->position, &r.origin);
        Vector3D v2 = vectorMultiply(&v1, r.direction);

        float denominator = dotProduct(v2, v2);
        if (denominator == 0.0f) continue;

        float numerator = dotProduct(vectorSubtract(&objects[i]->position, &r.origin), r.direction);
        t = numerator / denominator;

        if (t > 0.0f && t < magnitude(r.direction)) {
            Point3D intersection = vectorAdd(&r.origin, vectorMultiply(&r.direction, t));
            printf("Hit at %f, %f, %f\n", intersection.x, intersection.y, intersection.z);
            return;
        }
    }

    printf("No hit.\n");
}

// Function to subtract two vectors
Vector3D* vectorSubtract(Vector3D* v1, Vector3D* v2) {
    Vector3D* result = (Vector3D*)malloc(sizeof(Vector3D));
    result->x = v1->x - v2->x;
    result->y = v1->y - v2->y;
    result->z = v1->z - v2->z;
    return result;
}

// Function to multiply a vector by a scalar
Vector3D* vectorMultiply(Vector3D* v, float scalar) {
    Vector3D* result = (Vector3D*)malloc(sizeof(Vector3D));
    result->x = v->x * scalar;
    result->y = v->y * scalar;
    result->z = v->z * scalar;
    return result;
}

// Function to add two vectors
Vector3D* vectorAdd(Vector3D* v1, Vector3D* v2) {
    Vector3D* result = (Vector3D*)malloc(sizeof(Vector3D));
    result->x = v1->x + v2->x;
    result->y = v1->y + v2->y;
    result->z = v1->z + v2->z;
    return result;
}

int main() {
    // Define 3D points and vectors
    Point3D point1 = {1.0f, 2.0f, 3.0f};
    Vector3D vector1 = {4.0f, 5.0f, 6.0f};
    Vector3D vector2 = {7.0f, 8.0f, 9.0f};

    // Create a ray
    Ray r;
    r.origin.x = point1.x;
    r.origin.y = point1.y;
    r.origin.z = point1.z;
    r.direction.x = vector1.x;
    r.direction.y = vector1.y;
    r.direction.z = vector1.z;

    // Define 3D objects
    Point3D* objects[2];
    objects[0] = &point1;
    objects[1] = &point1; // Same object as point1

    // Cast the ray and detect collisions
    castRay(r, objects, 2);

    return 0;
}