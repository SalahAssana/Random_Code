% Neural Network Trainer
classdef NeuralNetworkTrainer
    methods
        function obj = NeuralNetworkTrainer()
            % Initialize neural network parameters
            numLayers = 3;
            hiddenLayerSizes = [256, 128];
            outputLayerSize = 10;
            learningRate = 0.01;
            numEpochs = 100;
            
            % Generate synthetic data (MNIST dataset)
            [X_train, y_train] = generateSyntheticData();
            [X_test, y_test] = generateSyntheticData('test');
            
            % Initialize neural network
            net = feedforwardnet(numLayers);
            net.layers{1}.size = hiddenLayerSizes(1);
            net.layers{2}.size = hiddenLayerSizes(2);
            net.layers{end}.size = outputLayerSize;
            net.learngd = learningRate;
            
            % Train neural network
            [X_train, y_train] = prepareData(X_train, y_train);
            net = train(net, X_train, y_train, numEpochs);
            
            % Evaluate neural network performance
            [X_test, y_test] = prepareData(X_test, y_test);
            y_pred = predict(net, X_test);
            accuracy = mean(double(y_pred == y_test)) * 100;
            fprintf('Neural Network Accuracy: %.2f%%\n', accuracy);
        end
        
        function [X, y] = generateSyntheticData(mode)
            % Generate synthetic data (MNIST dataset)
            if nargin < 1 || isempty(mode) || strcmpi(mode, 'train')
                X = rand(78400, 28*28); % 5000 images of size 28x28
                y = categorical(randperm(10, 78400));
            elseif strcmpi(mode, 'test')
                X = rand(2000, 28*28); % 2000 images of size 28x28
                y = categorical(randperm(10, 2000));
            end
        end
        
        function [X, y] = prepareData(X, y)
            % Prepare data for training (normalize and convert to doubles)
            X = X ./ max(X(:)); % Normalize pixel values
            y = double(y);
        end
        
        function y_pred = predict(net, X)
            % Predict output using trained neural network
            y_pred = net(X);
        end
    end
end

% Main script
if nargin == 0 || ~exist('NeuralNetworkTrainer', 'class')
    obj = NeuralNetworkTrainer();
end