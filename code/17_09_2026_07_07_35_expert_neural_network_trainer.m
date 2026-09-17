% Neural Network Trainer (Expert Complexity)
%
% Copyright 2023 Your Name Here
%
% This program trains a neural network to recognize handwritten digits.

% Import necessary packages
import java.io.*;
import java.util.*;

% Load MNIST dataset (synthetic data for this example)
data = load('mnist_data.mat');
trainData = data.trainData;
trainLabels = data.trainLabels;
testData = data.testData;
testLabels = data.testLabels;

% Define the neural network architecture
layers = [...
    sequence(10, 'tanh', 'stateful') % Input layer (28x28 images)
    fullyconnect(64, 'relu') % Hidden layer 1
    fullyconnect(64, 'relu') % Hidden layer 2
    fullyconnect(10, 'softmax') % Output layer (digit recognition)
];

% Define the training options
options = trainingOptions('sgd', ...
    'MaxEpochs', 30, ...
    'InitialLearnRate', 0.01, ...
    'LearnRateSchedule', 'piecewise', ...
    'LearnRateDropFactor', 0.1, ...
    'LearnRateDropPeriod', 10, ...
    'MiniBatchSize', 128, ...
    'ValidationFrequency', 5, ...
    'Verbose', false
);

% Train the neural network
net = trainNetwork(trainData, trainLabels, layers, options);
save('trainedNet.mat', 'net');

% Evaluate the trained neural network on test data
[~, accuracy] = evaluate(net, testData, testLabels);
fprintf('Test accuracy: %f\n', accuracy);

function [accuracy] = evaluate(net, testData, testLabels)
    predictions = predict(net, testData);
    correctPredictions = sum(predictions == testLabels);
    accuracy = mean(correctPredictions) * 100;
end