#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POPULATION_SIZE 1000
#define GENERATIONS 500

typedef struct {
    int x, y; // agent's position on a grid
    int age; // agent's age
} Agent;

Agent* agents;
int* grid[POPULATION_SIZE][2]; // grid to represent the environment

void initialize_agents() {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        agents[i].x = rand() % POPULATION_SIZE;
        agents[i].y = rand() % POPULATION_SIZE;
        agents[i].age = rand() % 100;
    }
}

void update_agents() {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        int x = agents[i].x + rand() % 3 - 1;
        int y = agents[i].y + rand() % 3 - 1;
        if (x >= 0 && x < POPULATION_SIZE && y >= 0 && y < POPULATION_SIZE) {
            agents[i].x = x;
            agents[i].y = y;
        }
    }
}

void print_grid() {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (int j = 0; j < POPULATION_SIZE; j++) {
            if (grid[i][j]) printf("1 ");
            else printf("0 ");
        }
        printf("\n");
    }
}

void main() {
    srand(time(NULL));
    agents = (Agent*)malloc(POPULATION_SIZE * sizeof(Agent));
    for (int i = 0; i < POPULATION_SIZE; i++) {
        grid[i][0] = (int*)malloc((2 + i) * sizeof(int));
        grid[i][1] = (int*)malloc((2 + i) * sizeof(int));
    }

    initialize_agents();
    for (int generation = 0; generation < GENERATIONS; generation++) {
        update_agents();
        printf("Generation %d:\n", generation);
        print_grid();
    }
}