% Neural Network Training - ADVANCED
%

classdef NeuralNetwork < handle
    properties
        layers
        weights
        biases
        activations
    end
    
    methods
        function obj = NeuralNetwork(layers)
            obj.layers = layers;
            obj.weights = cell(1, length(layers) - 1);
            obj.biases = cell(1, length(layers) - 1);
            obj.activations = cell(1, length(layers));
        end
        
        function y = feedforward(obj, x)
            for i = 1:length(obj.layers) - 1
                z = obj.weights{i} * x + obj.biases{i};
                x = sigmoid(z);
            end
            y = x;
        end
        
        function [dW, dB] = backpropagation(obj, x, t, learning_rate)
            % Forward pass
            h = feedforward(obj, x);
            
            % Error calculation
            delta = t - h;
            for i = length(obj.layers) - 1:-1:1
                if i == length(obj.layers) - 1
                    delta = delta .* obj.activations{i+1};
                else
                    z = obj.weights{i} * h + obj.biases{i};
                    delta = sigmoidDerivative(z) .* delta;
                end
                
                % Backpropagation
                dW{i} = h' * delta;
                dB{i} = mean(delta);
                
                % Weight update
                obj.weights{i} = obj.weights{i} - learning_rate * dW{i};
                obj.biases{i} = obj.biases{i} - learning_rate * dB{i};
                
                % Activation update
                obj.activations{i+1} = sigmoid(obj.weights{i} * h + obj.biases{i});
            end
        end
        
        function plot(obj)
            for i = 1:length(obj.layers) - 1
                figure;
                plot3(1:10, 1:10, obj.weights{i}(1:end), 'LineWidth', 2);
                title(['Weight Layer ' num2str(i)]);
            end
        end
    end
end

% Activation functions
function y = sigmoid(x)
    y = 1 ./ (1 + exp(-x));
end

function y = sigmoidDerivative(x)
    y = x .* (1 - x);
end

% Synthetic data generation
num_samples = 1000;
num_features = 10;

X = rand(num_samples, num_features);
Y = X * [1; 2] + 3;

% Neural network configuration
layers = {[5], [10], [10], [1]};
network = NeuralNetwork(layers);

% Training loop
learning_rate = 0.01;
num_iterations = 10000;

for i = 1:num_iterations
    for j = 1:size(X, 1)
        [dW, dB] = network.backpropagation(X(j, :), Y(j));
        for k = 1:length(layers) - 1
            network.weights{k} = dW{k};
            network.biases{k} = dB{k};
        end
    end
end

% Plotting the weights
network.plot();