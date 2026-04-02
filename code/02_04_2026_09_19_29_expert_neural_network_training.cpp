#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Layer {
    vector<double> weights;
    vector<double> biases;
};

class NeuralNetwork {
public:
    NeuralNetwork(int inputNeurons, int hiddenNeurons, int outputNeurons) 
        : inputNeurons(inputNeurons), hiddenNeurons(hiddenNeurons), outputNeurons(outputNeurons) {
        layers.push_back(Layer());
        layers.back().weights.resize(inputNeurons * hiddenNeurons);
        layers.back().biases.resize(hiddenNeurons);

        layers.push_back(Layer());
        layers.back().weights.resize(hiddenNeurons * outputNeurons);
        layers.back().biases.resize(outputNeurons);
    }

    void train(vector<vector<double>> inputs, vector<vector<double>> targets) {
        random_device rd;
        mt19937 gen(rd());
        normal_distribution<> nd(0.0, 1.0);

        for (int i = 0; i < 10000; ++i) {
            double error = 0.0;

            // Forward pass
            vector<double> hiddenLayerValues;
            for (int j = 0; j < hiddenNeurons; ++j) {
                double sum = 0.0;
                for (int k = 0; k < inputNeurons; ++k) {
                    sum += inputs[i][k] * layers[0].weights[k * hiddenNeurons + j];
                }
                sum += layers[0].biases[j];
                hiddenLayerValues.push_back(1.0 / (1.0 + exp(-sum)));
            }

            // Backward pass
            vector<double> outputLayerErrors;
            for (int j = 0; j < outputNeurons; ++j) {
                double sum = 0.0;
                for (int k = 0; k < hiddenNeurons; ++k) {
                    sum += hiddenLayerValues[k] * layers[1].weights[k * outputNeurons + j];
                }
                sum += layers[1].biases[j];

                double target = targets[i][j];
                double errorTerm = 2.0 * (target - sum) * (1.0 / (1.0 + exp(-sum)));
                outputLayerErrors.push_back(errorTerm);

                for (int k = 0; k < hiddenNeurons; ++k) {
                    layers[1].weights[k * outputNeurons + j] -= 0.01 * errorTerm * hiddenLayerValues[k];
                }
                layers[1].biases[j] -= 0.01 * errorTerm;
            }

            for (int j = 0; j < hiddenNeurons; ++j) {
                double sum = 0.0;
                for (int k = 0; k < inputNeurons; ++k) {
                    sum += inputs[i][k] * layers[0].weights[k * hiddenNeurons + j];
                }
                sum += layers[0].biases[j];

                double errorTerm = 0.0;
                for (int k = 0; k < outputNeurons; ++k) {
                    errorTerm += outputLayerErrors[k] * layers[1].weights[j * outputNeurons + k];
                }

                hiddenLayerValues[j] -= 0.01 * errorTerm;

                for (int k = 0; k < inputNeurons; ++k) {
                    layers[0].weights[k * hiddenNeurons + j] -= 0.01 * errorTerm * inputs[i][k];
                }
                layers[0].biases[j] -= 0.01 * errorTerm;
            }

            // Calculate total error
            for (int j = 0; j < outputNeurons; ++j) {
                error += pow(outputLayerErrors[j], 2);
            }
            cout << "Error at iteration " << i << ": " << error << endl;
        }
    }

private:
    int inputNeurons;
    int hiddenNeurons;
    int outputNeurons;
    vector<Layer> layers;
};

int main() {
    srand(time(0));

    NeuralNetwork nn(784, 256, 10);

    // Synthetic data
    vector<vector<double>> inputs;
    vector<vector<double>> targets;

    for (int i = 0; i < 10000; ++i) {
        vector<double> input(784);
        for (int j = 0; j < 28; ++j) {
            for (int k = 0; k < 28; ++k) {
                int val = rand() % 2;
                input[j * 28 + k] = val == 1 ? 1.0 : -1.0;
            }
        }

        inputs.push_back(input);

        vector<double> target(10);
        for (int j = 0; j < 10; ++j) {
            int val = rand() % 2;
            target[j] = val == 1 ? 1.0 : -1.0;
        }
        targets.push_back(target);
    }

    nn.train(inputs, targets);

    return 0;
}