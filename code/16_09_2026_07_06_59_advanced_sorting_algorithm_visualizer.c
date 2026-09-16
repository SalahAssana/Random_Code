#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

// Define the maximum size of the array
#define MAX_SIZE 100

// Define the types for the data structures
typedef struct {
    int* values;
    int size;
} Array;

// Function to create a new array with random values
Array* newArray(int size) {
    Array* arr = (Array*)malloc(sizeof(Array));
    arr->size = size;
    arr->values = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        arr->values[i] = rand() % 100;
    }

    return arr;
}

// Function to print the array
void printArray(Array* arr) {
    printf("[");
    for (int i = 0; i < arr->size; i++) {
        printf("%d", arr->values[i]);
        if (i < arr->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// Bubble sort function
void bubbleSort(Array* arr) {
    for (int i = 0; i < arr->size; i++) {
        for (int j = 0; j < arr->size - i - 1; j++) {
            if (arr->values[j] > arr->values[j + 1]) {
                int temp = arr->values[j];
                arr->values[j] = arr->values[j + 1];
                arr->values[j + 1] = temp;
            }
        }
    }
}

// Quick sort function
void quickSort(Array* arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

// Partition function for quick sort
int partition(Array* arr, int low, int high) {
    int pivot = arr->values[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr->values[j] <= pivot) {
            i++;
            int temp = arr->values[i];
            arr->values[i] = arr->values[j];
            arr->values[j] = temp;
        }
    }

    int temp = arr->values[i + 1];
    arr->values[i + 1] = arr->values[high];
    arr->values[high] = temp;

    return i + 1;
}

// Function to display the array using SDL
void displayArray(Array* arr, SDL_Renderer* renderer) {
    int width = 800;
    int height = 600;
    int cellSize = width / arr->size;

    for (int i = 0; i < arr->size; i++) {
        int x = i * cellSize;
        int y = height - (arr->values[i] * cellSize) - 20;
        SDL_Rect rect = {x, y, cellSize, cellSize};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Sorting Algorithm Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Failed to create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        return 1;
    }

    srand(time(NULL));

    Array* arr = newArray(MAX_SIZE);

    int selection = 0;
    while (true) {
        switch (selection) {
            case 0:
                bubbleSort(arr);
                break;
            case 1:
                quickSort(arr, 0, arr->size - 1);
                break;
            default:
                printf("Invalid selection. Please enter a number between 0 and 2.\n");
                return 1;
        }

        displayArray(arr, renderer);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return 0;
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_1:
                        selection = 0;
                        break;
                    case SDLK_2:
                        selection = 1;
                        break;
                    default:
                        printf("Invalid key press. Please enter a number between 1 and 2.\n");
                }
            }
        }

        SDL_Delay(100);
    }

    free(arr->values);
    free(arr);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}