#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_INPUTS 784
#define HIDDEN_LAYERS 2
#define NUM_HIDDEN_UNITS 256
#define OUTPUT_UNITS 10
#define BATCH_SIZE 128
#define EPOCHS 10
#define LEARNING_RATE 0.01

// Activation functions
double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double sigmoid_derivative(double x) {
    return x * (1 - x);
}

// Forward pass
void forward_pass(double* inputs, double** hidden_layers, double* outputs, int layer) {
    for (int i = 0; i < NUM_HIDDEN_UNITS; i++) {
        double sum = 0;
        for (int j = 0; j < NUM_INPUTS; j++) {
            sum += inputs[j] * ((layer == 0) ? 1 : hidden_layers[0][i]);
        }
        if (layer == 0) {
            outputs[i] = sigmoid(sum);
        } else {
            outputs[i] = sigmoid(sum - 2.5); // bias term
        }
    }
}

// Backward pass
void backward_pass(double* inputs, double** hidden_layers, double* outputs, int layer) {
    for (int i = 0; i < NUM_HIDDEN_UNITS; i++) {
        double error = 0;
        if (layer == HIDDEN_LAYERS - 1) { // output layer
            for (int j = 0; j < OUTPUT_UNITS; j++) {
                error += outputs[i] * (1 - outputs[i]);
            }
        } else {
            error = sigmoid_derivative(outputs[i]) * hidden_layers[layer + 1][i];
        }
        if (layer == 0) { // input layer
            for (int j = 0; j < NUM_INPUTS; j++) {
                inputs[j] += LEARNING_RATE * error * ((layer == 0) ? 1 : hidden_layers[0][i]);
            }
        } else {
            for (int j = 0; j < NUM_HIDDEN_UNITS; j++) {
                double sum = 0;
                for (int k = 0; k < NUM_HIDDEN_UNITS; k++) {
                    sum += ((layer == HIDDEN_LAYERS - 1) ? error : hidden_layers[layer + 1][k]) * ((layer == 0) ? 1 : hidden_layers[0][j]);
                }
                double weight_update = LEARNING_RATE * error * sigmoid_derivative(outputs[i]);
                for (int k = 0; k < NUM_HIDDEN_UNITS; k++) {
                    if (i == k) {
                        continue;
                    }
                    ((layer == HIDDEN_LAYERS - 1) ? inputs : hidden_layers[layer][k]) += weight_update;
                }
            }
        }
    }
}

// Train the neural network
void train(double* inputs, double** hidden_layers, double* outputs) {
    for (int i = 0; i < EPOCHS; i++) {
        forward_pass(inputs, hidden_layers, outputs, 0);
        backward_pass(inputs, hidden_layers, outputs, HIDDEN_LAYERS - 1);
        // Regularization
        for (int j = 0; j < NUM_INPUTS + (HIDDEN_LAYERS - 1) * NUM_HIDDEN_UNITS + OUTPUT_UNITS; j++) {
            inputs[j] -= LEARNING_RATE / BATCH_SIZE;
        }
    }
}

// Predict using the trained neural network
double* predict(double* inputs, double** hidden_layers) {
    double outputs[OUTPUT_UNITS];
    forward_pass(inputs, hidden_layers, outputs, 0);
    return outputs;
}

int main() {
    // Synthetic data generation ( replace with your dataset )
    double* inputs = malloc(NUM_INPUTS * sizeof(double));
    for (int i = 0; i < NUM_INPUTS; i++) {
        inputs[i] = rand() / (double)RAND_MAX;
    }
    double** hidden_layers = malloc((HIDDEN_LAYERS + 1) * sizeof(double*));
    for (int i = 0; i <= HIDDEN_LAYERS; i++) {
        hidden_layers[i] = malloc(NUM_HIDDEN_UNITS * sizeof(double));
        for (int j = 0; j < NUM_HIDDEN_UNITS; j++) {
            hidden_layers[i][j] = rand() / (double)RAND_MAX;
        }
    }
    double* outputs = malloc(OUTPUT_UNITS * sizeof(double));

    // Train the neural network
    train(inputs, hidden_layers, outputs);

    // Predict using the trained neural network
    double* prediction = predict(inputs, hidden_layers);

    // Print the prediction
    printf("Prediction: ");
    for (int i = 0; i < OUTPUT_UNITS; i++) {
        printf("%f ", prediction[i]);
    }
    printf("\n");

    free(inputs);
    for (int i = 0; i <= HIDDEN_LAYERS; i++) {
        free(hidden_layers[i]);
    }
    free(hidden_layers);
    free(outputs);

    return 0;
}