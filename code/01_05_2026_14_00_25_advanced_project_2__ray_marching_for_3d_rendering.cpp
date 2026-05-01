#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

// Structure to represent 3D points
struct Point3D {
    float x, y, z;
};

// Class to represent a ray
class Ray {
public:
    Point3D origin;
    Point3D direction;

    // Constructor for ray
    Ray(Point3D o, Point3D d) : origin(o), direction(d) {}
};

// Class to represent a sphere
class Sphere {
public:
    Point3D center;
    float radius;

    // Constructor for sphere
    Sphere(Point3D c, float r) : center(c), radius(r) {}
};

// Function to calculate the distance from the ray origin to the point
float distanceToOrigin(const Ray& ray, const Point3D& point) {
    return sqrt(pow(point.x - ray.origin.x, 2) + pow(point.y - ray.origin.y, 2) + pow(point.z - ray.origin.z, 2));
}

// Function to perform ray-sphere intersection
bool intersectRaySphere(const Ray& ray, const Sphere& sphere, float& t) {
    Point3D L = {ray.origin.x - sphere.center.x, ray.origin.y - sphere.center.y, ray.origin.z - sphere.center.z};
    float tca = dotProduct(L, sphere.direction);
    float d2 = lengthSquared(L) - pow(tca, 2);

    if (d2 < 0) {
        return false;
    }

    float thc = sqrt(d2);
    t = tca - thc;

    return true;
}

// Function to perform ray-marching
void marchRay(const Ray& ray, const std::vector<Sphere>& spheres, int& depth, float& color) {
    float t = 0;
    Point3D p = {ray.origin.x, ray.origin.y, ray.origin.z};

    for (int i = 0; i < depth; i++) {
        bool hit = false;

        for (const auto& sphere : spheres) {
            if (intersectRaySphere(ray, sphere, t)) {
                p = {sphere.center.x + sphere.radius * sin(t), sphere.center.y + sphere.radius * cos(t), sphere.center.z};
                hit = true;
                break;
            }
        }

        if (!hit) {
            break;
        }

        color = 0.5f; // Simple diffuse lighting
    }
}

// Function to perform dot product
float dotProduct(const Point3D& a, const Point3D& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Function to calculate the length squared of a vector
float lengthSquared(const Point3D& v) {
    return pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2);
}

int main() {
    // Define the spheres
    std::vector<Sphere> spheres = {
        Sphere({0.5f, 0.5f, 0.5f}, 0.1f),
        Sphere({-0.3f, -0.3f, -0.3f}, 0.2f)
    };

    // Define the ray
    Ray ray({0.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.5f});

    // Perform ray-marching
    int depth = 10;
    float color = 0.0f;

    marchRay(ray, spheres, depth, color);

    std::cout << "Color: " << color << std::endl;

    return 0;
}