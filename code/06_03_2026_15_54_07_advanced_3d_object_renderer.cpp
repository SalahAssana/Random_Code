#include <iostream>
#include <vector>
#include <cmath>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// Class representing a 3D point
class Point3D {
public:
    double x, y, z;
    Point3D(double _x = 0.0, double _y = 0.0, double _z = 0.0) : x(_x), y(_y), z(_z) {}
};

// Class representing a ray
class Ray {
public:
    Point3D origin;
    Vector3d direction;
    Ray(Point3D _origin, Vector3d _direction) : origin(_origin), direction(_direction) {}
};

// Function to perform ray tracing and calculate intersection points
Point3D traceRay(Ray& r, vector<vector<Point3D>>& vertices) {
    Point3D closest = {INFINITY, INFINITY, INFINITY};
    double minDistance = INFINITY;

    for (int i = 0; i < vertices.size(); i++) {
        for (int j = 0; j < vertices[i].size(); j++) {
            Point3D v1 = vertices[i][j];
            if (i + 1 < vertices.size()) {
                Point3D v2 = vertices[i + 1][j];
            } else if (j + 1 < vertices[i].size()) {
                Point3D v2 = vertices[i][j + 1];
            } else {
                continue;
            }
            Point3D v3;

            if (i == vertices.size() - 1 && j == vertices[i].size() - 1) {
                v3 = vertices[0][0]; // Close the triangle
            } else if (j + 1 < vertices[i].size()) {
                v3 = vertices[i][j + 1];
            } else {
                i++;
                j = 0;
                continue;
            }

            Vector3d edge1(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
            Vector3d edge2(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
            Vector3d direction = r.direction;
            double a = dot(edge1, edge1);
            double b = 2.0 * (dot(edge1, edge2));
            double c = dot(edge2, edge2) - 1.0;

            double determinant = b * b - 4.0 * a * c;
            if (determinant < 0.0) {
                continue; // No intersection
            }

            double t = (-b - sqrt(determinant)) / (2.0 * a);
            Point3D intersection = v1 + direction * t;

            double distance = (r.origin.x - intersection.x) * (r.origin.x - intersection.x) +
                              (r.origin.y - intersection.y) * (r.origin.y - intersection.y) +
                              (r.origin.z - intersection.z) * (r.origin.z - intersection.z);

            if (distance < minDistance) {
                closest = intersection;
                minDistance = distance;
            }
        }
    }

    return closest;
}

int main() {
    vector<vector<Point3D>> vertices = {
        {{0, 0, 0}, {1, 0, 0}, {1, 1, 0}},
        {{1, 1, 0}, {0, 1, 0}, {0, 0, 0}},
        {{0, 0, 1}, {1, 0, 1}, {1, 1, 1}},
        {{1, 1, 1}, {0, 1, 1}, {0, 0, 1}}
    };

    Ray ray({0.5, 0.5, 2.5}, Vector3d(0, 0, -1));

    Point3D intersection = traceRay(ray, vertices);

    cout << "Intersection point: (" << intersection.x << ", " << intersection.y << ", " << intersection.z << ")" << endl;

    return 0;
}