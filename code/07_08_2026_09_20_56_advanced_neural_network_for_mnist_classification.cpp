#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// Activation functions
double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double ReLU(double x) {
    if (x > 0)
        return x;
    else
        return 0;
}

class NeuralNetwork {
public:
    NeuralNetwork(int inputSize, int hiddenSize, int outputSize);

    void train(std::vector<std::vector<double>>& inputs, std::vector<std::vector<double>>& outputs);
    double predict(std::vector<double>& input);

private:
    // Layers
    struct Layer {
        double* weights;
        double* biases;
        int size;
    };

    // Initialize layers
    void initLayers(int inputSize, int hiddenSize, int outputSize);

    // Forward pass
    std::vector<double> forwardPass(std::vector<double>& input);

    // Backward pass
    void backwardPass(std::vector<double>& input, double target);

    // Update weights and biases
    void update(double learningRate, double momentum);

    Layer hiddenLayer;
    Layer outputLayer;

};

NeuralNetwork::NeuralNetwork(int inputSize, int hiddenSize, int outputSize) {
    initLayers(inputSize, hiddenSize, outputSize);
}

void NeuralNetwork::initLayers(int inputSize, int hiddenSize, int outputSize) {
    // Initialize weights and biases for the layers
    hiddenLayer.size = hiddenSize;
    hiddenLayer.weights = new double[hiddenSize * (inputSize + 1)];
    hiddenLayer.biases = new double[hiddenSize];

    outputLayer.size = outputSize;
    outputLayer.weights = new double[outputSize * (hiddenSize + 1)];
    outputLayer.biases = new double[outputSize];
}

std::vector<double> NeuralNetwork::forwardPass(std::vector<double>& input) {
    // Calculate the output of the hidden layer
    std::vector<double> hiddenOutputs(hiddenLayer.size);
    for (int i = 0; i < hiddenLayer.size; ++i) {
        double sum = 0;
        for (int j = 0; j < input.size() + 1; ++j) {
            sum += input[j] * (hiddenLayer.weights[i * (input.size() + 1) + j]);
        }
        hiddenOutputs[i] = sigmoid(sum + hiddenLayer.biases[i]);
    }

    // Calculate the output of the output layer
    std::vector<double> outputOutputs(outputLayer.size);
    for (int i = 0; i < outputLayer.size; ++i) {
        double sum = 0;
        for (int j = 0; j < hiddenLayer.size + 1; ++j) {
            sum += hiddenOutputs[j] * (outputLayer.weights[i * (hiddenLayer.size + 1) + j]);
        }
        outputOutputs[i] = sigmoid(sum + outputLayer.biases[i]);
    }

    return outputOutputs;
}

void NeuralNetwork::backwardPass(std::vector<double>& input, double target) {
    // Calculate the error of the output layer
    std::vector<double> outputErrors(outputLayer.size);
    for (int i = 0; i < outputLayer.size; ++i) {
        double err = target[i] - outputOutputs[i];
        outputErrors[i] = err * sigmoid(-1 * (target[i] - outputOutputs[i]));
    }

    // Calculate the error of the hidden layer
    std::vector<double> hiddenErrors(hiddenLayer.size);
    for (int i = 0; i < hiddenLayer.size; ++i) {
        double sum = 0;
        for (int j = 0; j < outputLayer.size; ++j) {
            sum += outputErrors[j] * outputLayer.weights[i * (outputLayer.size + 1) + j];
        }
        hiddenErrors[i] = sum * sigmoid(-1 * (hiddenOutputs[i]));
    }

    // Update the weights and biases
    update(0.1, 0.5);
}

void NeuralNetwork::update(double learningRate, double momentum) {
    // Update the weights of the output layer
    for (int i = 0; i < outputLayer.size; ++i) {
        for (int j = 0; j < hiddenLayer.size + 1; ++j) {
            outputLayer.weights[i * (hiddenLayer.size + 1) + j] -= learningRate * outputErrors[i] * hiddenOutputs[j];
            outputLayer.weights[i * (hiddenLayer.size + 1) + j] *= momentum;
        }
    }

    // Update the biases of the output layer
    for (int i = 0; i < outputLayer.size; ++i) {
        outputLayer.biases[i] -= learningRate * outputErrors[i];
    }

    // Update the weights of the hidden layer
    for (int i = 0; i < hiddenLayer.size; ++i) {
        for (int j = 0; j < input.size() + 1; ++j) {
            hiddenLayer.weights[i * (input.size() + 1) + j] -= learningRate * hiddenErrors[i] * input[j];
            hiddenLayer.weights[i * (input.size() + 1) + j] *= momentum;
        }
    }

    // Update the biases of the hidden layer
    for (int i = 0; i < hiddenLayer.size; ++i) {
        hiddenLayer.biases[i] -= learningRate * hiddenErrors[i];
    }
}

double NeuralNetwork::predict(std::vector<double>& input) {
    return outputOutputs[0];
}

int main() {
    // Initialize the neural network
    NeuralNetwork nn(784, 256, 10);

    // Define the MNIST dataset
    std::vector<std::vector<double>> inputs = {{1, 2, 3, ..., 784}};
    std::vector<std::vector<double>> outputs = {{0, 0, 0, ..., 1}};

    // Train the neural network
    nn.train(inputs, outputs);

    return 0;
}