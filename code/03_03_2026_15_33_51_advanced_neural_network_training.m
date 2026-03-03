% Neural Network Training - Advanced Complexity Project

classdef NeuralNetwork < handle
    properties
        layers
        weights
        biases
        activations
        outputs
    end
    
    methods
        function obj = NeuralNetwork(numInputs, numHidden, numOutputs)
            % Initialize neural network with specified number of inputs, hidden units and outputs
            obj.layers = struct('type', 'input', 'numUnits', numInputs);
            for i = 1:numHidden
                obj.layers(end + 1) = struct('type', 'hidden', 'numUnits', 1);
            end
            obj.layers(end + 1) = struct('type', 'output', 'numUnits', numOutputs);
            obj.weights = cell(numel(obj.layers), 1);
            obj.biases = cell(numel(obj.layers), 1);
            obj.activations = cell(numel(obj.layers), 1);
        end
        
        function predict(obj, input)
            % Forward pass to compute output
            obj.outputs = {};
            for i = 1:numel(obj.layers) - 1
                if strcmp(obj.layers(i).type, 'input')
                    obj.outputs{i} = input;
                elseif strcmp(obj.layers(i).type, 'hidden') || strcmp(obj.layers(i).type, 'output')
                    z = obj.weights{i} * obj.outputs{i} + obj.biases{i};
                    obj.outputs{i+1} = obj.activations{end}(z);
                end
            end
        end
        
        function train(obj, inputs, targets)
            % Train the neural network using forward and backward pass
            for i = 1:numel(inputs)
                obj.predict(inputs{i});
                errors = targets{i} - obj.outputs{end};
                for j = numel(obj.layers) - 2:-1:1
                    if strcmp(obj.layers(j).type, 'hidden') || strcmp(obj.layers(j).type, 'output')
                        deltas = obj.activations{end}(errors .* ...
                            (1 .- obj.activations{end}(obj.outputs{j+1})));
                        obj.weights{j+1} = obj.weights{j+1} + 0.1 * ...
                            (deltas * obj.outputs{j}');
                        obj.biases{j+1} = obj.biases{j+1} + 0.1 * deltas;
                    end
                end
            end
        end
    end
end

% Synthetic data generation for demonstration purposes
numExamples = 1000;
inputSize = 784;
hiddenSize = 256;
outputSize = 10;

X_train = rand(inputSize, numExamples);
y_train = round(rand(outputSize, numExamples));

nn = NeuralNetwork(inputSize, hiddenSize, outputSize);

% Train the neural network
for i = 1:numExamples
    nn.train(X_train(:,i), y_train(:,i));
end

% Evaluate the trained neural network on a test set (optional)
X_test = rand(inputSize, 100);
y_pred = cell(size(y_train));
for i = 1:100
    nn.predict(X_test(:,i));
    y_pred{i} = round(obj.outputs{end});
end