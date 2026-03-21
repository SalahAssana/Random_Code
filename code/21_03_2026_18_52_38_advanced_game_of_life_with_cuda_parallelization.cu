#include <cuda_runtime.h>
#include <device_launch_configuration.h>

// Define Game of Life constants
const int BOARD_SIZE = 100;
const int GENERATIONS = 1000;

// Define Game of Life struct for cell state
struct Cell {
    bool alive;
};

// CUDA kernel function to simulate Game of Life
__global__ void gameOfLifeKernel(Cell* d_board, Cell* d_nextBoard) {
    // Calculate the global thread index
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    // Check if the current cell is within the board boundaries
    if (idx >= BOARD_SIZE || idx < 0) return;

    // Load the current cell state from device memory
    Cell currCell;
    currCell.alive = d_board[idx].alive;

    // Calculate the number of live neighbors
    int liveNeighbors = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int neighborIdx = idx + i * BOARD_SIZE + j;
            liveNeighbors += d_board[neighborIdx].alive;
        }
    }

    // Apply Game of Life rules to determine the next cell state
    Cell nextCell;
    if (currCell.alive) {
        if (liveNeighbors < 2 || liveNeighbors > 3) nextCell.alive = false;
        else nextCell.alive = true;
    } else {
        if (liveNeighbors == 3) nextCell.alive = true;
        else nextCell.alive = false;
    }

    // Store the next cell state in device memory
    d_nextBoard[idx].alive = nextCell.alive;
}

// CUDA host function to manage Game of Life simulation
void gameOfLifeHost(Cell* h_board, Cell* d_board, int generations) {
    // Allocate device memory for the board and next board
    Cell* d_nextBoard;
    cudaMalloc((void**)&d_nextBoard, BOARD_SIZE * sizeof(Cell));

    // Perform each generation
    for (int i = 0; i < generations; i++) {
        // Copy current board to device memory
        cudaMemcpy(d_board, h_board, BOARD_SIZE * sizeof(Cell), cudaMemcpyHostToDevice);

        // Launch CUDA kernel to simulate Game of Life
        int blockSize = 256;
        int numBlocks = (BOARD_SIZE + blockSize - 1) / blockSize;
        gameOfLifeKernel<<<numBlocks, blockSize>>>(d_board, d_nextBoard);

        // Copy next board from device memory to host memory
        cudaMemcpy(h_board, d_nextBoard, BOARD_SIZE * sizeof(Cell), cudaMemcpyDeviceToHost);

        // Free device memory for the next board
        cudaFree(d_nextBoard);
    }

    // Free device memory for the current board
    cudaFree(d_board);
}

// Main function to test Game of Life simulation
int main() {
    // Initialize host memory for the board and next board
    Cell* h_board = new Cell[BOARD_SIZE];
    Cell* d_board;
    cudaMalloc((void**)&d_board, BOARD_SIZE * sizeof(Cell));

    // Initialize the board with random cell states
    srand(time(0));
    for (int i = 0; i < BOARD_SIZE; i++) {
        h_board[i].alive = (rand() % 2 == 1);
    }

    // Perform a specified number of generations
    gameOfLifeHost(h_board, d_board, GENERATIONS);

    // Clean up memory and device resources
    delete[] h_board;
    cudaFree(d_board);

    return 0;
}