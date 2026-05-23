#include <iostream>
#include <vector>
#include <algorithm>

// Forward declaration of classes
class Ray;
class Object3D;

// Class for 2D vector
class Vector2 {
public:
    float x, y;
};

// Class for 3D vector
class Vector3 {
public:
    float x, y, z;
};

// Class for raycasting
class Ray {
public:
    Vector3 origin, direction;
    float length;

    // Constructor
    Ray(Vector3 origin, Vector3 direction, float length) : origin(origin), direction(direction), length(length) {}
};

// Abstract base class for 3D objects
class Object3D {
public:
    virtual bool intersect(Ray& ray) = 0; // Function to check intersection with a ray
    virtual void move(float dx, float dy, float dz) = 0; // Function to move the object

protected:
    Vector3 position;
};

// Class for a moving 3D box
class Box : public Object3D {
public:
    bool intersect(Ray& ray) override {
        // Raycasting algorithm for a 3D box
        float t1 = (ray.origin.x - position.x + ray.direction.x * length) / (ray.direction.x);
        float t2 = (position.x - ray.origin.x - ray.direction.x * length) / (-ray.direction.x);

        if (t1 > t2 && t1 < length) {
            return true;
        }

        t1 = (ray.origin.y - position.y + ray.direction.y * length) / (ray.direction.y);
        t2 = (position.y - ray.origin.y - ray.direction.y * length) / (-ray.direction.y);

        if (t1 > t2 && t1 < length) {
            return true;
        }

        t1 = (ray.origin.z - position.z + ray.direction.z * length) / (ray.direction.z);
        t2 = (position.z - ray.origin.z - ray.direction.z * length) / (-ray.direction.z);

        if (t1 > t2 && t1 < length) {
            return true;
        }

        return false;
    }

    void move(float dx, float dy, float dz) override {
        position.x += dx;
        position.y += dy;
        position.z += dz;
    }
};

// Class for the game engine
class GameEngine {
public:
    std::vector<Object3D*> objects; // Vector of 3D objects

    void update() {
        // Update all objects in the scene
        for (Object3D* obj : objects) {
            obj->move(0.1f, 0.2f, 0.3f);
        }
    }

    void render(Ray& ray) {
        // Render the scene using raycasting
        bool hit = false;
        float t = -1.0f;

        for (Object3D* obj : objects) {
            if (obj->intersect(ray)) {
                if (!hit || t < ray.length) {
                    hit = true;
                    t = ray.length;
                }
            }
        }

        // Output the result
        std::cout << "Ray length: " << t << std::endl;
    }
};

// Main function
int main() {
    GameEngine engine;

    // Create objects in the scene
    Box* box1 = new Box();
    box1->position.x = 0.5f;
    box1->position.y = 0.2f;
    box1->position.z = 0.1f;

    Box* box2 = new Box();
    box2->position.x = -0.3f;
    box2->position.y = -0.4f;
    box2->position.z = -0.5f;

    engine.objects.push_back(box1);
    engine.objects.push_back(box2);

    // Create a ray
    Ray ray(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), 10.0f);

    // Update and render the scene
    engine.update();
    engine.render(ray);

    return 0;
}