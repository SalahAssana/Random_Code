#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

using namespace cv;
using namespace std;

class NeuralNetwork {
public:
    void train(vector<Mat> images, vector<int> labels) {
        // Initialize weights and biases
        Mat weights(28*28 + 1, 512, CV_32F);
        Mat biases(512, CV_32F);

        // Train the neural network using backpropagation algorithm
        for (int i = 0; i < images.size(); i++) {
            // Forward pass
            Mat output(1, 10, CV_32F);
            for (int j = 0; j < 10; j++) {
                float sum = 0;
                for (int k = 0; k < 28*28 + 1; k++) {
                    sum += images[i].at<float>(k) * weights.at<float>(k, j);
                }
                output.at<float>(0, j) = sigmoid(sum + biases.at<float>(j));
            }

            // Backward pass
            Mat error(10, CV_32F);
            for (int j = 0; j < 10; j++) {
                error.at<float>(0, j) = labels[i] * output.at<float>(0, j) - (1 - labels[i]) * (1 - output.at<float>(0, j));
            }

            // Update weights and biases
            for (int j = 0; j < 10; j++) {
                for (int k = 0; k < 28*28 + 1; k++) {
                    weights.at<float>(k, j) += 0.1 * error.at<float>(0, j) * images[i].at<float>(k);
                }
                biases.at<float>(j) += 0.1 * error.at<float>(0, j);
            }
        }
    }

    void classify(vector<Mat> images, vector<int>& labels) {
        // Initialize output
        Mat output(1, 10, CV_32F);

        // Classify the images using the trained neural network
        for (int i = 0; i < images.size(); i++) {
            float sum = 0;
            for (int j = 0; j < 28*28 + 1; j++) {
                sum += images[i].at<float>(j) * weight.at<float>(j, 0);
            }
            output.at<float>(0, 0) = sigmoid(sum + bias.at<float>(0));

            for (int j = 1; j < 10; j++) {
                float s = 0;
                for (int k = 0; k < 28*28 + 1; k++) {
                    s += images[i].at<float>(k) * weight.at<float>(k, j);
                }
                output.at<float>(0, j) = sigmoid(s + bias.at<float>(j));
            }

            // Find the index of the maximum value in the output
            int maxIndex = 0;
            for (int j = 1; j < 10; j++) {
                if (output.at<float>(0, j) > output.at<float>(0, maxIndex)) {
                    maxIndex = j;
                }
            }

            // Update the label
            labels[i] = maxIndex;
        }
    }

private:
    float sigmoid(float x) {
        return 1 / (1 + exp(-x));
    }
};

int main() {
    NeuralNetwork nn;

    // Load the training data
    vector<Mat> images;
    vector<int> labels;
    for (int i = 0; i < 1000; i++) {
        Mat image = imread("image" + to_string(i) + ".png");
        resize(image, image, Size(28, 28));
        // Convert the image to grayscale
        cvtColor(image, image, COLOR_BGR2GRAY);
        images.push_back(image);
    }

    // Train the neural network using the training data
    nn.train(images, labels);

    // Load the testing data
    vector<Mat> testImages;
    for (int i = 0; i < 100; i++) {
        Mat image = imread("testImage" + to_string(i) + ".png");
        resize(image, image, Size(28, 28));
        cvtColor(image, image, COLOR_BGR2GRAY);
        testImages.push_back(image);
    }

    // Classify the testing data using the trained neural network
    vector<int> testLabels;
    nn.classify(testImages, testLabels);

    return 0;
}