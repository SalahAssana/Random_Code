#include <iostream>
#include <cmath>

using namespace std;

// Function to multiply two matrices
void multiplyMatrices(int** matrix1, int** matrix2, int** result, int rows1, int cols1, int rows2, int cols2) {
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            int sum = 0;
            for (int k = 0; k < cols1; k++) {
                sum += matrix1[i][k] * matrix2[k][j];
            }
            result[i][j] = sum;
        }
    }
}

// Function to print a matrix
void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to generate a random matrix
void generateRandomMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

// Function to check if two matrices are equal
bool checkMatrixEquality(int** matrix1, int** matrix2, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix1[i][j] != matrix2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Function to calculate the product of two matrices
void multiplyAndVerify(int** matrix1, int** matrix2, int** result) {
    // Calculate the product
    int rows1 = 3;
    int cols1 = 3;
    int rows2 = 3;
    int cols2 = 2;

    if (cols1 != rows2) {
        cout << "Error: Matrix multiplication is not possible." << endl;
        return;
    }

    multiplyMatrices(matrix1, matrix2, result, rows1, cols1, rows2, cols2);

    // Print the product
    cout << "Matrix 1:" << endl;
    printMatrix(matrix1, rows1, cols1);
    cout << "Matrix 2:" << endl;
    printMatrix(matrix2, rows2, cols2);
    cout << "Product:" << endl;
    printMatrix(result, rows1, cols2);

    // Check if the product is correct
    int** expectedResult = new int*[rows1];
    for (int i = 0; i < rows1; i++) {
        expectedResult[i] = new int[cols2];
    }

    generateRandomMatrix(expectedResult, rows1, cols2);

    bool areEqual = checkMatrixEquality(result, expectedResult, rows1, cols2);
    if (!areEqual) {
        cout << "Error: Product is not correct." << endl;
    }
}

int main() {
    // Generate random matrices
    int** matrix1 = new int*[3];
    for (int i = 0; i < 3; i++) {
        matrix1[i] = new int[3];
    }

    int** matrix2 = new int*[3];
    for (int i = 0; i < 3; i++) {
        matrix2[i] = new int[2];
    }

    generateRandomMatrix(matrix1, 3, 3);
    generateRandomMatrix(matrix2, 3, 2);

    // Calculate and verify the product
    int** result = new int*[3];
    for (int i = 0; i < 3; i++) {
        result[i] = new int[2];
    }

    multiplyAndVerify(matrix1, matrix2, result);

    // Free memory
    for (int i = 0; i < 3; i++) {
        delete[] matrix1[i];
        delete[] matrix2[i];
        delete[] result[i];
    }
    delete[] matrix1;
    delete[] matrix2;
    delete[] result;

    return 0;
}