% Neural Network for Classification
% Script to train and test a neural network on synthetic data to classify handwritten digits (MNIST dataset) and visualize the results using a confusion matrix.

% Define necessary imports
import mlr;
import mlrx;

% Load MNIST dataset
[~, ~, X_train, y_train, ~, ~, X_test, y_test] = loadmnist();

% Reshape data for neural network
X_train = reshape(X_train, size(X_train, 1), size(X_train, 2), 1);
X_test = reshape(X_test, size(X_test, 1), size(X_test, 2), 1);

% Define neural network architecture
nnet = newmlp([784 128 10], 'tansig', 'logsig');

% Set training options
opt = newoptions('maxepochs', 1000);
opt.learngd = 0.01;
opt.momentum = 0.1;

% Train neural network
[nnet, y_fit] = train(nnet, X_train, y_train, opt);

% Evaluate performance on test set
[ypred, ~] = sim(nnet, X_test);
y_pred_class = class(y_pred);

% Calculate confusion matrix
conf_mat = confusionmat(y_test, y_pred_class);

% Display results
fprintf('Confusion Matrix:\n');
disp(conf_mat);

% Plot misclassification rate over time
misclass_rate = sum(ypred ~= y_test) / size(X_test, 1);
figure;
plot(misclass_rate);
xlabel('Epochs');
ylabel('Misclassification Rate');

% End script