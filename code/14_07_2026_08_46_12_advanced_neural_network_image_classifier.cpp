#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>

// Activation functions
double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double relu(double x) {
    return x > 0 ? x : 0;
}

class Neuron {
public:
    double weights[784];
    double bias;
    double output;

    Neuron() {
        std::fill_n(weights, 784, rand() / (RAND_MAX + 1.0));
        bias = rand() / (RAND_MAX + 1.0);
    }

    void calculateOutput(double* input) {
        output = 0;
        for (int i = 0; i < 784; ++i) {
            output += weights[i] * input[i];
        }
        output += bias;
        output = sigmoid(output);
    }
};

class Layer {
public:
    Neuron** neurons;

    Layer(int numNeurons, int inputSize) {
        neurons = new Neuron*[numNeurons];
        for (int i = 0; i < numNeurons; ++i) {
            neurons[i] = new Neuron();
        }
    }

    ~Layer() {
        for (int i = 0; i < 10; ++i) {
            delete neurons[i];
        }
        delete[] neurons;
    }

    void calculateOutput(double* input) {
        for (int i = 0; i < 10; ++i) {
            neurons[i]->calculateOutput(input);
        }
    }
};

class ConvolutionalNeuralNetwork {
public:
    Layer** layers;

    ConvolutionalNeuralNetwork(int numLayers, int inputSize, int* layerSizes) {
        layers = new Layer*[numLayers];
        for (int i = 0; i < numLayers; ++i) {
            layers[i] = new Layer(layerSizes[i], inputSize);
            inputSize = layerSizes[i];
        }
    }

    ~ConvolutionalNeuralNetwork() {
        for (int i = 0; i < 3; ++i) {
            delete layers[i];
        }
        delete[] layers;
    }

    void calculateOutput(double* input) {
        for (int i = 0; i < 3; ++i) {
            layers[i]->calculateOutput(input);
            input = layers[i]->neurons[0]->output * new double[layerSizes[i]];
            // Pooling logic
        }
    }
};

int main() {
    int numLayers = 3;
    int layerSizes[] = {784, 10, 10};
    ConvolutionalNeuralNetwork cnn(numLayers, 784, layerSizes);
    double input[784] = {};
    cnn.calculateOutput(input);
    return 0;
}