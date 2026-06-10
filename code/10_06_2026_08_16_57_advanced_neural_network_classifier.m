% Neural Network Classifier
classdef NeuralNetworkClassifier
    methods
        function obj = NeuralNetworkClassifier(inputSize, hiddenLayerSize, outputSize)
            % Constructor for Neural Network Classifier
            obj.inputSize = inputSize;
            obj.hiddenLayerSize = hiddenLayerSize;
            obj.outputSize = outputSize;
            
            % Initialize weights and biases randomly
            obj.weights1 = rand(hiddenLayerSize, inputSize);
            obj.biases1 = zeros(1, hiddenLayerSize);
            obj.weights2 = rand(outputSize, hiddenLayerSize);
            obj.biases2 = zeros(1, outputSize);
        end
        
        function [predictedLabels] = classify(obj, inputs)
            % Classify the given inputs using the neural network
            outputs = sigmoid(dot(inputs, obj.weights1) + obj.biases1);
            outputs = sigmoid(dot(outputs, obj.weights2) + obj.biases2);
            predictedLabels = round( outputs );
        end
        
        function [accuracy] = train(obj, inputs, labels)
            % Train the neural network using the given inputs and labels
            for i = 1:size(inputs, 2)
                input = inputs(:, i);
                label = labels(i);
                
                % Forward propagation
                outputs1 = sigmoid(dot(input, obj.weights1) + obj.biases1);
                outputs2 = sigmoid(dot(outputs1, obj.weights2) + obj.biases2);
                predictedLabel = round( outputs2 );
                
                % Backward propagation
                error2 = (predictedLabel - label) * outputs2 * (1 - outputs2);
                error1 = error2 * outputs1 * (1 - outputs1);
                
                % Update weights and biases
                obj.weights2 = obj.weights2 + 0.1 * error2' * outputs1;
                obj.biases2 = obj.biases2 + 0.1 * error2';
                obj.weights1 = obj.weights1 + 0.1 * error1' * input;
                obj.biases1 = obj.biases1 + 0.1 * error1';
            end
            
            % Calculate accuracy
            correctCount = sum(labels == round( classify(obj, inputs) ));
            accuracy = correctCount / size(inputs, 2);
        end
        
    end
    
end

% Sigmoid function
function output = sigmoid(input)
    output = 1 ./ (1 + exp(-input));
end

% Main script
if nargin == 0
    % Synthetic data for training and testing
    inputs = [randn(100, 2), randn(100, 2) + [1; 1]];
    labels = ones(200, 1);
    labels(101:200) = -1;
    
    % Create a neural network classifier with two input features, one hidden layer with three neurons, and one output neuron
    nn = NeuralNetworkClassifier(2, 3, 1);
    
    % Train the neural network
    nn.train(inputs, labels)
    
    % Test the neural network
    predictedLabels = nn.classify(inputs);
    accuracy = sum(labels == predictedLabels) / size(inputs, 2);
    fprintf('Accuracy: %.2f%%\n', accuracy * 100);
else
    % Example usage with given inputs and labels
    inputs = [1; 0];
    labels = -1;
    nn = NeuralNetworkClassifier(2, 3, 1);
    predictedLabels = nn.classify(inputs);
    fprintf('Predicted label: %d\n', predictedLabels);
end