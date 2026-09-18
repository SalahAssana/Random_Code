#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define a structure to represent a traffic entity (car or pedestrian)
typedef struct {
    int id;
    char type; // 'C' for car, 'P' for pedestrian
    int speed;
    int direction; // 0 for forward, 1 for backward
} TrafficEntity;

// Function to generate random traffic entities
TrafficEntity* generateEntities(int numEntities) {
    TrafficEntity* entities = (TrafficEntity*)malloc(numEntities * sizeof(TrafficEntity));
    
    srand(time(NULL)); // Seed the random number generator
    
    for (int i = 0; i < numEntities; i++) {
        entities[i].id = i;
        entities[i].type = rand() % 2 ? 'C' : 'P'; // Randomly choose car or pedestrian
        entities[i].speed = rand() % 50 + 1; // Speed between 1 and 50 km/h
        entities[i].direction = rand() % 2; // Random direction (0 for forward, 1 for backward)
    }
    
    return entities;
}

// Function to print the traffic pattern
void printPattern(TrafficEntity* entities, int numEntities) {
    printf("Traffic Pattern:\n");
    for (int i = 0; i < numEntities; i++) {
        printf("%c %d km/h (%s)\n", entities[i].type, entities[i].speed, entities[i].direction ? "backward" : "forward");
    }
}

// Main function
int main() {
    int numEntities = 10;
    TrafficEntity* entities = generateEntities(numEntities);
    
    printPattern(entities, numEntities);
    
    free(entities); // Free the memory allocated for the entities
    
    return 0;
}