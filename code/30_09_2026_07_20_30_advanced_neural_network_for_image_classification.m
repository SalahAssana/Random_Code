% Neural Network for Image Classification
% ADVANCED Complexity Project

% Import necessary libraries
import java.util.Arrays;
import java.lang.Math;

class ImageClassifier {
    % Define the number of classes
    numClasses = 10;

    % Define the convolutional neural network architecture
    layers = [...
        layerConstruction('conv2d', 32, [3 3], 'relu', 'same');
        layerConstruction('maxPooling2d', [2 2], 'same');
        layerConstruction('conv2d', 64, [3 3], 'relu', 'same');
        layerConstruction('maxPooling2d', [2 2], 'same');
        layerConstruction('flatten');
        layerConstruction('dense', numClasses, 'softmax')
    ];

    % Define the loss function and optimizer
    lossFunction = @crossEntropyLoss;
    optimizer = @adamOptimizer;

    % Train the neural network
    function train(model, X_train, y_train)
        epochs = 10;
        batchSize = 32;

        for epoch = 1:epochs
            idx = randperm(size(X_train, 2));
            for i = 1:batchSize:size(idx, 2), batchEnd = min(i + batchSize - 1, size(idx, 2)); 
                X_batch = X_train(:, idx(i : batchEnd));
                y_batch = y_train(idx(i : batchEnd));

                % Forward pass
                outputs = model.predict(X_batch);

                % Calculate the loss
                loss = lossFunction(outputs, y_batch);

                % Backward pass
                gradOutputs = gradients(loss, y_batch);
                gradWeights = gradients(model.weights, gradOutputs);

                % Update the weights using the optimizer
                model.weights = optimizer(model.weights, gradWeights);

                % Display the training progress
                fprintf('Epoch %d: Loss = %.2f\n', epoch, loss);
            end
        end
    end

    % Predict the labels for a given input
    function predictedLabels = predict(model, X_test)
        outputs = model.predict(X_test);
        [maxVals, indices] = max(outputs, [], 2);
        predictedLabels = indices;
    end

    % Define the layer construction function
    function layer = layerConstruction(type, numFilters, filterSize, activation, padding)
        switch type
            case 'conv2d'
                layer = Conv2DLayer(numFilters, filterSize, activation, padding);
            case 'maxPooling2d'
                layer = MaxPooling2DLayer(filterSize, padding);
            case 'flatten'
                layer = FlattenLayer();
            case 'dense'
                layer = DenseLayer(numFilters, activation);
        end
    end

    % Define the cross entropy loss function
    function loss = crossEntropyLoss(outputs, labels)
        loss = -mean(labels .* log(outputs) + (1 - labels) .* log(1 - outputs));
    end

    % Define the gradients of the loss with respect to the weights
    function gradWeights = gradients(weights, gradOutputs)
        gradWeights = gradOutputs .* weights;
    end

    % Define the Adam optimizer
    function weights = adamOptimizer(weights, gradWeights, learningRate, beta1, beta2)
        weights = weights - learningRate * gradWeights;
        return weights;
    end
end

% Main script
if nargin < 4 || nargin > 5
    error('Invalid number of input arguments');
end

% Load the synthetic dataset
[images, labels] = loadSyntheticDataset();

% Split the data into training and testing sets
[trainImages, testImages, trainLabels, testLabels] = splitData(images, labels);

% Create an instance of the image classifier model
model = ImageClassifier();

% Train the model using the training data
model.train(trainImages, trainLabels);

% Make predictions on the testing data
predictedLabels = model.predict(testImages);

% Display the accuracy of the model
accuracy = mean(predictedLabels == testLabels);
fprintf('Accuracy: %.2f%%\n', accuracy * 100);
```
