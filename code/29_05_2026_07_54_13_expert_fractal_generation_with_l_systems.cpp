#include <iostream>
#include <vector>
#include <cmath>

// L-system constants
const int MAX_ITERATIONS = 10000;
const double AXIOM_LENGTH = 10.0; // length of axiom string
const double PROBABILITY = 0.5; // probability of choosing an angle

struct Point {
    double x, y;
};

void generateFractal(std::vector<Point>& points, int iterations) {
    if (iterations > MAX_ITERATIONS)
        return;

    // Initialize axiom string
    std::string axiom(AXIOM_LENGTH, 'F');
    axiom[0] = 'X';

    for (int i = 0; i < iterations; ++i) {
        std::string nextIteration;
        for (char c : axiom) {
            if (c == 'X') {
                if (rand() % 2)
                    nextIteration += "F-";
                else
                    nextIteration += "+FX";
            } else if (c == 'F') {
                nextIteration += "FF";
            }
        }
        axiom = nextIteration;
    }

    // Parse fractal string and generate points
    for (int i = 0; i < axiom.length(); ++i) {
        char c = axiom[i];
        if (c == 'X') {
            double dx = AXIOM_LENGTH / (AXIOM_LENGTH + 1);
            points.push_back({points.back().x + dx, points.back().y});
        } else if (c == 'F') {
            double dx = AXIOM_LENGTH / (AXIOM_LENGTH + 1);
            double dy = sin(i * M_PI / AXIOM_LENGTH) * dx;
            points.push_back({points.back().x + dx, points.back().y + dy});
        } else if (c == '+') {
            points.back().x += cos(i * M_PI / AXIOM_LENGTH) * AXIOM_LENGTH / (AXIOM_LENGTH + 1);
        }
    }
}

int main() {
    srand(time(0)); // seed random number generator

    std::vector<Point> points;
    generateFractal(points, 5);

    for (const auto& point : points)
        std::cout << "(" << point.x << ", " << point.y << ")\n";

    return 0;
}