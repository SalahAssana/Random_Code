#include <iostream>
#include <vector>

// Function to multiply two matrices
std::vector<std::vector<int>> multiplyMatrices(const std::vector<std::vector<int>>& matrix1,
                                                 const std::vector<std::vector<int>>& matrix2) {
    if (matrix1[0].size() != matrix2.size()) {
        std::cerr << "Matrix dimensions are incompatible for multiplication.\n";
        return {};
    }

    int rowsMat1 = matrix1.size();
    int colsMat1 = matrix1[0].size();
    int colsMat2 = matrix2[0].size();

    // Create the result matrix
    std::vector<std::vector<int>> resultMatrix(rowsMat1, std::vector<int>(colsMat2, 0));

    for (int i = 0; i < rowsMat1; ++i) {
        for (int j = 0; j < colsMat2; ++j) {
            int sum = 0;
            for (int k = 0; k < colsMat1; ++k) {
                sum += matrix1[i][k] * matrix2[k][j];
            }
            resultMatrix[i][j] = sum;
        }
    }

    return resultMatrix;
}

int main() {
    // Synthetic data
    std::vector<std::vector<int>> matrixA {{1, 2, 3}, {4, 5, 6}};
    std::vector<std::vector<int>> matrixB {{7, 8}, {9, 10}, {11, 12}};

    // Multiply the matrices
    auto result = multiplyMatrices(matrixA, matrixB);

    // Print the result
    for (const auto& row : result) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    return 0;
}