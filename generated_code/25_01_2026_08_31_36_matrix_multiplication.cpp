#include <iostream>
#include <vector>

// Function to multiply two matrices
std::vector<std::vector<int>> multiplyMatrices(const std::vector<std::vector<int>>& matrix1,
                                                 const std::vector<std::vector<int>>& matrix2) {
    // Get the dimensions of the matrices
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int rows2 = matrix2.size();
    int cols2 = matrix2[0].size();

    // Check if matrices can be multiplied
    if (cols1 != rows2) {
        std::cout << "Matrices cannot be multiplied." << std::endl;
        return {};
    }

    // Create the result matrix with zeros
    std::vector<std::vector<int>> result(rows1, std::vector<int>(cols2, 0));

    // Perform matrix multiplication
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            int sum = 0;
            for (int k = 0; k < cols1; ++k) {
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

int main() {
    // Create the first matrix
    std::vector<std::vector<int>> matrix1 = {{1, 2}, {3, 4}};

    // Create the second matrix
    std::vector<std::vector<int>> matrix2 = {{5, 6}, {7, 8}};

    // Multiply the matrices
    auto result = multiplyMatrices(matrix1, matrix2);

    // Print the result
    if (!result.empty()) {
        printMatrix(result);
    }

    return 0;
}