#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <random>

using namespace std;

class TrafficLight {
public:
    enum class Color { RED, GREEN, YELLOW };
    queue<Color> colors;
    int duration;

    TrafficLight(int redDuration, int greenDuration) : 
        duration(redDuration + greenDuration), 
        colors({Color::RED, Color::GREEN}) {}

    void cycle() {
        while (!colors.empty()) {
            auto color = colors.front();
            for (int i = 0; i < duration / (color == Color::RED ? 1 : 2); i++) {
                cout << "Traffic light is " << ((color == Color::RED) ? "red" : (color == Color::GREEN) ? "green" : "yellow") << endl;
                this_thread::sleep_for(chrono::seconds(1));
            }
            colors.pop();
            if (!colors.empty()) {
                cout << "Traffic light is now " << ((colors.front() == Color::RED) ? "red" : (colors.front() == Color::GREEN) ? "green" : "yellow") << endl;
            }
        }
    }
};

class Car {
public:
    enum class Direction { LEFT, RIGHT };
    int speed;
    Direction direction;

    Car(int speed, Direction direction) : 
        speed(speed), 
        direction(direction) {}

    void drive() {
        for (int i = 0; i < speed; i++) {
            cout << "Car is moving " << ((direction == Direction::LEFT) ? "left" : "right") << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
};

class Pedestrian {
public:
    enum class Action { WALK, STOP };
    int speed;
    Action action;

    Pedestrian(int speed, Action action) : 
        speed(speed), 
        action(action) {}

    void walk() {
        for (int i = 0; i < speed; i++) {
            cout << "Pedestrian is walking" << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
};

class Intersection {
public:
    map<string, TrafficLight> lights;
    queue<Car> cars;
    queue<Pedestrian> pedestrians;

    void addCar(Car car) { cars.push(car); }
    void addPedestrian(Pedestrian pedestrian) { pedestrians.push(pedestrian); }

    void simulate() {
        while (!cars.empty()) {
            Car car = cars.front();
            car.drive();
            cars.pop();
        }

        while (!pedestrians.empty()) {
            Pedestrian pedestrian = pedestrians.front();
            if (pedestrian.action == Pedestrian::WALK) {
                pedestrian.walk();
            }
            pedestrians.pop();
        }
    }
};

int main() {
    TrafficLight trafficLight1(10, 5);
    TrafficLight trafficLight2(15, 10);

    Intersection intersection;
    intersection.lights["light1"] = trafficLight1;
    intersection.lights["light2"] = trafficLight2;

    Car car1(3, Car::Direction::LEFT);
    Car car2(4, Car::Direction::RIGHT);

    Pedestrian pedestrian1(2, Pedestrian::WALK);
    Pedestrian pedestrian2(3, Pedestrian::STOP);

    intersection.addCar(car1);
    intersection.addCar(car2);
    intersection.addPedestrian(pedestrian1);
    intersection.addPedestrian(pedestrian2);

    trafficLight1.cycle();
    trafficLight2.cycle();

    intersection.simulate();

    return 0;
}