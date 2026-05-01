#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the structure for traffic simulation data
typedef struct {
    int id; // Unique identifier for each car/pedestrian
    int x;   // Current position on the grid (x-coordinate)
    int y;   // Current position on the grid (y-coordinate)
    char type; // Car or pedestrian ('C' or 'P')
} TrafficEntity;

// Define the structure for traffic lights and their timing
typedef struct {
    int id;  // Unique identifier for each intersection
    int redTime; // Time spent in red light state
    int yellowTime; // Time spent in yellow light state
    int greenTime; // Time spent in green light state
} TrafficLight;

// Function to initialize traffic entities and lights
void initSimulation(int numCars, int numPedestrians, int numIntersections) {
    // Initialize random number generator for entity movement
    srand(time(NULL));
    
    // Allocate memory for traffic entities
    TrafficEntity* entities = (TrafficEntity*)malloc((numCars + numPedestrians) * sizeof(TrafficEntity));
    
    // Initialize entities with random positions and types
    for (int i = 0; i < numCars; i++) {
        entities[i].id = i;
        entities[i].x = rand() % 10;
        entities[i].y = rand() % 10;
        entities[i].type = 'C';
    }
    
    for (int i = numCars; i < numCars + numPedestrians; i++) {
        entities[i].id = i;
        entities[i].x = rand() % 10;
        entities[i].y = rand() % 10;
        entities[i].type = 'P';
    }
    
    // Initialize traffic lights
    TrafficLight* lights = (TrafficLight*)malloc(numIntersections * sizeof(TrafficLight));
    
    for (int i = 0; i < numIntersections; i++) {
        lights[i].id = i;
        lights[i].redTime = rand() % 5 + 1;
        lights[i].yellowTime = rand() % 2 + 1;
        lights[i].greenTime = rand() % 3 + 1;
    }
    
    // Free allocated memory
    free(entities);
    free(lights);
}

// Function to simulate traffic flow for a given time step
void updateSimulation(TrafficEntity* entities, TrafficLight* lights) {
    // Simulate movement of each entity based on its type and current position
    for (int i = 0; i < numCars + numPedestrians; i++) {
        if (entities[i].type == 'C') { // Car movement
            // Move car one step in a random direction (up, down, left, right)
            int dx = rand() % 2 - 1;
            int dy = rand() % 2 - 1;
            entities[i].x += dx;
            entities[i].y += dy;
        } else { // Pedestrian movement
            // Move pedestrian one step in a random direction (up, down, left, right)
            int dx = rand() % 2 - 1;
            int dy = rand() % 2 - 1;
            entities[i].x += dx;
            entities[i].y += dy;
        }
    }
    
    // Update traffic lights based on the current state of each intersection
    for (int i = 0; i < numIntersections; i++) {
        if (/* some condition */) { // Red light state
            lights[i].redTime--;
            if (lights[i].redTime == 0) {
                lights[i].state = 'G'; // Green light state
            }
        } else if (/* some condition */) { // Yellow light state
            lights[i].yellowTime--;
            if (lights[i].yellowTime == 0) {
                lights[i].state = 'R'; // Red light state
            }
        } else { // Green light state
            lights[i].greenTime--;
            if (lights[i].greenTime == 0) {
                lights[i].state = 'Y'; // Yellow light state
            }
        }
    }
}

// Function to print the current state of the traffic simulation
void printSimulation(TrafficEntity* entities, TrafficLight* lights) {
    for (int i = 0; i < numCars + numPedestrians; i++) {
        printf("Entity %d: x=%d, y=%d, type='%c'\n", entities[i].id, entities[i].x, entities[i].y, entities[i].type);
    }
    
    for (int i = 0; i < numIntersections; i++) {
        printf("Intersection %d: Red time left=%d, Yellow time left=%d, Green time left=%d\n", lights[i].id, lights[i].redTime, lights[i].yellowTime, lights[i].greenTime);
    }
}

int main() {
    // Initialize traffic simulation with 10 cars, 5 pedestrians, and 3 intersections
    initSimulation(10, 5, 3);
    
    // Simulate traffic flow for 10 time steps
    for (int i = 0; i < 10; i++) {
        updateSimulation(entities, lights);
        printSimulation(entities, lights);
        
        // Wait for a short period before the next simulation step
        sleep(1);
    }
    
    return 0;
}