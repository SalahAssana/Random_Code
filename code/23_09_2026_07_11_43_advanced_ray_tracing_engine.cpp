#include <iostream>
#include <vector>
#include <cmath>

// Structure to represent 3D points
struct Vector3 {
    float x, y, z;
};

// Function to calculate distance between two points
float Distance(const Vector3& p1, const Vector3& p2) {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2) + std::pow(p2.z - p1.z, 2));
}

// Class to represent a ray
class Ray {
public:
    Vector3 origin;
    Vector3 direction;

    // Constructor for the ray
    Ray(const Vector3& o, const Vector3& d) : origin(o), direction(d) {}
};

// Function to cast a ray and find the intersection with a sphere
Vector3 CastRayAndFindIntersection(const Ray& r, const Vector3& center, float radius) {
    Vector3 difference = r.origin - center;
    float dotProduct = DotProduct(r.direction, difference);
    float denominator = DotProduct(r.direction, r.direction);
    float t = (-2 * dotProduct + std::sqrt(std::pow(dotProduct, 2) + (dotProduct * dotProduct * dotProduct) / denominator)) / denominator;

    Vector3 intersectionPoint = r.origin + t * r.direction;
    if (Distance(intersectionPoint, center) <= radius) {
        return intersectionPoint;
    } else {
        return {0, 0, 0}; // Ray did not intersect the sphere
    }
}

// Function to calculate the dot product of two vectors
float DotProduct(const Vector3& v1, const Vector3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

int main() {
    // Define some sample data for testing
    Vector3 sphereCenter = {0, 0, -10};
    float sphereRadius = 5;
    Ray ray = {Vector3{0, 0, 0}, Vector3{0, 0, 1}};

    Vector3 intersectionPoint = CastRayAndFindIntersection(ray, sphereCenter, sphereRadius);

    std::cout << "Intersection point: (" << intersectionPoint.x << ", " << intersectionPoint.y << ", " << intersectionPoint.z << ")" << std::endl;

    return 0;
}