#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define the fractal generator struct
typedef struct {
    double x;
    double y;
} Point;

// Function to generate a Sierpinski triangle
void sierpinski(Point *points, int num_points, double scale) {
    // Base case: If there are only 3 points, return
    if (num_points <= 3) {
        return;
    }

    // Calculate the midpoint of each side
    Point mid1 = { (points[0].x + points[1].x) / 2,
                    (points[0].y + points[1].y) / 2 };
    Point mid2 = { (points[1].x + points[2].x) / 2,
                    (points[1].y + points[2].y) / 2 };
    Point mid3 = { (points[0].x + points[2].x) / 2,
                    (points[0].y + points[2].y) / 2 };

    // Recursively generate the smaller triangles
    sierpinski(&mid1, num_points / 2, scale * 0.5);
    sierpinski(&mid2, num_points / 2, scale * 0.5);
    sierpinski(&mid3, num_points / 2, scale * 0.5);

    // Draw the triangles
    for (int i = 0; i < num_points; i++) {
        printf("Point (%f, %f)\n", points[i].x * scale, points[i].y * scale);
    }
}

// Function to generate a Koch curve
void koch_curve(Point *points, int num_points) {
    // Base case: If there are only 4 points, return
    if (num_points <= 4) {
        return;
    }

    // Calculate the midpoint of each side
    Point mid1 = { (points[0].x + points[1].x) / 2,
                    (points[0].y + points[1].y) / 2 };
    Point mid2 = { (points[1].x + points[2].x) / 2,
                    (points[1].y + points[2].y) / 2 };
    Point mid3 = { (points[0].x + points[2].x) / 2,
                    (points[0].y + points[2].y) / 2 };

    // Recursively generate the smaller triangles
    koch_curve(&mid1, num_points / 4);
    koch_curve(&mid2, num_points / 4);
    koch_curve(&mid3, num_points / 4);

    // Draw the curve
    for (int i = 0; i < num_points; i++) {
        printf("Point (%f, %f)\n", points[i].x, points[i].y);
    }
}

// Main function to generate and print fractals
int main() {
    // Initialize the points array
    Point *points = (Point *)malloc(1024 * sizeof(Point));

    // Generate a Sierpinski triangle
    sierpinski(points, 1024, 1);

    // Generate a Koch curve
    koch_curve(points, 1024);

    // Free the memory
    free(points);

    return 0;
}