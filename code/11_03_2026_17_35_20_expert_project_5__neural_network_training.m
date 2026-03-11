% Project 5: Neural Network Training
% Author: [Your Name]
% Date: [Current Date]

clear; clc;

% Define constants and parameters
NUM_INPUTS = 784;
HIDDEN_LAYERS = 2;
OUTPUT_LAYER = 10;
LEARNING_RATE = 0.1;
MOMENTUM = 0.5;
REGULARIZATION_TERM = 0.001;
MAX_EPOCHS = 100;

% Load MNIST dataset (synthetic data)
load mnist_all.mat

% Preprocess data
X_train = X_train / 255;
Y_train = Y_train - 1;
X_test = X_test / 255;
Y_test = Y_test - 1;

% Define a neural network class
classdef NeuralNetwork < handle
    properties
        inputs
        hiddenLayers
        outputs
        weights
        biases
        deltas
        momentum
    end
    
    methods
        function obj = NeuralNetwork(inputs, hiddenLayers, outputs)
            obj.inputs = inputs;
            obj.hiddenLayers = hiddenLayers;
            obj.outputs = outputs;
            obj.weights = cell(1, length(hiddenLayers) + 1);
            obj.biases = cell(1, length(hiddenLayers) + 1);
            obj.deltas = cell(1, length(hiddenLayers) + 1);
            obj.momentum = Momentum(LEARNING_RATE, MOMENTUM);
        end
        
        function [output] = forwardPass(obj, input)
            % Forward pass
            output = zeros(size(input));
            for i = 1:length(obj.hiddenLayers)
                weights = obj.weights{i};
                biases = obj.biases{i};
                output = sigmoid(sum((weights * input + repmat(biases, 1, size(input, 2))).*obj.deltas{i}) + REGULARIZATION_TERM);
            end
            output = sigmoid(sum((obj.weights{end} * output + repmat(obj.biases{end}, 1, size(output, 2))).*obj.deltas{end}) + REGULARIZATION_TERM);
        end
        
        function [delta] = backPropagate(obj, input, target)
            % Backpropagation
            delta = zeros(size(input));
            for i = length(obj.hiddenLayers) : -1 : 1
                weights = obj.weights{i};
                biases = obj.biases{i};
                output = sigmoid(sum((weights * input + repmat(biases, 1, size(input, 2))).*obj.deltas{i}) + REGULARIZATION_TERM);
                error = target - output;
                delta = (error .* sigmoidDerivative(output)) * weights';
                obj.deltas{i} = delta;
            end
            for i = 1 : length(obj.hiddenLayers)
                weights = obj.weights{i};
                biases = obj.biases{i};
                output = sigmoid(sum((weights * input + repmat(biases, 1, size(input, 2))).*obj.deltas{i}) + REGULARIZATION_TERM);
                error = target - output;
                delta = (error .* sigmoidDerivative(output)) * weights';
                obj.deltas{i} = delta;
            end
        end
        
        function [weights, biases] = updateParameters(obj, input, target)
            % Update parameters
            for i = 1:length(obj.hiddenLayers) + 1
                if i == length(obj.hiddenLayers) + 1
                    weights = (obj.deltas{i} * input') + REGULARIZATION_TERM;
                else
                    weights = (obj.deltas{i} * obj.weights{i}' + REGULARIZATION_TERM);
                end
                biases = (obj.deltas{i});
            end
        end
        
        function [accuracy] = evaluate(obj, X_test, Y_test)
            % Evaluate the neural network
            predictions = zeros(size(Y_test));
            for i = 1:size(X_test, 1)
                input = X_test(i, :);
                output = obj.forwardPass(input);
                predictions(i) = find(max(output) == output);
            end
            accuracy = mean(predictions == Y_test);
        end
        
    end
    
end

% Create a neural network instance
nn = NeuralNetwork(NUM_INPUTS, HIDDEN_LAYERS, OUTPUT_LAYER);

% Train the neural network
for epoch = 1 : MAX_EPOCHS
    for i = 1:size(X_train, 1)
        input = X_train(i, :);
        target = Y_train(i, :);
        nn.backPropagate(input, target);
        nn.updateParameters(input, target);
    end
end

% Evaluate the neural network
accuracy = nn.evaluate(X_test, Y_test);

% Display the accuracy
fprintf('Accuracy: %.2f%%\n', accuracy * 100);
```
