#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Define the game board dimensions (adjust as needed)
#define WIDTH 50
#define HEIGHT 25

// Define the cell states (0: dead, 1: alive)
typedef enum { DEAD, ALIVE } CellState;

// Define a struct to hold cell information
typedef struct {
    CellState state;
    int x, y; // coordinates on the board
} Cell;

// Function to initialize the game board with random cells
void init_board(Cell** board) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int rand_num = rand() % 2;
            if (rand_num == 1)
                board[i][j].state = ALIVE;
            else
                board[i][j].state = DEAD;
            board[i][j].x = j;
            board[i][j].y = i;
        }
    }
}

// Function to print the game board
void print_board(Cell** board) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j].state == ALIVE)
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }
}

// Function to update the game board using parallel threads
void* update_board(void* arg) {
    Cell** board = (Cell**)arg;
    int num_threads = 4; // adjust as needed

    pthread_t threads[num_threads];
    for (int i = 0; i < num_threads; i++) {
        int start_row = i * HEIGHT / num_threads;
        int end_row = (i + 1) * HEIGHT / num_threads;
        pthread_create(&threads[i], NULL, update_board_thread, board + start_row);
    }

    for (int i = 0; i < num_threads; i++)
        pthread_join(threads[i]);

    return NULL;
}

// Thread function to update a portion of the game board
void* update_board_thread(void* arg) {
    Cell** board = (Cell**)arg;
    int start_row = pthread_get_spu_id() * HEIGHT / 4;
    int end_row = (pthread_get_spu_id() + 1) * HEIGHT / 4;

    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < WIDTH; j++) {
            Cell& cell = board[i][j];
            int live_neighbors = count_live_neighbors(board, i, j);
            if (cell.state == ALIVE && (live_neighbors < 2 || live_neighbors > 3))
                cell.state = DEAD;
            else if (cell.state == DEAD && live_neighbors == 3)
                cell.state = ALIVE;
        }
    }

    return NULL;
}

// Function to count the number of live neighbors for a given cell
int count_live_neighbors(Cell** board, int x, int y) {
    int count = 0;

    // Check eight neighboring cells
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0)
                continue;
            int nx = x + i;
            int ny = y + j;

            // Ensure valid coordinates
            if (nx >= 0 && nx < HEIGHT && ny >= 0 && ny < WIDTH) {
                if (board[nx][ny].state == ALIVE)
                    count++;
            }
        }
    }

    return count;
}

int main() {
    // Initialize the game board with random cells
    Cell** board = (Cell**)malloc(HEIGHT * sizeof(Cell*));
    for (int i = 0; i < HEIGHT; i++)
        board[i] = (Cell*)malloc(WIDTH * sizeof(Cell));

    init_board(board);

    // Simulate the Game of Life using parallel threads
    pthread_t thread;
    pthread_create(&thread, NULL, update_board, board);
    pthread_join(thread);

    // Print the final game board state
    print_board(board);

    for (int i = 0; i < HEIGHT; i++)
        free(board[i]);
    free(board);

    return 0;
}