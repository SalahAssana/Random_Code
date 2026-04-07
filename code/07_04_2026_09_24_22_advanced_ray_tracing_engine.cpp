#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

// Structure to represent 3D points
struct Point3D {
    float x, y, z;
};

// Structure to represent a ray
struct Ray {
    Point3D origin;
    Point3D direction;
};

// Structure to represent a sphere
struct Sphere {
    Point3D center;
    float radius;
};

// Class to represent a 3D scene
class Scene {
public:
    std::vector<Sphere> spheres;

    // Function to add a sphere to the scene
    void AddSphere(float x, float y, float z, float r) {
        Sphere s;
        s.center = {x, y, z};
        s.radius = r;
        spheres.push_back(s);
    }
};

// Class to represent a light source
class Light {
public:
    Point3D position;
    float intensity;

    // Constructor for the light source
    Light(float x, float y, float z, float i) : position({x, y, z}), intensity(i) {}
};

// Function to calculate the intersection of a ray with a sphere
Point3D RaySphereIntersection(Ray r, Sphere s) {
    Point3D p = r.origin;
    Point3D d = r.direction;

    // Calculate the vector from the sphere center to the ray origin
    Point3D L = {s.center.x - p.x, s.center.y - p.y, s.center.z - p.z};

    // Calculate the dot product of the light vector and the ray direction
    float tca = (L.x * d.x + L.y * d.y + L.z * d.z);

    // Calculate the square magnitude of the light vector
    float flen2 = L.x * L.x + L.y * L.y + L.z * L.z;

    // Check if the ray intersects with the sphere
    if (tca >= 0 && tca <= flen2) {
        // Calculate the distance from the origin to the intersection point
        float denominator = d.x * d.x + d.y * d.y + d.z * d.z;
        float numerator = 2 * (L.x * d.x + L.y * d.y + L.z * d.z);

        // Calculate the t value for the intersection
        float t = (-tca + sqrt(tca * tca - denominator)) / denominator;

        // Calculate the intersection point
        Point3D pIntersect;
        pIntersect.x = p.x + t * d.x;
        pIntersect.y = p.y + t * d.y;
        pIntersect.z = p.z + t * d.z;

        return pIntersect;
    } else {
        // Ray does not intersect with the sphere
        return {0, 0, 0};
    }
}

// Function to perform ray tracing and render the scene
void RayTracing(Scene& s) {
    std::ofstream output("output.ppm");
    output << "P3\n" << 512 << " " << 512 << "\n255\n";

    for (int y = 0; y < 512; y++) {
        for (int x = 0; x < 512; x++) {
            Ray r;
            r.origin.x = -1 + (x * 2) / 512;
            r.origin.y = -1 + (y * 2) / 512;
            r.origin.z = -1;

            r.direction.x = 0;
            r.direction.y = 0;
            r.direction.z = 1;

            for (auto& sphere : s.spheres) {
                Point3D pIntersect = RaySphereIntersection(r, sphere);
                if (pIntersect.x != 0 || pIntersect.y != 0 || pIntersect.z != 0) {
                    output << "255 255 255\n";
                    return;
                }
            }

            output << "0 0 0\n";
        }
    }
}

int main() {
    Scene s;

    // Add spheres to the scene
    for (int i = 0; i < 10; i++) {
        float x = static_cast<float>(rand()) / RAND_MAX * 2 - 1;
        float y = static_cast<float>(rand()) / RAND_MAX * 2 - 1;
        float z = static_cast<float>(rand()) / RAND_MAX * 2;
        float r = static_cast<float>(rand()) / RAND_MAX + 0.5;

        s.AddSphere(x, y, z, r);
    }

    // Perform ray tracing and render the scene
    RayTracing(s);

    return 0;
}
