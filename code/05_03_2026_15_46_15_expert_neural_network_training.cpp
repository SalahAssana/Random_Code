#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

class NeuralNetwork {
public:
    NeuralNetwork(int inputNeurons, int hiddenNeurons, int outputNeurons) : 
        m_inputNeurons(inputNeurons), m_hiddenNeurons(hiddenNeurons), m_outputNeurons(outputNeurons),
        m_weights1(std::make_unique<std::vector<std::vector<double>>>()), 
        m_weights2(std::make_unique<std::vector<std::vector<double>>>()) {
        // Initialize weights
        for (int i = 0; i < inputNeurons; ++i) {
            m_weights1->push_back(std::vector<double>());
            for (int j = 0; j < hiddenNeurons; ++j) {
                m_weights1->at(i).push_back(rand() / static_cast<double>(RAND_MAX));
            }
        }
        for (int i = 0; i < hiddenNeurons; ++i) {
            m_weights2->push_back(std::vector<double>());
            for (int j = 0; j < outputNeurons; ++j) {
                m_weights2->at(i).push_back(rand() / static_cast<double>(RAND_MAX));
            }
        }
    }

    void train(const std::vector<double>& inputs, const std::vector<double>& targets) {
        // Forward pass
        std::vector<double> hidden(m_hiddenNeurons);
        for (int i = 0; i < m_hiddenNeurons; ++i) {
            double sum = 0.0;
            for (int j = 0; j < m_inputNeurons; ++j) {
                sum += inputs[j] * m_weights1->at(j)[i];
            }
            hidden[i] = sigmoid(sum);
        }

        std::vector<double> outputs(m_outputNeurons);
        for (int i = 0; i < m_outputNeurons; ++i) {
            double sum = 0.0;
            for (int j = 0; j < m_hiddenNeurons; ++j) {
                sum += hidden[j] * m_weights2->at(j)[i];
            }
            outputs[i] = sigmoid(sum);
        }

        // Backward pass
        std::vector<double> hiddenErrors(m_hiddenNeurons);
        for (int i = 0; i < m_outputNeurons; ++i) {
            double outputError = targets[i] - outputs[i];
            for (int j = 0; j < m_hiddenNeurons; ++j) {
                double weightUpdate = outputError * hidden[j] * (1.0 - hidden[j]) * m_weights2->at(j)[i];
                for (int k = 0; k < m_inputNeurons; ++k) {
                    m_weights1->at(k)[i] -= 0.1 * outputError * hidden[j] * (1.0 - hidden[j]) * inputs[k];
                }
            }
        }

        // Update weights
        for (int i = 0; i < m_hiddenNeurons; ++i) {
            double sum = 0.0;
            for (int j = 0; j < m_inputNeurons; ++j) {
                sum += inputs[j] * m_weights1->at(j)[i];
            }
            for (int k = 0; k < m_outputNeurons; ++k) {
                m_weights2->at(i)[k] -= 0.1 * (targets[k] - outputs[k]) * hidden[i] * (1.0 - hidden[i]);
            }
        }
    }

private:
    int m_inputNeurons;
    int m_hiddenNeurons;
    int m_outputNeurons;

    std::unique_ptr<std::vector<std::vector<double>>>& m_weights1;
    std::unique_ptr<std::vector<std::vector<double>>>& m_weights2;

    double sigmoid(double x) {
        return 1.0 / (1.0 + exp(-x));
    }
};

int main() {
    NeuralNetwork nn(3, 4, 2);
    std::vector<double> inputs = {0.5, 0.7, 0.9};
    std::vector<double> targets = {0.6, 0.1};
    for (int i = 0; i < 10000; ++i) {
        nn.train(inputs, targets);
    }
    return 0;
}