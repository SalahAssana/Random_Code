#include <iostream>
using namespace std;

// Function to multiply two matrices
void multiplyMatrices(int A[3][3], int B[3][2], int C[3][2]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            C[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Function to print a matrix
void printMatrix(int matrix[3][2]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int A[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int B[3][2] = {{10, 11}, {12, 13}, {14, 15}};
    int C[3][2];

    // Multiply matrices A and B
    multiplyMatrices(A, B, C);

    // Print the result matrix
    cout << "Matrix product: " << endl;
    printMatrix(C);

    return 0;
}