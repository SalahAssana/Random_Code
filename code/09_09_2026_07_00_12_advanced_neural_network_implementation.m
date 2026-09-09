% Neural Network Implementation

classdef NeuralNetwork < handle
    properties
        layers
        weights
        biases
        activations
        derivatives
    end
    
    methods
        function obj = NeuralNetwork(layers)
            obj.layers = layers;
            obj.weights = cell(size(layers, 2), 1);
            obj.biases = cell(size(layers, 2), 1);
            obj.activations = cell(size(layers, 2), 1);
            obj.derivatives = cell(size(layers, 2), 1);
        end
        
        function [obj, output] = forwardPropagate(obj, input)
            % Initialize the output
            output = zeros(size(input));
            
            % Iterate over each layer
            for i = 1:size(obj.layers, 2) - 1
                % Get the current and next layers
                currLayer = obj.layers{i};
                nextLayer = obj.layers{i + 1};
                
                % Calculate the weighted sum of the inputs
                weightsSum = (obj.weights{i} * input')';
                
                % Add the bias
                biasSum = weightsSum + obj.biases{i};
                
                % Apply the activation function
                output = actFun(biasSum, currLayer);
                
                % Store the output for backpropagation
                obj.derivatives{i} = (nextLayer * output')';
                
                % Update the input for the next layer
                input = output;
            end
            
            % Calculate the final output using the last layer's weights and bias
            output = actFun((obj.weights{end} * input')' + obj.biases{end}, obj.layers{end});
        end
        
        function [obj, error] = backPropagate(obj, input, target)
            % Initialize the error
            error = 0;
            
            % Backpropagate through each layer in reverse order
            for i = size(obj.layers, 2) : -1 : 1
                % Get the current and previous layers
                currLayer = obj.layers{i};
                prevLayer = obj.layers{i - 1};
                
                % Calculate the error gradient
                errorGradient = (target - actFun((obj.weights{i} * input')' + obj.biases{i}, currLayer));
                
                % Update the weights and bias for this layer
                obj.weights{i} = obj.weights{i} - 0.01 * (input' * errorGradient)';
                obj.biases{i} = obj.biases{i} - 0.01 * sum(errorGradient);
                
                % Store the output of this layer
                input = actFun((obj.weights{i} * prevLayer')' + obj.biases{i}, currLayer);
            end
        end
        
        function result = actFun(input, activation)
            if strcmp(activation, 'sigmoid')
                result = 1 ./ (1 + exp(-input));
            elseif strcmp(activation, 'relu')
                result = max(input, 0);
            else
                error('Unknown activation function');
            end
        end
    end
end

% Create a neural network with two hidden layers and one output layer
layers = {{10}, {20}, {1}};
nn = NeuralNetwork(layers);

% Synthesize some data
inputData = rand(1, 10);
targetData = sigmoid(rand(1));

% Train the neural network
for i = 1:1000
    [nn, error] = nn.backPropagate(inputData, targetData);
end

% Test the neural network
output = nn.forwardPropagate(inputData);

% Display the output
disp(output)
```
