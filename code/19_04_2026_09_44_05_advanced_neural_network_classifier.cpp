#include <iostream>
#include <vector>
#include <cmath>
#include <random>

// Activation functions
double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double ReLU(double x) {
    return x > 0 ? x : 0;
}

// Neural Network class
class NeuralNetwork {
public:
    // Constructor
    NeuralNetwork(int inputSize, int hiddenSize, int outputSize)
        : inputs(inputSize), hidden(hiddenSize), outputs(outputSize) {}

    // Train the network using backpropagation
    void train(std::vector<std::vector<double>>& inputs, std::vector<std::vector<double>>& targets) {
        for (int i = 0; i < inputs.size(); i++) {
            double* inputArray = &inputs[i][0];
            double* targetArray = &targets[i][0];

            // Forward pass
            hidden[0] = sigmoid(dot(inputArray, inputs.size()) * inputArray);
            outputs[0] = sigmoid(dot(hidden, hidden.size()) * hidden);

            // Backward pass
            double error = targetArray[0] - outputs[0];
            double outputDelta = error * outputs[0] * (1 - outputs[0]);
            for (int j = 0; j < hidden.size(); j++) {
                hidden[j] -= outputDelta * inputs[i][j] * 0.5;
            }
        }
    }

    // Make a prediction
    double predict(double* input) {
        double* hiddenArray = new double[hidden.size()];
        for (int i = 0; i < inputs.size(); i++) {
            hiddenArray[i] = sigmoid(dot(input, inputs.size()) * input);
        }
        double output = sigmoid(dot(hiddenArray, hidden.size()) * hiddenArray);
        delete[] hiddenArray;
        return output;
    }

private:
    // Helper function to calculate dot product
    double dot(double* arr1, int size) {
        double sum = 0;
        for (int i = 0; i < size; i++) {
            sum += arr1[i];
        }
        return sum;
    }

    std::vector<double> inputs;
    std::vector<double> hidden;
    std::vector<double> outputs;
};

// Main function
int main() {
    // Create a synthetic dataset
    int numInputs = 784; // MNIST input size
    int numHidden = 256; // Neural network hidden layer size
    int numOutputs = 10; // Number of output classes (digits)

    std::vector<std::vector<double>> inputs;
    std::vector<std::vector<double>> targets;

    for (int i = 0; i < 10000; i++) {
        std::vector<double> input;
        for (int j = 0; j < numInputs; j++) {
            if (rand() % 2) {
                input.push_back(1.0);
            } else {
                input.push_back(-1.0);
            }
        }
        inputs.push_back(input);

        std::vector<double> target;
        for (int j = 0; j < numOutputs; j++) {
            if (j == rand() % 10) {
                target.push_back(1.0);
            } else {
                target.push_back(-1.0);
            }
        }
        targets.push_back(target);
    }

    // Create a neural network
    NeuralNetwork nn(numInputs, numHidden, numOutputs);

    // Train the network
    for (int i = 0; i < 10000; i++) {
        nn.train(inputs, targets);
    }

    // Make a prediction
    std::vector<double> input;
    for (int j = 0; j < numInputs; j++) {
        if (rand() % 2) {
            input.push_back(1.0);
        } else {
            input.push_back(-1.0);
        }
    }
    double prediction = nn.predict(&input[0]);

    std::cout << "Prediction: " << prediction << std::endl;

    return 0;
}