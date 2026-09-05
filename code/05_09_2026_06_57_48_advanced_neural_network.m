% Define some constants
LEARNING_RATE = 0.1;
MOMENTUM = 0.9;

classdef NeuralNetwork < handle
    properties
        inputs
        hiddenLayerSize
        outputs
        weightsIH
        weightsHO
        biasesH
        biasesO
        deltaWIO
        deltaWHO
        momentumWIO
        momentumWHO
    end
    
    methods
        function obj = NeuralNetwork(inputs, hiddenLayerSize, outputs)
            obj.inputs = inputs;
            obj.hiddenLayerSize = hiddenLayerSize;
            obj.outputs = outputs;
            
            % Initialize weights and biases with random values
            obj.weightsIH = rand(obj.inputs, obj.hiddenLayerSize);
            obj.weightsHO = rand(obj.hiddenLayerSize, obj.outputs);
            obj.biasesH = zeros(1, obj.hiddenLayerSize);
            obj.biasesO = zeros(1, obj.outputs);
            
            % Initialize momentum for weights updates
            obj.deltaWIO = zeros(size(obj.weightsIH));
            obj.deltaWHO = zeros(size(obj.weightsHO));
            obj.momentumWIO = zeros(size(obj.weightsIH));
            obj.momentumWHO = zeros(size(obj.weightsHO));
        end
        
        function outputs = feedforward(obj, inputs)
            % Calculate hidden layer activations
            hiddenLayerActivations = sigmoid(dot(inputs, obj.weightsIH) + obj.biasesH);
            
            % Calculate output layer activations
            outputs = sigmoid(dot(hiddenLayerActivations, obj.weightsHO) + obj.biasesO);
        end
        
        function [obj, cost] = train(obj, inputs, targets)
            % Forward pass
            hiddenLayerActivations = sigmoid(dot(inputs, obj.weightsIH) + obj.biasesH);
            outputs = sigmoid(dot(hiddenLayerActivations, obj.weightsHO) + obj.biasesO);
            
            % Calculate the error
            deltaO = outputs - targets;
            deltaH = (deltaO * obj.weightsHO') .* sigmoidDerivative(hiddenLayerActivations);
            
            % Update biases and weights using backpropagation and gradient descent
            obj.biasesO = obj.biasesO + LEARNING_RATE * sum(deltaO, 2);
            obj.weightsHO = obj.weightsHO + LEARNING_RATE * hiddenLayerActivations' * deltaO + ...
                MOMENTUM * obj.momentumWHO;
            obj.momentumWHO = MOMENTUM * obj.momentumWHO + (LEARNING_RATE * hiddenLayerActivations' * deltaO);
            
            obj.biasesH = obj.biasesH + LEARNING_RATE * sum(deltaH, 2);
            obj.weightsIH = obj.weightsIH + LEARNING_RATE * inputs' * deltaH + ...
                MOMENTUM * obj.momentumWIO;
            obj.momentumWIO = MOMENTUM * obj.momentumWIO + (LEARNING_RATE * inputs' * deltaH);
            
            % Calculate the cost
            cost = 0.5 * sum(sum((outputs - targets).^2));
        end
    end
end

% Define a sigmoid function and its derivative
function output = sigmoid(input)
    output = 1 / (1 + exp(-input));
end

function output = sigmoidDerivative(input)
    output = input .* (1 - input);
end

% Load MNIST dataset
load mnist_all.mat;

% Create an instance of the neural network with 784 inputs, 256 hidden neurons, and 10 outputs
nn = NeuralNetwork(784, 256, 10);

% Train the neural network for 10000 iterations
for i = 1:10000
    % Get a random training example
    [inputs, targets] = selectRandomExample(trainingImages, trainingLabels);
    
    % Train the neural network on this example
    [nn, cost] = nn.train(inputs, targets);
end

% Use the trained neural network to recognize handwritten digits
recognizedDigits = zeros(size(testingLabels));
for i = 1:size(testingImages, 4)
    outputs = nn.feedforward(testingImages(:, :, :, i));
    [~, recognizedDigit] = max(outputs);
    recognizedDigits(i) = recognizedDigit;
end

% Evaluate the performance of the neural network
accuracy = sum(recognizedDigits == testingLabels) / size(testingImages, 4);
fprintf('Accuracy: %.2f%%\n', accuracy * 100);

function [inputs, targets] = selectRandomExample(images, labels)
    % Randomly select an example from the training set
    idx = randi(size(images, 4));
    inputs = images(:, :, :, idx);
    targets = labels(idx);
end

% Helper function to evaluate the accuracy of the neural network
function accuracy = evaluateAccuracy(nn, testInputs, testTargets)
    recognizedDigits = zeros(size(testTargets));
    for i = 1:size(testInputs, 4)
        outputs = nn.feedforward(testInputs(:, :, :, i));
        [~, recognizedDigit] = max(outputs);
        recognizedDigits(i) = recognizedDigit;
    end
    
    accuracy = sum(recognizedDigits == testTargets) / size(testInputs, 4);
end