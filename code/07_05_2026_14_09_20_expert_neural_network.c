#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define the sigmoid function
double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

// Define the derivative of the sigmoid function
double sigmoid_derivative(double x) {
    return x * (1 - x);
}

// Define a struct for the neural network layer
typedef struct {
    double* weights;
    double* bias;
    int num_neurons;
} Layer;

// Define a struct for the neural network
typedef struct {
    int num_layers;
    Layer** layers;
} NeuralNetwork;

// Initialize a new neural network
NeuralNetwork* initialize_neural_network(int num_layers, int* num_neurons_per_layer) {
    NeuralNetwork* nn = (NeuralNetwork*)malloc(sizeof(NeuralNetwork));
    nn->num_layers = num_layers;
    nn->layers = (Layer**)malloc(num_layers * sizeof(Layer*));

    for (int i = 0; i < num_layers; i++) {
        Layer* layer = (Layer*)malloc(sizeof(Layer));
        layer->num_neurons = num_neurons_per_layer[i];
        layer->weights = (double*)malloc(layer->num_neurons * sizeof(double));
        layer->bias = (double*)malloc(layer->num_neurons * sizeof(double));

        nn->layers[i] = layer;
    }

    return nn;
}

// Free the memory allocated by the neural network
void free_neural_network(NeuralNetwork* nn) {
    for (int i = 0; i < nn->num_layers; i++) {
        Layer* layer = nn->layers[i];
        free(layer->weights);
        free(layer->bias);
        free(layer);
    }
    free(nn->layers);
    free(nn);
}

// Feedforward pass
double** feedforward(NeuralNetwork* nn, double** input) {
    for (int i = 0; i < nn->num_layers - 1; i++) {
        Layer* layer = nn->layers[i];
        double** output = (double**)malloc(layer->num_neurons * sizeof(double));

        for (int j = 0; j < layer->num_neurons; j++) {
            double sum = 0;
            for (int k = 0; k < input[0]->size; k++) {
                sum += input[k][j] * layer->weights[j];
            }
            sum += layer->bias[j];
            output[j] = sigmoid(sum);
        }

        free(input);
        input = output;

        // Propagate the error
        for (int j = 0; j < layer->num_neurons; j++) {
            double delta = 0;
            for (int k = 0; k < nn->layers[nn->num_layers - 1]->num_neurons; k++) {
                delta += (input[k][j] * sigmoid_derivative(input[k][j])) * (layer->weights[j]);
            }
            layer->bias[j] -= delta * sigmoid_derivative(layer->bias[j]);
        }

        // Update the weights
        for (int j = 0; j < layer->num_neurons; j++) {
            double sum = 0;
            for (int k = 0; k < input[0]->size; k++) {
                sum += input[k][j] * sigmoid_derivative(input[k][j]) * layer->weights[j];
            }
            for (int k = 0; k < input[0]->size; k++) {
                layer->weights[j] -= 0.1 * sigmoid_derivative(layer->bias[j]) * input[k][j];
            }
        }
    }

    return input;
}

int main() {
    int num_layers = 3;
    int* num_neurons_per_layer = (int*)malloc((num_layers + 1) * sizeof(int));
    num_neurons_per_layer[0] = 784;
    num_neurons_per_layer[1] = 256;
    num_neurons_per_layer[2] = 10;

    NeuralNetwork* nn = initialize_neural_network(num_layers, num_neurons_per_layer);

    // Synthesize some input data
    int num_inputs = 784;
    double** input = (double**)malloc(num_inputs * sizeof(double*));
    for (int i = 0; i < num_inputs; i++) {
        input[i] = (double*)malloc(10 * sizeof(double));
        for (int j = 0; j < 10; j++) {
            input[i][j] = (double)rand() / RAND_MAX;
        }
    }

    // Perform a feedforward pass
    double** output = feedforward(nn, input);

    // Print the output
    for (int i = 0; i < num_neurons_per_layer[num_layers - 1]; i++) {
        printf("%f ", output[i][0]);
    }
    printf("\n");

    free_neural_network(nn);
    for (int i = 0; i < num_inputs; i++) {
        free(input[i]);
    }
    free(input);

    return 0;
}