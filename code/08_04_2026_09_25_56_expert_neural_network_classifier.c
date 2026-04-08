#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_INPUTS 784
#define HIDDEN_LAYERS 2
#define NUM_HIDDEN_NEURONS 256
#define OUTPUT_LAYERS 1
#define NUM_OUTPUT_NEURONS 10

typedef struct {
    double *weights;
    double *biases;
} layer;

void initialize_layers(layer *hidden_layer, int size) {
    hidden_layer->weights = (double *)malloc(size * sizeof(double));
    hidden_layer->biases = (double *)malloc(size * sizeof(double));

    for (int i = 0; i < size; i++) {
        hidden_layer->weights[i] = (rand() % 100) / 100.0 - 0.5;
        hidden_layer->biases[i] = (rand() % 100) / 100.0 - 0.5;
    }
}

void forward_propagation(layer *hidden_layers, double *input, double *output) {
    for (int i = 0; i < HIDDEN_LAYERS; i++) {
        double sum = 0.0;
        for (int j = 0; j < NUM_INPUTS; j++) {
            sum += input[j] * hidden_layers[i].weights[j];
        }
        sum += hidden_layers[i].biases[0];

        output[0] = sigmoid(sum);
    }

    double out_sum = 0.0;
    for (int i = 0; i < NUM_HIDDEN_NEURONS; i++) {
        out_sum += hidden_layers[HIDDEN_LAYERS - 1].weights[i] * output[0];
    }
    out_sum += hidden_layers[HIDDEN_LAYERS - 1].biases[0];

    output[1] = sigmoid(out_sum);
}

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

void backpropagation(layer *hidden_layers, double *input, double *output, double *target) {
    double *error = (double *)malloc(OUTPUT_LAYERS * sizeof(double));

    for (int i = 0; i < OUTPUT_LAYERS; i++) {
        error[i] = target[i] - output[i];
    }

    for (int i = HIDDEN_LAYERS - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = 0; j < NUM_HIDDEN_NEURONS; j++) {
            sum += hidden_layers[i].weights[j] * error[0];
        }
        sum *= output[i];

        error[i] = sigmoid(-sum);

        for (int j = 0; j < NUM_HIDDEN_NEURONS; j++) {
            hidden_layers[i].weights[j] -= 0.1 * error[i] * output[i];
        }

        hidden_layers[i].biases[0] -= 0.1 * error[i];
    }

    double sum = 0.0;
    for (int i = 0; i < NUM_INPUTS; i++) {
        sum += input[i] * error[HIDDEN_LAYERS - 1];
    }
    sum *= output[0];

    error[0] = sigmoid(-sum);

    for (int i = 0; i < NUM_INPUTS; i++) {
        input[i] -= 0.1 * error[0];
    }
}

void train(layer *hidden_layers, double *input, double *target) {
    double output[HIDDEN_LAYERS + OUTPUT_LAYERS];

    forward_propagation(hidden_layers, input, output);

    for (int i = 0; i < OUTPUT_LAYERS; i++) {
        if (output[i] > 0.5) {
            target[i] = 1;
        } else {
            target[i] = 0;
        }
    }

    backpropagation(hidden_layers, input, output, target);
}

int main() {
    srand(time(NULL));

    layer hidden_layers[HIDDEN_LAYERS];

    for (int i = 0; i < HIDDEN_LAYERS; i++) {
        initialize_layers(&hidden_layers[i], NUM_HIDDEN_NEURONS);
    }

    double input[NUM_INPUTS];
    double target[OUTPUT_LAYERS];

    for (int i = 0; i < NUM_INPUTS; i++) {
        input[i] = (rand() % 100) / 100.0 - 0.5;
    }

    for (int i = 0; i < OUTPUT_LAYERS; i++) {
        target[i] = (rand() % 2);
    }

    for (int i = 0; i < 10000; i++) {
        train(hidden_layers, input, target);
    }

    return 0;
}