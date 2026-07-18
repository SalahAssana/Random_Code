% Neural Network Trainer
% Author: [Your Name]

classdef NeuralNetworkTrainer < handle
    properties
        % Hyperparameters
        learningRate = 0.01;
        momentum = 0.9;
        hiddenLayerSize = 256;
        outputLayerSize = 10;
        
        % Weights and biases
        weights1 = rand([784, hiddenLayerSize]);
        weights2 = rand([hiddenLayerSize, outputLayerSize]);
        bias1 = zeros(1, hiddenLayerSize);
        bias2 = zeros(1, outputLayerSize);
    end
    
    methods
        function obj = NeuralNetworkTrainer()
            % Initialize neural network layers
            obj.layers = {layer(obj.hiddenLayerSize), layer(obj.outputLayerSize)};
        end
        
        function [weights, bias] = forwardPropagate(obj, inputs)
            % Forward propagate through the neural network
            hiddenLayer = sigmoid(dot(inputs, obj.weights1) + obj.bias1);
            outputLayer = sigmoid(dot(hiddenLayer, obj.weights2) + obj.bias2);
            [weights, bias] = deal(obj.weights2, obj.bias2);
        end
        
        function train(obj, inputs, targets)
            % Train the neural network using backpropagation and gradient descent
            for i = 1:length(inputs)
                inputsSingle = inputs(i,:);
                targetsSingle = targets(i,:);
                
                % Forward propagation
                [hiddenLayer, outputLayer] = forwardPropagate(obj, inputsSingle);
                
                % Backward propagation
                error = targetsSingle - outputLayer;
                delta2 = error .* sigmoidDerivative(outputLayer);
                hiddenError = delta2 * obj.weights2';
                delta1 = hiddenError .* sigmoidDerivative(hiddenLayer);
                
                % Weight updates
                obj.weights2 = obj.weights2 + obj.learningRate * dot(hiddenLayer', delta2) + obj.momentum * obj.weights2;
                obj.bias2 = obj.bias2 + obj.learningRate * mean(delta2) + obj.momentum * obj.bias2;
                obj.weights1 = obj.weights1 + obj.learningRate * dot(inputsSingle', delta1) + obj.momentum * obj.weights1;
                obj.bias1 = obj.bias1 + obj.learningRate * mean(delta1) + obj.momentum * obj.bias1;
            end
        end
        
        function plot(obj)
            % Plot the neural network's performance
            x = -6:0.1:6;
            y = sigmoid(dot(x', obj.weights1) + obj.bias1);
            plot(x, y);
        end
    end
end

classdef layer < handle
    properties
        size
    end
    
    methods
        function this = layer(size)
            this.size = size;
        end
        
        function output = sigmoid(this, input)
            % Sigmoid activation function
            output = 1 ./ (1 + exp(-input));
        end
        
        function derivative = sigmoidDerivative(this, input)
            % Derivative of the sigmoid activation function
            derivative = input .* (1 - input);
        end
    end
end

% Test the neural network trainer
trainer = NeuralNetworkTrainer();
trainer.train(rand(10, 784), rand(10, 10));
trainer.plot();