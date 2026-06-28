#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// Struct to represent 3D point
struct Point {
    float x, y, z;
};

// Struct to represent 3D vector
struct Vector {
    float x, y, z;

    Vector(float x = 0.0f, float y = 0.0f, float z = 0.0f)
        : x(x), y(y), z(z) {}

    float dot(const Vector& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    float magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector normalize() const {
        float m = magnitude();
        return Vector(x / m, y / m, z / m);
    }
};

// Struct to represent 3D ray
struct Ray {
    Point origin;
    Vector direction;

    Ray(Point origin, Vector direction)
        : origin(origin), direction(direction) {}
};

// Struct to represent 3D sphere
struct Sphere {
    Point center;
    float radius;

    Sphere(Point center, float radius)
        : center(center), radius(radius) {}
};

// Function to intersect a ray with a sphere
bool intersectSphere(Ray& ray, Sphere& sphere, Point& intersection) {
    Vector L = Vector(ray.origin.x - sphere.center.x,
                       ray.origin.y - sphere.center.y,
                       ray.origin.z - sphere.center.z);
    float tca = L.dot(sphere.direction);
    if (tca < 0.0f || std::abs(tca) > ray.direction.magnitude() * sphere.radius) {
        return false;
    }

    float d2 = L.dot(L) - tca * tca;
    if (d2 > sphere.radius * sphere.radius) {
        return false;
    }

    float thc = std::sqrt(d2);
    float t0 = tca - thc;
    float t1 = tca + thc;

    intersection.x = ray.origin.x + t1 * ray.direction.x;
    intersection.y = ray.origin.y + t1 * ray.direction.y;
    intersection.z = ray.origin.z + t1 * ray.direction.z;

    return true;
}

// Function to render a scene
void renderScene(const std::vector<Sphere>& spheres, int width, int height) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Point pixel(x / float(width - 1) * 2.0f - 1.0f,
                         -(y / float(height - 1)) * 2.0f - 1.0f);

            Ray ray(pixel, Vector(0.0f, 0.0f, 1.0f));

            Sphere closestSphere;
            Point intersection;

            bool hit = false;
            for (const auto& sphere : spheres) {
                if (intersectSphere(ray, sphere, intersection)) {
                    if (!hit || std::sqrt((intersection.x - pixel.x) * (intersection.x - pixel.x) +
                                          (intersection.y - pixel.y) * (intersection.y - pixel.y) +
                                          (intersection.z - pixel.z) * (intersection.z - pixel.z)) <
                        std::sqrt((closestSphere.center.x - pixel.x) * (closestSphere.center.x - pixel.x) +
                                  (closestSphere.center.y - pixel.y) * (closestSphere.center.y - pixel.y) +
                                  (closestSphere.center.z - pixel.z) * (closestSphere.center.z - pixel.z))) {
                        closestSphere = sphere;
                    }
                    hit = true;
                }
            }

            if (hit) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    Point light(0.0f, 0.0f, -1.0f);

    std::vector<Sphere> spheres = {
        Sphere(Point(-0.5f, 0.0f, 0.0f), 1.0f),
        Sphere(Point(0.5f, 0.0f, 0.0f), 1.0f)
    };

    renderScene(spheres, 80, 25);

    return 0;
}