#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define INPUT_NEURONS 784
#define HIDDEN_NEURONS 256
#define OUTPUT_NEURONS 10
#define EPOCHS 10
#define LEARNING_RATE 0.1

typedef struct {
    double* inputs;
    int size;
} input_t;

typedef struct {
    double* weights;
    int size;
} weight_t;

void init_weights(weight_t* w, int n) {
    w->size = n;
    w->weights = (double*)malloc(n * sizeof(double));
    for(int i = 0; i < n; i++) {
        w->weights[i] = rand() / (RAND_MAX + 1.0);
    }
}

void free_weights(weight_t* w) {
    free(w->weights);
    w->size = 0;
}

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

input_t generate_input(int size) {
    input_t i;
    i.size = size;
    i.inputs = (double*)malloc(size * sizeof(double));
    for(int j = 0; j < size; j++) {
        i.inputs[j] = rand() / (RAND_MAX + 1.0);
    }
    return i;
}

void free_input(input_t* i) {
    free(i->inputs);
    i->size = 0;
}

void forward_pass(input_t* input, weight_t* weights, double* output) {
    int hidden_layer_size = HIDDEN_NEURONS;
    double* hidden_layer = (double*)malloc(hidden_layer_size * sizeof(double));
    for(int i = 0; i < INPUT_NEURONS; i++) {
        double sum = 0.0;
        for(int j = 0; j < hidden_layer_size; j++) {
            sum += input->inputs[i] * weights->weights[j];
        }
        hidden_layer[j] = sigmoid(sum);
    }

    int output_layer_size = OUTPUT_NEURONS;
    double* output_layer = (double*)malloc(output_layer_size * sizeof(double));
    for(int i = 0; i < hidden_layer_size; i++) {
        double sum = 0.0;
        for(int j = 0; j < output_layer_size; j++) {
            sum += hidden_layer[i] * weights->weights[OUTPUT_NEURONS + j];
        }
        output_layer[j] = sigmoid(sum);
    }

    for(int i = 0; i < output_layer_size; i++) {
        output[i] = output_layer[i];
    }

    free(hidden_layer);
    free(output_layer);
}

void backpropagate(input_t* input, weight_t* weights, double* error) {
    int hidden_layer_size = HIDDEN_NEURONS;
    double* hidden_layer = (double*)malloc(hidden_layer_size * sizeof(double));
    for(int i = 0; i < INPUT_NEURONS; i++) {
        double sum = 0.0;
        for(int j = 0; j < hidden_layer_size; j++) {
            sum += input->inputs[i] * weights->weights[j];
        }
        hidden_layer[j] = sigmoid(sum);
    }

    int output_layer_size = OUTPUT_NEURONS;
    double* output_layer = (double*)malloc(output_layer_size * sizeof(double));
    for(int i = 0; i < hidden_layer_size; i++) {
        double sum = 0.0;
        for(int j = 0; j < output_layer_size; j++) {
            sum += hidden_layer[i] * weights->weights[OUTPUT_NEURONS + j];
        }
        output_layer[j] = sigmoid(sum);
    }

    for(int i = 0; i < output_layer_size; i++) {
        error[i] = (output_layer[i] - input->size) * sigmoid(output_layer[i]) * (1.0 - sigmoid(output_layer[i]));
    }

    free(hidden_layer);
    free(output_layer);
}

int main() {
    srand(time(NULL));
    weight_t weights;
    init_weights(&weights, INPUT_NEURONS + HIDDEN_NEURONS + OUTPUT_NEURONS);

    input_t input = generate_input(INPUT_NEURONS);
    double output[OUTPUT_NEURONS];
    forward_pass(&input, &weights, output);

    for(int epoch = 0; epoch < EPOCHS; epoch++) {
        backpropagate(&input, &weights, output);
        for(int i = 0; i < OUTPUT_NEURONS; i++) {
            weights.weights[INPUT_NEURONS + HIDDEN_NEURONS + i] += LEARNING_RATE * output[i];
        }
    }

    free_weights(&weights);
    free_input(&input);

    return 0;
}