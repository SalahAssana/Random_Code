#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define WIDTH 800
#define HEIGHT 600
#define TRACK_LENGTH 1000.0f
#define TRACK_WIDTH 10.0f
#define VELOCITY 100.0f
#define ACCELERATION 50.0f

typedef struct {
    float x, y;
    float velocity;
    float acceleration;
} Car;

Car* cars[5];
float track[TRACK_LENGTH][2];

void initTrack() {
    for (int i = 0; i < TRACK_LENGTH; i++) {
        if (i % (TRACK_WIDTH * 10) < TRACK_WIDTH) {
            track[i][0] = i;
            track[i][1] = 0.5f + sin(i / 20.0f);
        } else {
            track[i][0] = i - TRACK_WIDTH * 10;
            track[i][1] = 2.0f - sin((i - TRACK_WIDTH * 10) / 20.0f);
        }
    }
}

void initCars() {
    for (int i = 0; i < 5; i++) {
        cars[i].x = i % TRACK_WIDTH * 100 + TRACK_WIDTH;
        cars[i].y = sin(i / 4.0f) * HEIGHT / 2.0f;
        cars[i].velocity = VELOCITY;
        cars[i].acceleration = ACCELERATION;
    }
}

void render() {
    for (int i = 0; i < TRACK_LENGTH; i++) {
        printf("%f %f\n", track[i][0], track[i][1]);
    }
    for (int i = 0; i < 5; i++) {
        printf("Car %d: x=%f, y=%f, v=%f\n", i, cars[i].x, cars[i].y, cars[i].velocity);
    }
}

void updateCars() {
    for (int i = 0; i < 5; i++) {
        if (cars[i].x > TRACK_LENGTH) {
            cars[i].x = 0;
            cars[i].y = sin(i / 4.0f) * HEIGHT / 2.0f;
            cars[i].velocity = VELOCITY;
        } else {
            if (cars[i].x + cars[i].velocity < track[(int)round(cars[i].x)[0]) || cars[i].x - cars[i].velocity > track[(int)round(cars[i].x)[0] + 1][0]) {
                cars[i].acceleration = -ACCELERATION;
            } else {
                if (cars[i].y < track[(int)round(cars[i].x)][1]) {
                    cars[i].acceleration = ACCELERATION;
                } else if (cars[i].y > track[(int)round(cars[i].x)][1] + 10.0f) {
                    cars[i].acceleration = -ACCELERATION;
                }
            }
            cars[i].velocity += cars[i].acceleration * 0.01f;
            cars[i].x += cars[i].velocity * 0.01f;
        }
    }
}

int main() {
    srand(time(NULL));
    initTrack();
    initCars();
    while (1) {
        updateCars();
        render();
        sleep(1);
    }
    return 0;
}