#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

class NeuralNetwork {
public:
    NeuralNetwork(int numLayers, int* neuronsPerLayer) : layers(numLayers), neuronsPerLayer(neuronsPerLayer) {
        for (int i = 0; i < numLayers; ++i) {
            Layer& layer = layers[i];
            layer.neurons.resize(neuronsPerLayer[i]);
            if (i > 0) {
                layer.weights.resize(neuronsPerLayer[i - 1], std::vector<double>(neuronsPerLayer[i]));
                for (auto& weight : layer.weights) {
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::normal_distribution<> normalDist(0.0, 1.0);
                    for (double& val : weight) {
                        val = normalDist(gen);
                    }
                }
            }
        }
    }

    void feedForward(const std::vector<double>& input) {
        Layer& currentLayer = layers[0];
        double sum;
        for (int i = 0; i < neuronsPerLayer[0]; ++i) {
            sum = 0.0;
            for (int j = 0; j < 1; ++j) {
                sum += input[j] * currentLayer.weights[i][j];
            }
            currentLayer.neurons[i] = std::tanh(sum);
        }

        for (int i = 1; i < neuronsPerLayer.size(); ++i) {
            Layer& currentLayer = layers[i];
            double sum;
            for (int j = 0; j < currentLayer.neurons.size(); ++j) {
                sum = 0.0;
                for (int k = 0; k < currentLayer.weights.size()[0]; ++k) {
                    sum += currentLayer.neurons[k] * currentLayer.weights[j][k];
                }
                currentLayer.neurons[j] = std::tanh(sum);
            }
        }
    }

    void backpropagate(const std::vector<double>& target) {
        Layer& outputLayer = layers.back();
        double error;
        for (int i = 0; i < neuronsPerLayer.size() - 1; ++i) {
            Layer& currentLayer = layers[i];
            Layer& nextLayer = layers[i + 1];
            error = 0.0;
            for (int j = 0; j < currentLayer.neurons.size(); ++j) {
                double output = currentLayer.neurons[j];
                double targetOutput = target[j];
                error += (targetOutput - output) * (1 - output) * (1 + output);
            }
            for (int j = 0; j < nextLayer.weights.size()[0]; ++j) {
                for (int k = 0; k < currentLayer.neurons.size(); ++k) {
                    double weightDelta = error * output * (1 - output) * currentLayer.neurons[k];
                    nextLayer.weights[j][k] -= 0.01 * weightDelta;
                }
            }
        }
    }

private:
    std::vector<Layer> layers;
    int* neuronsPerLayer;
};

struct Layer {
    std::vector<double> neurons;
    std::vector<std::vector<double>> weights;
};

int main() {
    int numLayers = 3;
    int neuronsPerLayer[] = {2, 4, 1};
    NeuralNetwork nn(numLayers, neuronsPerLayer);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> normalDist(0.0, 1.0);
    for (int i = 0; i < numLayers - 1; ++i) {
        Layer& layer = nn.layers[i];
        for (auto& weight : layer.weights) {
            for (double& val : weight) {
                val = normalDist(gen);
            }
        }
    }

    std::vector<double> input = {0.5, 0.5};
    nn.feedForward(input);

    std::vector<double> target = {0.8};
    nn.backpropagate(target);

    return 0;
}