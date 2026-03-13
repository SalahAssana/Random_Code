% Neural Network Training
% Copyright (C) 2023 Your Name
%
% This program is free software; you can redistribute it and/or modify it
% under the terms of the GNU General Public License as published by the
% Free Software Foundation; either version 2 of the License, or (at your option)
% any later version.
%
% This program is distributed in the hope that it will be useful, but WITHOUT
% ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
% FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

% Import necessary packages
import matlab.neuralnet;

% Load MNIST dataset
load('mnist.mat');

% Define neural network architecture
hiddenLayerSize = 256;
numEpochs = 10;
miniBatchSize = 128;

% Create neural network
net = patternnet([784, hiddenLayerSize, 10]);

% Set training options
options = trainingOptions(numEpochs, 'InitialLearnRate', 0.01, 'LearnRateSchedule', 'piecewise');

% Train the network
[net, info] = train(net, mnist.images, mnist.labels, options);

% Plot training progress
figure;
plot(info.FitVal);
xlabel('Number of epochs');
ylabel('Training error');
title('Training Error Progress');

% Test the network
testImages = mnist.test.images;
testLabels = mnist.test.labels;

% Evaluate performance on test set
[ypred, ~] = predict(net, testImages);

% Calculate accuracy
accuracy = mean(ypred == testLabels);
fprintf('Test accuracy: %f\n', accuracy);

% Save trained model
save('trained_network.mat', 'net');