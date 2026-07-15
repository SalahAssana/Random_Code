% Neural Network for Handwritten Digit Recognition
%
% This script demonstrates a neural network implementation using backpropagation
% and stochastic gradient descent to recognize handwritten digits (0-9).
%

classdef NeuralNetwork < handle
    properties
        inputLayerSize
        hiddenLayerSize
        outputLayerSize
        inputs
        hiddenLayer
        outputs
    end
    
    methods
        function obj = NeuralNetwork(inputLayerSize, hiddenLayerSize, outputLayerSize)
            % Constructor: Initialize the neural network with given sizes.
            obj.inputLayerSize = inputLayerSize;
            obj.hiddenLayerSize = hiddenLayerSize;
            obj.outputLayerSize = outputLayerSize;
            
            % Randomly initialize weights and biases for the layers
            obj.hiddenLayer = rand(obj.hiddenLayerSize, obj.inputLayerSize) * 2 - 1;
            obj.outputs = zeros(obj.outputLayerSize, 1);
        end
        
        function y = predict(obj, x)
            % Forward pass: Compute the output of the neural network.
            z = [ones(1, 1), x];  % Add bias term
            hidden = sigmoid(z * obj.hiddenLayer');
            y = sigmoid(hidden * obj.outputs');
        end
        
        function [gradInp, gradHidden] = computeGradients(obj, x, t)
            % Backpropagation: Compute the gradients of the loss with respect to inputs and hidden layer.
            z = [ones(1, 1), x];  % Add bias term
            hidden = sigmoid(z * obj.hiddenLayer');
            outputs = sigmoid(hidden * obj.outputs');
            
            % Compute the error between predicted output and actual target
            deltaOutputs = (outputs - t) .* outputs .* (1 - outputs);
            deltaHidden = (hidden - 0.5) .* hidden .* (1 - hidden);
            error = deltaOutputs * obj.outputs;
            
            % Compute gradients for inputs and hidden layer using chain rule
            gradInp = error * z(2:end) .* (hidden .* (1 - hidden));
            gradHidden = error * hidden' * z(2:end);
        end
        
        function [obj] = train(obj, x, t)
            % Stochastic gradient descent: Update the neural network weights.
            [gradInp, gradHidden] = obj.computeGradients(x, t);
            
            % Update weights for inputs and hidden layer
            obj.hiddenLayer -= 0.1 * (gradHidden' / obj.inputLayerSize);
            obj.outputs -= 0.1 * (gradInp' / obj.hiddenLayerSize);
        end
        
        function y = sigmoid(z)
            % Sigmoid activation function.
            y = 1 ./ (1 + exp(-z));
        end
    end
end

% Example usage:
if true
    % Load MNIST dataset (synthetic data for simplicity)
    X_train = randn(1000, 784);
    t_train = reshape(randi([0, 9], 1000, 1), 1000, 1);
    
    % Create a neural network with 784 inputs, 256 hidden units, and 10 outputs
    net = NeuralNetwork(784, 256, 10);
    
    % Train the neural network for 100 epochs
    for epoch = 1:100
        for i = 1:size(X_train, 1)
            x = X_train(i, :);
            t = t_train(i);
            
            % Forward pass to compute output
            y = net.predict(x);
            
            % Backpropagation and weight update
            net.train(x, t);
        end
        
        % Display the current accuracy
        y = zeros(size(t_train));
        for i = 1:size(X_train, 1)
            x = X_train(i, :);
            y(i) = net.predict(x);
        end
        
        accuracy = mean(y == t_train);
        fprintf('Epoch %d: Accuracy = %.2f%%\n', epoch, accuracy * 100);
    end
end