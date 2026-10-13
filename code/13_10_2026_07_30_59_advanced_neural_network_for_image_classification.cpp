#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "neural_network.h"

int main() {
    // Set random seed
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    // Create neural network
    NeuralNetwork nn(784, 256, 10);

    // Train the neural network
    for (int i = 0; i < 10000; ++i) {
        int batch_size = 32;
        std::vector<std::pair<std::vector<double>, double>> batch;

        for (int j = 0; j < batch_size; ++j) {
            // Generate random input image
            std::vector<double> input(784);
            for (int k = 0; k < 28*28; ++k) {
                input[k] = dis(gen);
            }

            // Calculate output
            double target = dis(gen) > 0.5 ? 1 : 0;

            batch.push_back({input, target});
        }

        nn.train(batch);
    }

    // Test the neural network
    std::cout << "Testing..." << std::endl;
    for (int i = 0; i < 10; ++i) {
        // Generate random input image
        std::vector<double> input(784);
        for (int j = 0; j < 28*28; ++j) {
            input[j] = dis(gen);
        }

        double output = nn.predict(input);

        if (output > 0.5)
            std::cout << "Image " << i << " is a digit.\n";
        else
            std::cout << "Image " << i << " is not a digit.\n";
    }

    return 0;
}
```

```c++
#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <vector>
#include <algorithm>

class NeuralNetwork {
public:
    NeuralNetwork(int input_dim, int hidden_dim, int output_dim);
    void train(const std::vector<std::pair<std::vector<double>, double>>& batch);
    double predict(const std::vector<double>& input);

private:
    struct Layer {
        std::vector<double> weights;
        std::vector<double> biases;
    };

    std::vector<Layer> layers;

    // Forward pass
    std::vector<double> forward_pass(const std::vector<double>& input) const;

    // Backward pass
    void backward_pass(const std::vector<std::pair<std::vector<double>, double>>& batch);

    // Activation function
    double sigmoid(double x) { return 1 / (1 + exp(-x)); }
};

#endif  // NEURAL_NETWORK_H
```

```c++
#include "neural_network.h"
#include <cmath>
#include <algorithm>

NeuralNetwork::NeuralNetwork(int input_dim, int hidden_dim, int output_dim)
    : layers({{input_dim, hidden_dim}, {hidden_dim, output_dim}}) {}

void NeuralNetwork::train(const std::vector<std::pair<std::vector<double>, double>>& batch) {
    for (const auto& [input, target] : batch) {
        // Forward pass
        std::vector<double> hidden = forward_pass(input);

        // Calculate error
        double output = sigmoid(dot(hidden, layers[1].biases));
        double error = target - output;

        // Backward pass
        backward_pass({{hidden, error}});
    }
}

double NeuralNetwork::predict(const std::vector<double>& input) {
    return sigmoid(dot(forward_pass(input), layers[1].biases));
}

std::vector<double> NeuralNetwork::forward_pass(const std::vector<double>& input) const {
    std::vector<double> hidden;
    for (int i = 0; i < layers.size() - 1; ++i) {
        double sum = 0;
        for (int j = 0; j < input.size(); ++j) {
            sum += input[j] * layers[i].weights[j];
        }
        hidden.push_back(sigmoid(sum + layers[i].biases));
    }
    return hidden;
}

void NeuralNetwork::backward_pass(const std::vector<std::pair<std::vector<double>, double>>& batch) {
    for (const auto& [input, target] : batch) {
        // Forward pass
        std::vector<double> hidden = forward_pass(input);

        // Calculate error
        double output = sigmoid(dot(hidden, layers[1].biases));
        double error = target - output;

        // Backward pass
        for (int i = 0; i < layers.size() - 1; ++i) {
            double delta = error * layers[i + 1].weights.size() == 0 ? error : layers[i + 1].weights[0] * hidden.back() * (1 - hidden.back()) * error;
            for (int j = 0; j < input.size(); ++j) {
                layers[i].biases[j] -= delta * input[j];
                layers[i].weights[j] -= 0.01 * delta * input[j];
            }
        }
    }
}

double NeuralNetwork::dot(const std::vector<double>& a, const std::vector<double>& b) {
    double sum = 0;
    for (int i = 0; i < a.size(); ++i) {
        sum += a[i] * b[i];
    }
    return sum;
}