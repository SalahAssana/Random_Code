#include <iostream>
#include <vector>
#include <cmath>

// Activation function: Sigmoid
double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

// Activation function: ReLU
double relu(double x) {
    return x > 0 ? x : 0;
}

// Neural Network class
class NeuralNetwork {
public:
    NeuralNetwork(int numLayers, int* layerSizes) {
        layers_.resize(numLayers);
        for (int i = 0; i < numLayers; ++i) {
            layers_[i].resize(layerSizes[i]);
        }
    }

    // Feedforward pass
    std::vector<double> feedForward(std::vector<double> inputs) {
        std::vector<double> outputs;
        outputs.push_back(sigmoid(dot(inputs, layers_[0])));

        for (int i = 1; i < layers_.size(); ++i) {
            double sum = 0;
            for (int j = 0; j < layers_[i-1].size(); ++j) {
                sum += outputs[outputs.size()-1] * layers_[i-1][j];
            }
            outputs.push_back(sigmoid(sum));
        }

        return outputs;
    }

    // Backpropagation
    void backpropagate(int targetIndex, std::vector<double> targets) {
        // Calculate error at each layer
        for (int i = layers_.size() - 1; i > 0; --i) {
            double sum = 0;
            for (int j = 0; j < layers_[i].size(); ++j) {
                sum += (targets[targetIndex] - outputs_[outputs_.size()-1][0]) * sigmoidDerivative(outputs_[outputs_.size()-1][0]);
            }
            errors_.push_back(-sum);
        }

        // Update weights
        for (int i = 0; i < layers_.size(); ++i) {
            for (int j = 0; j < layers_[i].size(); ++j) {
                double sum = 0;
                for (int k = 0; k < layers_[i-1].size(); ++k) {
                    sum += outputs_[outputs_.size()-i][k] * errors_[errors_.size()-i];
                }
                weights_[i][j] += 0.1 * sum;
            }
        }
    }

private:
    std::vector<std::vector<double>> layers_;
    std::vector<std::vector<double>> weights_;
    std::vector<std::vector<double>> outputs_;
    std::vector<std::vector<double>> errors_;

    // Dot product
    double dot(std::vector<double> a, std::vector<double> b) {
        double sum = 0;
        for (int i = 0; i < a.size(); ++i) {
            sum += a[i] * b[i];
        }
        return sum;
    }

    // Sigmoid derivative
    double sigmoidDerivative(double x) {
        return x * (1 - x);
    }
};

int main() {
    int numLayers = 3;
    int* layerSizes = new int[numLayers];
    layerSizes[0] = 2; // Input layer: 2 neurons
    layerSizes[1] = 4; // Hidden layer: 4 neurons
    layer Sizes[2] = 1; // Output layer: 1 neuron

    NeuralNetwork nn(numLayers, layerSizes);

    // Synthetical data
    std::vector<double> inputs = {0.5, 0.5};
    int targetIndex = 0;
    double targets[] = {0.8}; // Target for output neuron

    // Train the network
    for (int i = 0; i < 10000; ++i) {
        nn.feedForward(inputs);
        nn.backpropagate(targetIndex, std::vector<double>(targets, targets+1));
    }

    return 0;
}