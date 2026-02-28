#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define the neural network structure
typedef struct {
    int inputs;
    int hidden;
    int outputs;
} NeuralNetwork;

// Function to initialize the neural network with random weights and biases
void initNeuralNetwork(NeuralNetwork* nn) {
    // Initialize the weights for the input layer
    for (int i = 0; i < nn->inputs * (nn->hidden + nn->outputs); i++) {
        nn->weights[i] = (double)rand() / RAND_MAX;
    }

    // Initialize the biases for the hidden and output layers
    for (int i = 0; i < (nn->hidden + nn->outputs); i++) {
        nn->biases[i] = (double)rand() / RAND_MAX;
    }
}

// Function to forward propagate through the neural network
void forwardPropagate(NeuralNetwork* nn, double* inputs) {
    // Calculate the output of the input layer
    for (int i = 0; i < nn->inputs; i++) {
        nn->hidden[i] = inputs[i];
    }

    // Calculate the output of the hidden layer
    for (int i = 0; i < nn->hidden; i++) {
        double sum = 0.0;
        for (int j = 0; j < nn->inputs; j++) {
            sum += nn->weights[j * (nn->hidden + nn->outputs) + i] * inputs[j];
        }
        nn->hidden[i] = sigmoid(sum);
    }

    // Calculate the output of the output layer
    for (int i = 0; i < nn->outputs; i++) {
        double sum = 0.0;
        for (int j = 0; j < nn->hidden; j++) {
            sum += nn->weights[nn->inputs * (nn->hidden + nn->outputs) + i * nn->hidden + j] * nn->hidden[j];
        }
        nn->output[i] = sigmoid(sum);
    }
}

// Function to calculate the derivative of the sigmoid function
double sigmoidDerivative(double x) {
    return x * (1.0 - x);
}

// Function to train the neural network using backpropagation
void trainNeuralNetwork(NeuralNetwork* nn, double* inputs, double* outputs, int iterations) {
    // Calculate the output of the input layer
    for (int i = 0; i < nn->inputs; i++) {
        nn->hidden[i] = inputs[i];
    }

    // Calculate the error at the output layer
    for (int i = 0; i < nn->outputs; i++) {
        double difference = outputs[i] - nn->output[i];
        nn->error[i] = difference * difference;
    }

    // Backpropagate the error through the network
    for (int i = 0; i < nn->hidden; i++) {
        double sum = 0.0;
        for (int j = 0; j < nn->outputs; j++) {
            sum += nn->weights[nn->inputs * (nn->hidden + nn->outputs) + i * nn->outputs + j] * nn->error[j];
        }
        nn->delta[i] = sigmoidDerivative(nn->hidden[i]) * sum;
    }

    // Update the weights and biases
    for (int i = 0; i < nn->inputs * (nn->hidden + nn->outputs); i++) {
        double weightSum = 0.0;
        for (int j = 0; j < iterations; j++) {
            weightSum += nn->delta[i / (nn->hidden + nn->outputs)] * inputs[i % nn->inputs];
        }
        nn->weights[i] -= learningRate * weightSum;
    }

    for (int i = 0; i < (nn->hidden + nn->outputs); i++) {
        double biasSum = 0.0;
        for (int j = 0; j < iterations; j++) {
            biasSum += nn->delta[i] * nn->hidden[i];
        }
        nn->biases[i] -= learningRate * biasSum;
    }
}

// Function to test the neural network
void testNeuralNetwork(NeuralNetwork* nn, double* inputs) {
    // Forward propagate through the network
    forwardPropagate(nn, inputs);

    // Print the output of the network
    for (int i = 0; i < nn->outputs; i++) {
        printf("Output %d: %f\n", i, nn->output[i]);
    }
}

// Main function to run the neural network image classifier
int main() {
    // Initialize the neural network with random weights and biases
    NeuralNetwork nn;
    nn.inputs = 784;
    nn.hidden = 256;
    nn.outputs = 10;
    initNeuralNetwork(&nn);

    // Define the learning rate for training
    double learningRate = 0.1;

    // Train the neural network using backpropagation
    double* inputs = (double*)malloc(784 * sizeof(double));
    double* outputs = (double*)malloc(10 * sizeof(double));
    for (int i = 0; i < 784; i++) {
        inputs[i] = (double)rand() / RAND_MAX;
    }
    for (int i = 0; i < 10; i++) {
        outputs[i] = (double)rand() / RAND_MAX;
    }
    trainNeuralNetwork(&nn, inputs, outputs, 100);

    // Test the neural network
    free(inputs);
    free(outputs);
    double* testInputs = (double*)malloc(784 * sizeof(double));
    for (int i = 0; i < 784; i++) {
        testInputs[i] = (double)rand() / RAND_MAX;
    }
    testNeuralNetwork(&nn, testInputs);

    // Free the memory
    free(testInputs);
    return 0;
}