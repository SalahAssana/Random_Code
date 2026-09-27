Here is the C++ code for the Neural Network Image Classifier:

```cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Activation functions
double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double ReLU(double x) {
    return max(0, x);
}

// Convolutional layer
class ConvLayer {
public:
    int kernelSize;
    int numFilters;
    double learningRate;

    vector<vector<double>> weights;
    vector<vector<double>> biases;

    void forward(vector<vector<double>>& input) {
        int outputHeight = (input.size() - kernelSize + 1);
        int outputWidth = (input[0].size() - kernelSize + 1);

        for (int i = 0; i < numFilters; ++i) {
            vector<vector<double>> filterOutput(outputHeight, vector<double>(outputWidth));
            for (int j = 0; j < outputHeight; ++j) {
                for (int k = 0; k < outputWidth; ++k) {
                    double sum = 0;
                    for (int m = 0; m < kernelSize; ++m) {
                        for (int n = 0; n < kernelSize; ++n) {
                            sum += input[j + m][k + n] * weights[m][n];
                        }
                    }
                    filterOutput[j][k] = sigmoid(sum + biases[i]);
                }
            }
        }
    }

    void backward(vector<vector<double>>& gradients) {
        for (int i = 0; i < numFilters; ++i) {
            vector<vector<double>> gradientOutput(gradients.size(), vector<double>(gradients[0].size()));
            for (int j = 0; j < gradients.size(); ++j) {
                for (int k = 0; k < gradients[0].size(); ++k) {
                    double sum = 0;
                    for (int m = 0; m < kernelSize; ++m) {
                        for (int n = 0; n < kernelSize; ++n) {
                            sum += gradients[j + m][k + n] * weights[m][n];
                        }
                    }
                    gradientOutput[j][k] = sigmoid(sum);
                }
            }
        }
    }

    void update(double learningRate) {
        for (int i = 0; i < numFilters; ++i) {
            for (int j = 0; j < kernelSize; ++j) {
                for (int k = 0; k < kernelSize; ++k) {
                    weights[j][k] -= learningRate * gradients[i][j][k];
                }
            }
        }
    }
};

// Neural network
class NeuralNetwork {
public:
    int numLayers;
    vector<ConvLayer> layers;

    void forward(vector<vector<double>>& input) {
        for (int i = 0; i < numLayers; ++i) {
            layers[i].forward(input);
            input = layers[i].getOutput();
        }
    }

    void backward(vector<vector<double>>& gradients) {
        for (int i = numLayers - 1; i >= 0; --i) {
            layers[i].backward(gradients);
            gradients = layers[i].getGradients();
        }
    }

    void update(double learningRate) {
        for (int i = 0; i < numLayers; ++i) {
            layers[i].update(learningRate);
        }
    }
};

// Main function
int main() {
    // Synthetic data
    vector<vector<double>> input(1, vector<double>(28 * 28));
    for (int i = 0; i < input.size(); ++i) {
        for (int j = 0; j < input[0].size(); ++j) {
            input[i][j] = sin(i + j);
        }
    }

    // Neural network
    NeuralNetwork nn;
    nn.numLayers = 2;

    ConvLayer layer1;
    layer1.kernelSize = 3;
    layer1.numFilters = 10;
    layer1.learningRate = 0.01;
    vector<vector<double>> weights1(layer1.kernelSize, vector<double>(layer1.kernelSize));
    vector<vector<double>> biases1(10, vector<double>());
    for (int i = 0; i < weights1.size(); ++i) {
        for (int j = 0; j < weights1[0].size(); ++j) {
            weights1[i][j] = rand() / (RAND_MAX + 1.0);
        }
    }
    for (int i = 0; i < biases1.size(); ++i) {
        biases1[i][0] = rand() / (RAND_MAX + 1.0);
    }
    layer1.weights = weights1;
    layer1.biases = biases1;

    ConvLayer layer2;
    layer2.kernelSize = 3;
    layer2.numFilters = 10;
    layer2.learningRate = 0.01;
    vector<vector<double>> weights2(layer2.kernelSize, vector<double>(layer2.kernelSize));
    vector<vector<double>> biases2(10, vector<double>());
    for (int i = 0; i < weights2.size(); ++i) {
        for (int j = 0; j < weights2[0].size(); ++j) {
            weights2[i][j] = rand() / (RAND_MAX + 1.0);
        }
    }
    for (int i = 0; i < biases2.size(); ++i) {
        biases2[i][0] = rand() / (RAND_MAX + 1.0);
    }
    layer2.weights = weights2;
    layer2.biases = biases2;

    nn.layers.push_back(layer1);
    nn.layers.push_back(layer2);

    // Train the neural network
    for (int i = 0; i < 10000; ++i) {
        vector<vector<double>> gradients(input.size(), vector<double>(input[0].size()));
        nn.forward(input);
        double output = sigmoid(nn.getOutput()[0][0]);
        double loss = pow(output - 1, 2);

        gradients = input;
        nn.backward(gradients);
        nn.update(0.01);

        cout << "Loss: " << loss << endl;
    }

    return 0;
}
```