#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

// Using namespace std;
using namespace std;

// Constants
const int IMG_WIDTH = 28;
const int IMG_HEIGHT = 28;
const int NUM_CLASSES = 10;
const int TRAINING_EPOCHS = 30;
const float LEARNING_RATE = 0.001f;
const int BATCH_SIZE = 100;

// Convolutional Neural Network Class
class CNN {
public:
    // Constructor
    CNN(int numFilters, int kernelSize);

    // Destructor
    ~CNN();

    // Train the network
    void train(const vector<vector<vector<float>>>& trainingData,
               const vector<int>& trainingLabels);

    // Test the network
    float test(const vector<vector<vector<float>>>& testData,
               const vector<int>& testLabels);

private:
    // Neural Network Layers
    struct Layer {
        int numFilters;
        int kernelSize;
        vector<vector<float>> weights;
        vector<float> biases;
    };

    // Convolutional Layer
    void convolutionalLayer(vector<vector<vector<float>>>& input,
                             vector<Layer>& layers);

    // Max Pooling Layer
    vector<vector<vector<float>>> maxPoolingLayer(const vector<vector<vector<float>>>& input);

    // Fully Connected (Dense) Layer
    vector<float> fullyConnectedLayer(const vector<vector<vector<float>>>& input,
                                       const int numNeurons);

    // Sigmoid Activation Function
    float sigmoid(float x);

    // ReLU Activation Function
    float relu(float x);

    // Softmax Activation Function
    float softmax(float x, int numClasses);

    // Calculate Cross-Entropy Loss
    float crossEntropyLoss(const vector<float>& predicted,
                            const int expectedLabel);

    // Backpropagation Algorithm
    void backpropagation(vector<vector<vector<float>>>& input,
                         vector<int>& labels,
                         vector<Layer>& layers);

    // Gradient Descent Optimization Algorithm
    void gradientDescent(float learningRate, float momentum);

    // Neural Network Weights and Biases
    vector<float> weights;
    vector<float> biases;

    int numFilters;
    int kernelSize;
};

// CNN Constructor
CNN::CNN(int numFilters, int kernelSize) {
    this->numFilters = numFilters;
    this->kernelSize = kernelSize;
}

// CNN Destructor
CNN::~CNN() {}

// Train the network
void CNN::train(const vector<vector<vector<float>>>& trainingData,
               const vector<int>& trainingLabels) {
    // Initialize weights and biases for each layer
    vector<Layer> layers;
    for (int i = 0; i < numFilters; ++i) {
        Layer layer;
        layer.numFilters = i + 1;
        layer.kernelSize = kernelSize;
        layer.weights.resize(IMG_WIDTH, IMG_HEIGHT);
        layer.biases.resize(numClasses);
        layers.push_back(layer);
    }

    // Train the network using backpropagation and gradient descent
    for (int epoch = 0; epoch < TRAINING_EPOCHS; ++epoch) {
        for (int i = 0; i < trainingData.size(); ++i) {
            vector<vector<float>> input(trainingData[i]);
            int label = trainingLabels[i];

            // Forward pass
            convolutionalLayer(input, layers);
            // Max pooling layer
            input = maxPoolingLayer(input);
            // Fully connected layer
            vector<float> hidden = fullyConnectedLayer(input, numClasses);

            // Calculate cross-entropy loss
            float loss = crossEntropyLoss(hidden, label);

            // Backpropagation
            backpropagation(input, label, layers);

            // Gradient descent optimization
            gradientDescent(LEARNING_RATE, 0.9f);
        }
    }
}

// Test the network
float CNN::test(const vector<vector<vector<float>>>& testData,
               const vector<int>& testLabels) {
    float accuracy = 0.0f;
    for (int i = 0; i < testData.size(); ++i) {
        vector<vector<float>> input(testData[i]);
        int label = testLabels[i];

        // Forward pass
        convolutionalLayer(input, layers);
        // Max pooling layer
        input = maxPoolingLayer(input);
        // Fully connected layer
        vector<float> hidden = fullyConnectedLayer(input, numClasses);

        // Predict the class
        float predicted = 0.0f;
        for (int j = 0; j < numClasses; ++j) {
            predicted += softmax(hidden[j], numClasses);
        }

        // Calculate accuracy
        int predictedClass = argmax(predicted);
        if (predictedClass == label) {
            accuracy++;
        }
    }
    return accuracy / testData.size();
}

// Convolutional Layer
void CNN::convolutionalLayer(vector<vector<vector<float>>>& input,
                             vector<Layer>& layers) {
    for (int i = 0; i < numFilters; ++i) {
        // Apply convolution and activation to each filter
        vector<float> output(IMG_WIDTH * IMG_HEIGHT);
        for (int j = 0; j < IMG_WIDTH; ++j) {
            for (int k = 0; k < IMG_HEIGHT; ++k) {
                float sum = 0.0f;
                for (int m = 0; m < kernelSize; ++m) {
                    for (int n = 0; n < kernelSize; ++n) {
                        sum += layers[i].weights[j][k][m][n] * input[j + m][k + n];
                    }
                }
                output[j * IMG_HEIGHT + k] = relu(sum);
            }
        }
    }
}

// Max Pooling Layer
vector<vector<vector<float>>> CNN::maxPoolingLayer(const vector<vector<vector<float>>>& input) {
    vector<vector<vector<float>>> pooled(IMG_WIDTH / 2, IMG_HEIGHT / 2);
    for (int i = 0; i < IMG_WIDTH / 2; ++i) {
        for (int j = 0; j < IMG_HEIGHT / 2; ++j) {
            float maxVal = -INFINITY;
            for (int k = 0; k < kernelSize; ++k) {
                for (int l = 0; l < kernelSize; ++l) {
                    if (input[i * 2 + k][j * 2 + l] > maxVal) {
                        maxVal = input[i * 2 + k][j * 2 + l];
                    }
                }
            }
            pooled[i][j] = maxVal;
        }
    }
    return pooled;
}

// Fully Connected (Dense) Layer
vector<float> CNN::fullyConnectedLayer(const vector<vector<vector<float>>>& input,
                                       const int numNeurons) {
    vector<float> hidden(input.size(), 0.0f);
    for (int i = 0; i < input.size(); ++i) {
        float sum = 0.0f;
        for (int j = 0; j < input[i].size(); ++j) {
            sum += input[i][j] * weights[j];
        }
        hidden[i] = sigmoid(sum);
    }
    return hidden;
}

// Sigmoid Activation Function
float CNN::sigmoid(float x) {
    return 1.0f / (1.0f + exp(-x));
}

// ReLU Activation Function
float CNN::relu(float x) {
    return max(x, 0.0f);
}

// Softmax Activation Function
float CNN::softmax(float x, int numClasses) {
    float sum = 0.0f;
    for (int i = 0; i < numClasses; ++i) {
        sum += exp(x - log(numClasses));
    }
    return exp(x - log(sum)) / sum;
}

// Calculate Cross-Entropy Loss
float CNN::crossEntropyLoss(const vector<float>& predicted,
                            const int expectedLabel) {
    float loss = 0.0f;
    for (int i = 0; i < numClasses; ++i) {
        if (i == expectedLabel) {
            loss -= log(predicted[i]);
        }
    }
    return loss;
}

// Backpropagation Algorithm
void CNN::backpropagation(vector<vector<vector<float>>>& input,
                         vector<int>& labels,
                         vector<Layer>& layers) {
    for (int i = 0; i < numFilters; ++i) {
        // Calculate error gradient for each filter
        vector<float> errorGradient(layers[i].weights.size(), 0.0f);
        for (int j = 0; j < IMG_WIDTH; ++j) {
            for (int k = 0; k < IMG_HEIGHT; ++k) {
                float sum = 0.0f;
                for (int m = 0; m < kernelSize; ++m) {
                    for (int n = 0; n < kernelSize; ++n) {
                        sum += layers[i].weights[j][k][m][n] * input[j + m][k + n];
                    }
                }
                errorGradient[j][k] = relu(sum);
            }
        }

        // Update weights and biases
        for (int j = 0; j < IMG_WIDTH; ++j) {
            for (int k = 0; k < IMG_HEIGHT; ++k) {
                for (int m = 0; m < kernelSize; ++m) {
                    for (int n = 0; n < kernelSize; ++n) {
                        layers[i].weights[j][k][m][n] -= LEARNING_RATE * errorGradient[j + m][k + n];
                    }
                }
            }
        }
    }
}

// Gradient Descent Optimization Algorithm
void CNN::gradientDescent(float learningRate, float momentum) {
    // Update weights and biases using gradient descent
}