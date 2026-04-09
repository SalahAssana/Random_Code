#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define LEARNING_RATE 0.01
#define EPOCHS 10
#define HIDDEN_LAYERS 2
#define HIDDEN_NEURONS 256
#define INPUT_NEURONS 28*28
#define OUTPUT_NEURONS 10

typedef struct {
    double *weights;
    double *bias;
} Neuron;

typedef struct {
    Neuron **neurons;
    int neurons_count;
} Layer;

typedef struct {
    Layer **layers;
    int layers_count;
} Network;

Network create_network() {
    Network network = (Network)malloc(sizeof(struct Network));
    network->layers_count = HIDDEN_LAYERS + 2; // input, hidden, output
    network->layers = (Layer*)malloc(network->layers_count * sizeof(Layer));

    for(int i = 0; i < network->layers_count; i++) {
        network->layers[i].neurons_count = (i == 0) ? INPUT_NEURONS : ((i == HIDDEN_LAYERS + 1) ? OUTPUT_NEURONS : HIDDEN_NEURONS);
        network->layers[i].neurons = (Neuron*)malloc(network->layers[i].neurons_count * sizeof(Neuron));

        for(int j = 0; j < network->layers[i].neurons_count; j++) {
            network->layers[i].neurons[j].weights = (double*)malloc((i == HIDDEN_LAYERS + 1) ? OUTPUT_NEURONS : HIDDEN_NEURONS * sizeof(double));
            network->layers[i].neurons[j].bias = (double*)malloc(sizeof(double));

            if(i == 0) {
                // input layer
                for(int k = 0; k < INPUT_NEURONS; k++) {
                    network->layers[i].neurons[j].weights[k] = ((double)rand() / RAND_MAX) - 0.5;
                }
                network->layers[i].neurons[j].bias[0] = 0.0;

            } else if(i == HIDDEN_LAYERS + 1) {
                // output layer
                for(int k = 0; k < OUTPUT_NEURONS; k++) {
                    network->layers[i].neurons[j].weights[k] = ((double)rand() / RAND_MAX) - 0.5;
                }
                network->layers[i].neurons[j].bias[0] = 0.0;

            } else {
                // hidden layers
                for(int k = 0; k < HIDDEN_NEURONS; k++) {
                    network->layers[i].neurons[j].weights[k] = ((double)rand() / RAND_MAX) - 0.5;
                }
                network->layers[i].neurons[j].bias[0] = 0.0;
            }
        }
    }

    return network;
}

void forward_propagate(Network network, double *input) {
    for(int i = 0; i < network->layers_count; i++) {
        Layer *layer = &network->layers[i];
        for(int j = 0; j < layer->neurons_count; j++) {
            Neuron *neuron = &layer->neurons[j];

            double sum = 0.0;
            if(i == 0) {
                // input layer
                for(int k = 0; k < INPUT_NEURONS; k++) {
                    sum += input[k] * neuron->weights[k];
                }
            } else if(i > 0 && i < HIDDEN_LAYERS + 1) {
                // hidden layers
                for(int k = 0; k < HIDDEN_NEURONS; k++) {
                    sum += layer->neurons[j-1].output * neuron->weights[k];
                }
            } else if(i == HIDDEN_LAYERS + 1) {
                // output layer
                for(int k = 0; k < OUTPUT_NEURONS; k++) {
                    sum += layer->neurons[j-1].output * neuron->weights[k];
                }
            }

            double sigmoid_output = 1.0 / (1.0 + exp(-sum));
            neuron->output = sigmoid_output;
        }
    }
}

void backpropagate(Network network, double *input, double *target) {
    for(int i = 0; i < network->layers_count; i++) {
        Layer *layer = &network->layers[i];
        for(int j = 0; j < layer->neurons_count; j++) {
            Neuron *neuron = &layer->neurons[j];

            double error = 0.0;
            if(i == HIDDEN_LAYERS + 1) {
                // output layer
                error = target[0] - neuron->output;
            } else {
                // hidden layers
                for(int k = 0; k < network->layers[i+1].neurons_count; k++) {
                    error += (network->layers[i+1].neurons[k].output * neuron->weights[k]) * (1.0 - neuron->output) * neuron->output;
                }
            }

            double delta = LEARNING_RATE * error;
            for(int k = 0; k < layer->neurons_count; k++) {
                Neuron *prev_neuron = &layer->neurons[k];
                neuron->weights[k] -= delta * prev_neuron->output;
                neuron->bias[0] -= delta;
            }
        }
    }
}

void train(Network network, double *input, double *target) {
    forward_propagate(network, input);
    backpropagate(network, input, target);

    for(int i = 0; i < EPOCHS; i++) {
        for(int j = 0; j < network->layers_count - 1; j++) {
            Layer *layer = &network->layers[j];
            for(int k = 0; k < layer->neurons_count; k++) {
                Neuron *neuron = &layer->neurons[k];

                double sum = 0.0;
                if(j == 0) {
                    // input layer
                    for(int l = 0; l < INPUT_NEURONS; l++) {
                        sum += input[l] * neuron->weights[l];
                    }
                } else {
                    // hidden layers
                    for(int l = 0; l < HIDDEN_NEURONS; l++) {
                        sum += layer->neurons[k-1].output * neuron->weights[l];
                    }
                }

                double sigmoid_output = 1.0 / (1.0 + exp(-sum));
                neuron->output = sigmoid_output;
            }
        }

        backpropagate(network, input, target);
    }
}

int main() {
    srand(time(NULL));

    Network network = create_network();

    // synthetic data
    double *input = (double*)malloc(INPUT_NEURONS * sizeof(double));
    for(int i = 0; i < INPUT_NEURONS; i++) {
        input[i] = ((double)rand() / RAND_MAX) - 0.5;
    }

    double *target = (double*)malloc(OUTPUT_NEURONS * sizeof(double));
    for(int i = 0; i < OUTPUT_NEURONS; i++) {
        target[i] = ((double)rand() / RAND_MAX) % 10;
    }

    train(network, input, target);

    return 0;
}