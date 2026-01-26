#include <iostream>
#include <vector>

// Function to multiply two matrices
std::vector<std::vector<int>> multiplyMatrices(const std::vector<std::vector<int>>& matrix1,
                                                 const std::vector<std::vector<int>>& matrix2) {
    int rowsMatrix1 = matrix1.size();
    int colsMatrix1 = matrix1[0].size();
    int rowsMatrix2 = matrix2.size();
    int colsMatrix2 = matrix2[0].size();

    // Check if matrices can be multiplied
    if (colsMatrix1 != rowsMatrix2) {
        std::cout << "Matrices cannot be multiplied" << std::endl;
        return {};
    }

    // Initialize result matrix with zeros
    std::vector<std::vector<int>> result(rowsMatrix1, std::vector<int>(colsMatrix2, 0));

    // Multiply matrices
    for (int i = 0; i < rowsMatrix1; ++i) {
        for (int j = 0; j < colsMatrix2; ++j) {
            int sum = 0;
            for (int k = 0; k < colsMatrix1; ++k) {
                sum += matrix1[i][k] * matrix2[k][j];
            }
            result[i][j] = sum;
        }
    }

    return result;
}

// Function to print a matrix
void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

// Main function
int main() {
    // Define two matrices
    std::vector<std::vector<int>> matrix1 = {{1, 2, 3}, {4, 5, 6}};
    std::vector<std::vector<int>> matrix2 = {{7, 8}, {9, 10}, {11, 12}};

    // Multiply matrices
    auto result = multiplyMatrices(matrix1, matrix2);

    // Print the result
    std::cout << "Result:" << std::endl;
    printMatrix(result);

    return 0;
}