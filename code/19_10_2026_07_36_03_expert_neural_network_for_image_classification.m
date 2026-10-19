% Neural Network for Image Classification
% Author: [Your Name]

clear; clc;

% Load MNIST dataset (synthetic data)
load('mnist_all.bmp');
load('mnist_train.labels');

% Define constants and hyperparameters
nHidden = 256;
nClasses = 10;
learningRate = 0.001;
momentum = 0.9;
weightDecay = 0.0005;

% Initialize neural network
net = patternnet([32, 64], 'tansig', 'softmax');
net.layers{1}.size = [28 28];
net.layers{end}.transferFcn = 'softmax';

% Set up convolutional layers
conv1 = convlayer('pooling', 'max', [2 2], 'weight_init', 'zeros');
conv2 = convlayer('pooling', 'max', [2 2], 'weight_init', 'ones');

net.addLayer(conv1);
net.addLayer(conv2);

% Set up classification layer
clas = softmaxlayer('size', nClasses, 'transferFcn', 'softmax');
net.addLayer(clas);

% Compile network
net = compile(net);

% Train neural network
[net, tr] = train(net, mnist_train, 10);

% Test neural network
test = test(net, mnist_test);

% Display results
disp('Training Accuracy:');
disp(tr);
disp('Testing Accuracy:');
disp(test);

function [net, tr] = train(net, data, epochs)
    % Set up training options
    opts = trainingOptions('sgdm', 'InitialLearnRate', learningRate, ...
        'MaxEpochs', epochs, 'MiniBatchSize', 128, 'Plots', 'none');

    % Train neural network
    [net, tr] = train(net, data, opts);
end

function test = test(net, data)
    % Set up testing options
    opts = testingOptions('Velocity', 0.9);

    % Test neural network
    test = perform(net, data, opts);
end