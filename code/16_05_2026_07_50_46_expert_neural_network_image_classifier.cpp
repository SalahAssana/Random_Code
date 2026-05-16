#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// Define a struct to represent an image
struct Image {
    Mat img;
    int label;
};

// Define a class for the neural network
class NeuralNetwork {
public:
    // Constructor
    NeuralNetwork(int inputSize, int hiddenSize, int outputSize) {
        // Initialize weights and biases for the layers
        this->inputLayerWeights = vector<vector<double>>(inputSize, vector<double>(hiddenSize));
        this->inputLayerBiases = vector<double>(hiddenSize);
        this->hiddenLayerWeights = vector<vector<double>>(hiddenSize, vector<double>(outputSize));
        this->hiddenLayerBiases = vector<double>(outputSize);

        // Initialize the activation functions
        this->activationFunctions = vector<function<double(double)>>({[] (double x) { return x > 0 ? 1 : 0; }, [](double x) { return exp(x); }});
    }

    // Train the neural network using backpropagation
    void train(vector<Image>& images, int epochs) {
        for (int epoch = 0; epoch < epochs; epoch++) {
            for (Image& image : images) {
                // Forward pass
                vector<double> hiddenValues;
                for (int i = 0; i < this->hiddenLayerWeights.size(); i++) {
                    double sum = 0;
                    for (int j = 0; j < this->inputLayerWeights[0].size(); j++) {
                        sum += this->inputLayerWeights[i][j] * image.img.at<uchar>(j);
                    }
                    hiddenValues.push_back(this->activationFunctions[0](sum + this->inputLayerBiases[i]));
                }

                // Backward pass
                for (int i = 0; i < this->hiddenLayerWeights.size(); i++) {
                    double sum = 0;
                    for (int j = 0; j < this->hiddenLayerWeights[0].size(); j++) {
                        sum += this->hiddenLayerWeights[i][j] * image.label;
                    }
                    this->inputLayerBiases[i] -= this->activationFunctions[1](sum + this->hiddenLayerBiases[i]);
                }

                for (int i = 0; i < this->hiddenLayerWeights.size(); i++) {
                    double sum = 0;
                    for (int j = 0; j < this->inputLayerWeights.size(); j++) {
                        sum += this->inputLayerWeights[j][i] * hiddenValues[j];
                    }
                    this->hiddenLayerBiases[i] -= image.label - this->activationFunctions[1](sum);
                }

                // Update the weights
                for (int i = 0; i < this->inputLayerWeights.size(); i++) {
                    for (int j = 0; j < this->inputLayerWeights[0].size(); j++) {
                        this->inputLayerWeights[i][j] -= image.label - this->activationFunctions[1](sum);
                    }
                }

                for (int i = 0; i < this->hiddenLayerWeights.size(); i++) {
                    for (int j = 0; j < this->hiddenLayerWeights[0].size(); j++) {
                        this->hiddenLayerWeights[i][j] -= image.label - this->activationFunctions[1](sum);
                    }
                }
            }
        }
    }

    // Test the neural network using a test image
    int test(Image& image) {
        vector<double> hiddenValues;
        for (int i = 0; i < this->hiddenLayerWeights.size(); i++) {
            double sum = 0;
            for (int j = 0; j < this->inputLayerWeights[0].size(); j++) {
                sum += this->inputLayerWeights[i][j] * image.img.at<uchar>(j);
            }
            hiddenValues.push_back(this->activationFunctions[0](sum + this->inputLayerBiases[i]));
        }

        int label = 0;
        for (int i = 0; i < this->hiddenLayerWeights.size(); i++) {
            double sum = 0;
            for (int j = 0; j < this->hiddenLayerWeights[0].size(); j++) {
                sum += this->hiddenLayerWeights[i][j] * hiddenValues[j];
            }
            label = max(label, int(this->activationFunctions[1](sum + this->hiddenLayerBiases[i])));
        }

        return label;
    }

private:
    vector<vector<double>> inputLayerWeights;
    vector<double> inputLayerBiases;
    vector<vector<double>> hiddenLayerWeights;
    vector<double> hiddenLayerBiases;
    vector<function<double(double)>> activationFunctions;
};

int main() {
    // Load the training images
    vector<Image> trainImages = {{Mat(28, 28, CV_8UC1), 0}, {Mat(28, 28, CV_8UC1), 1}};

    // Create a neural network with one hidden layer
    NeuralNetwork nn(784, 128, 10);

    // Train the neural network
    nn.train(trainImages, 100);

    // Load a test image
    Image testImage = {Mat(28, 28, CV_8UC1), 0};

    // Test the neural network
    int label = nn.test(testImage);

    cout << "Predicted label: " << label << endl;

    return 0;
}