% Neural Network Trainer
%
% This is an expert-level MATLAB script that trains a neural network on a dataset 
% and evaluates its performance using metrics like accuracy and F1 score.

% Import necessary libraries
import ml;
import statistics;

% Define the dataset (synthetic)
X_train = rand(1000, 10);
y_train = mod(randi([0, 9], 1000, 1), 2);
X_test = rand(500, 10);
y_test = mod(randi([0, 9], 500, 1), 2);

% Define the neural network architecture
layers = [ ...
    sequenceInputLayer(10, 'Name', 'input_layer') ... 
    fullyConnectedLayer(64, 'Name', 'hidden_layer_1') ... 
    reluLayer('Name', 'relu_activation') ... 
    dropoutLayer(0.2) ... 
    fullyConnectedLayer(2, 'Name', 'output_layer') ... 
    softmaxLayer('Name', 'softmax_output') ... 
    classificationLayer('Classes', 2, 'Name', 'classification_layer')
];

% Define the options for training
options = trainingOptions('adam', ...
    'MaxEpochs', 10, ...
    'MiniBatchSize', 128, ...
    'GradientThreshold', 1.0, ...
    'SquaredGradientTolerance', 1e-8, ...
    'ValidationPatience', Inf, ...
    'Plots', 'none'
);

% Train the neural network
net = trainNetwork(X_train, y_train, layers, options);
net.save('nn_model.mat');

% Evaluate the trained model on the test set
[ypred, score] = classify(net, X_test);
accuracy = sum(ypred == y_test) / numel(y_test);

% Calculate the F1 score for each class
f1_scores = zeros(2, 1);
for i = 1:2
    TP = sum((ypred(:) == i) & (y_test(:) == i));
    FP = sum((ypred(:) ~= i) & (y_test(:) == i));
    FN = sum((ypred(:) ~= i) & (y_test(:) == i));
    precision = TP / (TP + FP);
    recall = TP / (TP + FN);
    f1_scores(i, 1) = (2 * precision * recall) / (precision + recall);
end

% Display the results
fprintf('Accuracy: %.4f\n', accuracy);
fprintf('F1 score for class 0: %.4f\n', f1_scores(1));
fprintf('F1 score for class 1: %.4f\n', f1_scores(2));

% Load and evaluate the pre-trained model
load('nn_model.mat');
ypred = classify(net, X_test);
accuracy = sum(ypred == y_test) / numel(y_test);
fprintf('Pre-trained model accuracy: %.4f\n', accuracy);

% Calculate the F1 score for each class using the pre-trained model
for i = 1:2
    TP = sum((ypred(:) == i) & (y_test(:) == i));
    FP = sum((ypred(:) ~= i) & (y_test(:) == i));
    FN = sum((ypred(:) ~= i) & (y_test(:) == i));
    precision = TP / (TP + FP);
    recall = TP / (TP + FN);
    f1_scores(i, 1) = (2 * precision * recall) / (precision + recall);
end

fprintf('Pre-trained model F1 score for class 0: %.4f\n', f1_scores(1));
fprintf('Pre-trained model F1 score for class 1: %.4f\n', f1_scores(2));

% Evaluate the pre-trained model using cross-validation
cvpartition = cvpartition(y_test, 'KFold', 5);
ypred_cv = zeros(numel(y_test), 1);

for i = 1:cvpartition.NumTestSets
    test_idx = cvpartition.TestSet{i};
    X_test_fold = X_test(test_idx, :);
    y_test_fold = y_test(test_idx);
    [ypred_fold, score] = classify(net, X_test_fold);
    ypred_cv(test_idx) = ypred_fold;
end

accuracy_cv = sum(ypred_cv == y_test) / numel(y_test);
fprintf('Pre-trained model cross-validation accuracy: %.4f\n', accuracy_cv);

% Calculate the F1 score for each class using cross-validation
for i = 1:2
    TP = sum((ypred_cv(:) == i) & (y_test(:) == i));
    FP = sum((ypred_cv(:) ~= i) & (y_test(:) == i));
    FN = sum((ypred_cv(:) ~= i) & (y_test(:) == i));
    precision = TP / (TP + FP);
    recall = TP / (TP + FN);
    f1_scores(i, 1) = (2 * precision * recall) / (precision + recall);
end

fprintf('Pre-trained model cross-validation F1 score for class 0: %.4f\n', f1_scores(1));
fprintf('Pre-trained model cross-validation F1 score for class 1: %.4f\n', f1_scores(2));