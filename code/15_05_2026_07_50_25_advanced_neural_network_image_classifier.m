% Neural Network Image Classifier

% Import necessary libraries
import java.util.*;
import java.io.*;

class Image {
    public String label;
    public double[][] features;

    public Image(String label, double[][] features) {
        this.label = label;
        this.features = features;
    }
}

class NeuralNetwork {
    public int inputSize;
    public int hiddenSize;
    public int outputSize;
    public double[][] weights1;
    public double[][] weights2;
    public double[] bias;

    public NeuralNetwork(int inputSize, int hiddenSize, int outputSize) {
        this.inputSize = inputSize;
        this.hiddenSize = hiddenSize;
        this.outputSize = outputSize;
        this.weights1 = new double[inputSize][hiddenSize];
        this.weights2 = new double[hiddenSize][outputSize];
        this.bias = new double[hiddenSize + outputSize];

        for (int i = 0; i < inputSize; i++) {
            for (int j = 0; j < hiddenSize; j++) {
                weights1[i][j] = Math.random() * 2 - 1;
            }
        }

        for (int i = 0; i < hiddenSize; i++) {
            for (int j = 0; j < outputSize; j++) {
                weights2[i][j] = Math.random() * 2 - 1;
            }
        }

        for (int i = 0; i < hiddenSize; i++) {
            bias[i] = Math.random() * 2 - 1;
        }

        for (int i = 0; i < outputSize; i++) {
            bias[hiddenSize + i] = Math.random() * 2 - 1;
        }
    }

    public double[] feedForward(double[][] input) {
        double[] hiddenLayer = new double[hiddenSize];
        double[] outputLayer = new double[outputSize];

        for (int i = 0; i < hiddenSize; i++) {
            double sum = 0;
            for (int j = 0; j < inputSize; j++) {
                sum += weights1[j][i] * input[j];
            }
            hiddenLayer[i] = sigmoid(sum + bias[i]);
        }

        for (int i = 0; i < outputSize; i++) {
            double sum = 0;
            for (int j = 0; j < hiddenSize; j++) {
                sum += weights2[j][i] * hiddenLayer[j];
            }
            outputLayer[i] = sigmoid(sum + bias[hiddenSize + i]);
        }

        return outputLayer;
    }

    public double sigmoid(double x) {
        return 1 / (1 + Math.exp(-x));
    }
}

class NeuralNetworkTrainer {
    public static void train(NeuralNetwork network, List<Image> images, int epochs) {
        for (int i = 0; i < epochs; i++) {
            for (Image image : images) {
                double[] input = new double[image.features.length];
                for (int j = 0; j < image.features.length; j++) {
                    input[j] = image.features[0][j];
                }

                double[] output = network.feedForward(input);
                double[] target = new double[network.outputSize];
                for (int j = 0; j < network.outputSize; j++) {
                    if (image.label.equals("class" + (j + 1))) {
                        target[j] = 1;
                    } else {
                        target[j] = 0;
                    }
                }

                double[] errors = new double[network.outputSize];
                for (int j = 0; j < network.outputSize; j++) {
                    errors[j] = target[j] - output[j];
                }

                for (int j = 0; j < network.hiddenSize; j++) {
                    for (int k = 0; k < network.outputSize; j++) {
                        double newWeight1 = weights1[0][j] + 0.01 * errors[k] * input[0];
                        weights1[0][j] = newWeight1;
                    }
                }

                for (int j = 0; j < network.outputSize; j++) {
                    double newWeight2 = weights2[0][j] + 0.01 * errors[j] * hiddenLayer[0];
                    weights2[0][j] = newWeight2;
                }
            }
        }
    }
}

public class Main {
    public static void main(String[] args) {
        List<Image> images = new ArrayList<>();

        // Add your training data here
        images.add(new Image("class1", {{1, 2}, {3, 4}}));
        images.add(new Image("class1", {{5, 6}, {7, 8}}));
        images.add(new Image("class2", {{9, 10}, {11, 12}}));
        images.add(new Image("class2", {{13, 14}, {15, 16}}));

        NeuralNetwork network = new NeuralNetwork(2, 4, 2);
        NeuralNetworkTrainer.train(network, images, 1000);

        // Add your testing data here
        double[][] testInput1 = {{17, 18}};
        double[] output1 = network.feedForward(testInput1);
        System.out.println("Predicted class for image 1: " + (output1[0] > output1[1]));

        double[][] testInput2 = {{19, 20}};
        double[] output2 = network.feedForward(testInput2);
        System.out.println("Predicted class for image 2: " + (output2[0] > output2[1]));
    }
}