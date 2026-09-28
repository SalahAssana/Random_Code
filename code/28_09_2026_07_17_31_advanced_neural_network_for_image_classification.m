% Neural Network for Image Classification

% Import necessary libraries
import mlcv.*;

% Load CIFAR-10 dataset
[images, labels] = loadCIFAR10();

% Split data into training and testing sets
[train_images, train_labels, test_images, test_labels] = splitData(images, labels);

% Define neural network architecture
net = setupNetwork();

% Train the network using stochastic gradient descent
trainNet(net, train_images, train_labels);

% Test the network on the test set
accuracy = testNet(net, test_images, test_labels);

% Display the accuracy
fprintf('Accuracy: %.2f%%\n', accuracy*100)

% Helper functions
function [train_images, train_labels, test_images, test_labels] = splitData(images, labels)
    % Split data into training and testing sets (80% for training, 20% for testing)
    idx = randperm(size(images, 4));
    train_idx = idx(1:round(0.8*size(images, 4)));
    test_idx = setdiff(1:size(images, 4), train_idx);
    
    train_images = images(:,:,:,train_idx);
    train_labels = labels(train_idx);
    test_images = images(:,:,:,test_idx);
    test_labels = labels(test_idx);
end

function net = setupNetwork()
    % Define the network architecture
    layers = [
        imageInputLayer([32 32 3], 'Normalization', 'zerocenter')
        convolution2dLayer(3, 6, 'Padding', 'same', 'Stride', 1)
        batchNormalizationLayer
        reluLayer
        maxPooling2dLayer(2, 'Stride', 2)
        
        convolution2dLayer(3, 12, 'Padding', 'same', 'Stride', 1)
        batchNormalizationLayer
        reluLayer
        maxPooling2dLayer(2, 'Stride', 2)
        
        flattenLayer
        fullyConnectedLayer(10)
        softmaxLayer
    ];
    
    net = convolutionalNetwork(layers);
end

function accuracy = trainNet(net, images, labels)
    % Train the network using stochastic gradient descent
    options = trainingOptions('sgd', 'MaxEpochs', 10);
    [net, info] = train(net, images(:,:,:,1:end), labels(1:end), options);
    
    accuracy = info.ValidationAccuracy(end);
end

function accuracy = testNet(net, images, labels)
    % Test the network on the test set
    predictions = classify(net, images(:,:,:,1:end));
    accuracy = mean(labels(:) == predictions(:));
end

% Load CIFAR-10 dataset function
function [images, labels] = loadCIFAR10()
    % Load pre-trained model
    url = 'https://www.cs.toronto.edu/~kriz/cifar-10-cnn-batchnorm.mat';
    data = load(url);
    
    % Extract images and labels
    images = data.images;
    labels = categorical(data.labels);
end