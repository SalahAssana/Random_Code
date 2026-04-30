#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>

// Activation functions
double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double softmax(double x, double temp) {
    return exp(x / temp) / sum(exp((other_elements - x) / temp));
}

// Layer class for neural network
class Layer {
public:
    int neurons;
    std::vector<std::vector<double>> weights;
    std::vector<double> biases;

    Layer(int n, int m) : neurons(n), biases(m, 0.0) {
        weights.resize(neurons, std::vector<double>(m, 0.0));
    }

    void forwardProp(std::vector<double>& inputs) {
        for (int i = 0; i < neurons; i++) {
            double sum = 0.0;
            for (int j = 0; j < inputs.size(); j++) {
                sum += weights[i][j] * inputs[j];
            }
            biases[i] = sigmoid(sum);
        }
    }

    std::vector<double> getOutput() {
        return biases;
    }
};

// Neural network class
class NeuralNetwork {
public:
    int numLayers;
    Layer* layers;

    NeuralNetwork(int n) : numLayers(n + 1), layers(new Layer[numLayers]) {
        for (int i = 0; i < numLayers - 1; i++) {
            layers[i].neurons = 64; // Set number of neurons in each layer
            if (i == 0) {
                layers[i].weights.resize(layers[i].neurons, std::vector<double>(784, 0.0)); // Input layer with 28x28 images
            } else {
                layers[i].weights.resize(layers[i].neurons, std::vector<double>(layers[i - 1].neurons, 0.0));
            }
        }
        layers[numLayers - 1].neurons = 10; // Output layer with 10 classes (digits 0-9)
    }

    void train(std::vector<std::vector<double>>& inputs, std::vector<int>& targets) {
        for (int i = 0; i < inputs.size(); i++) {
            Layer* currentLayer = &layers[0];
            std::vector<double> output(inputs[i]);
            for (int j = 1; j < numLayers; j++) {
                currentLayer->forwardProp(output);
                output = currentLayer->getOutput();
                currentLayer++;
            }
            int targetIndex = targets[i];
            Layer* lastLayer = &layers[numLayers - 1];
            double error = 0.5 * (output[targetIndex] - 1.0) * (output[targetIndex] - 1.0);
            for (int k = 0; k < output.size(); k++) {
                if (k == targetIndex) {
                    lastLayer->biases[k] -= 0.05 * error;
                } else {
                    lastLayer->biases[k] += 0.05 * error;
                }
            }
        }
    }

    void test(std::vector<std::vector<double>>& inputs, std::vector<int>& targets) {
        int correct = 0;
        for (int i = 0; i < inputs.size(); i++) {
            Layer* currentLayer = &layers[0];
            std::vector<double> output(inputs[i]);
            for (int j = 1; j < numLayers; j++) {
                currentLayer->forwardProp(output);
                output = currentLayer->getOutput();
                currentLayer++;
            }
            int targetIndex = targets[i];
            double maxIndex = -1;
            double maxValue = -1.0;
            for (int k = 0; k < output.size(); k++) {
                if (output[k] > maxValue) {
                    maxValue = output[k];
                    maxIndex = k;
                }
            }
            if (maxIndex == targetIndex) {
                correct++;
            }
        }
        std::cout << "Accuracy: " << double(correct) / inputs.size() * 100.0 << "%" << std::endl;
    }

    ~NeuralNetwork() {
        delete[] layers;
    }
};

int main() {
    // Training data
    std::vector<std::vector<double>> trainInputs(60000, std::vector<double>(784));
    std::vector<int> trainTargets(60000);

    // Testing data
    std::vector<std::vector<double>> testInputs(10000, std::vector<double>(784));
    std::vector<int> testTargets(10000);

    // Create and train the neural network
    NeuralNetwork nn(4);
    for (int i = 0; i < 60000; i++) {
        nn.train(trainInputs[i], trainTargets[i]);
    }

    // Test the neural network
    for (int i = 0; i < 10000; i++) {
        nn.test(testInputs[i], testTargets[i]);
    }

    return 0;
}