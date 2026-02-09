% Neural Network Implementation in MATLAB

% Import necessary libraries
import mlr.nn.*;

% Define constants
INPUT_LAYER = 784;
HIDDEN_LAYER1 = 256;
HIDDEN_LAYER2 = 128;
OUTPUT_LAYER = 10;

% Load MNIST dataset
[training_set, training_labels] = loadMNIST('training');
[test_set, test_labels] = loadMNIST('testing');

% Normalize data
training_set = normalize(training_set);
test_set = normalize(test_set);

% Create neural network
net = initNetwork(INPUT_LAYER, HIDDEN_LAYER1, HIDDEN_LAYER2, OUTPUT_LAYER);

% Train the network using backpropagation
train(net, training_set, training_labels);

% Test the network
outputs = test(net, test_set);

% Print accuracy
accuracy = sum(diag(outputs)) / size(test_labels, 1);
fprintf('Accuracy: %f\n', accuracy);

function [net] = initNetwork(inputLayer, hiddenLayer1, hiddenLayer2, outputLayer)
    net = feedforwardnet([inputLayer, hiddenLayer1, hiddenLayer2, outputLayer]);
end

function [outputs] = test(net, inputs)
    outputs = sim(net, inputs);
end

function [accuracy] = calculateAccuracy(outputs, labels)
    accuracy = sum(diag(outputs)) / size(labels, 1);
end

function [training_set, training_labels] = loadMNIST(type)
    % Load MNIST dataset from file
    if strcmpi(type, 'training')
        filename = 'mnist_train.csv';
    elseif strcmpi(type, 'testing')
        filename = 'mnist_test.csv';
    else
        error('Invalid type');
    end
    
    data = readtable(filename);
    
    % Convert data to numerical values
    training_set = double(data(:, 2:end));
    training_labels = categorical(data(:, 1));
end

function [data] = normalize(data)
    min_values = min(data, [], 2);
    max_values = max(data, [], 2);
    
    normalized_data = (data - min_values) ./ (max_values - min_values);
    
    data = normalized_data;
end