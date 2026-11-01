% Neural Network for MNIST Dataset

classdef MNIST_NN < handle
    methods
        function obj = MNIST_NN()
            % Load MNIST dataset
            [X_train, y_train], ~ = loadMNIST('training');
            [X_test, y_test] = loadMNIST('testing');

            % Define neural network architecture
            num_inputs = size(X_train, 2);
            num_hidden = 256;
            num_outputs = 10;

            % Initialize weights and biases
            w1 = rand(num_inputs, num_hidden) * 0.01;
            b1 = zeros(1, num_hidden);

            w2 = rand(num_hidden, num_outputs) * 0.01;
            b2 = zeros(1, num_outputs);

            % Train the neural network
            for epoch = 1:10
                for i = 1:size(X_train, 1)
                    x = X_train(i, :);
                    y_true = y_train(i);

                    % Forward pass
                    z1 = x * w1 + b1;
                    a1 = sigmoid(z1);

                    z2 = a1 * w2 + b2;
                    a2 = softmax(z2);

                    % Calculate loss
                    loss = mean((a2 - y_true) .^ 2);

                    % Backward pass
                    dz2 = (a2 - y_true);
                    dw2 = mean(a1 .* dz2, 1);
                    db2 = mean(dz2, 1);

                    dz1 = w2' * dz2;
                    dw1 = mean(x .* dz1, 1);
                    db1 = mean(dz1, 1);

                    % Update weights and biases
                    w1 = w1 - 0.01 * dw1;
                    b1 = b1 - 0.01 * db1;

                    w2 = w2 - 0.01 * dw2;
                    b2 = b2 - 0.01 * db2;
                end

                % Evaluate the neural network on the test set
                accuracy = evaluate(X_test, y_test, w1, w2, b1, b2);
                disp(['Epoch ', num2str(epoch), ': Accuracy = ', num2str(accuracy)]);
            end
        end

        function accuracy = evaluate(X, y, w1, w2, b1, b2)
            correct = 0;

            for i = 1:size(X, 1)
                x = X(i, :);
                y_true = y(i);

                % Forward pass
                z1 = x * w1 + b1;
                a1 = sigmoid(z1);

                z2 = a1 * w2 + b2;
                a2 = softmax(z2);

                [~, idx] = max(a2);
                y_pred = idx;

                if y_true == y_pred
                    correct = correct + 1;
                end
            end

            accuracy = correct / size(X, 1);
        end

        function s = sigmoid(x)
            s = 1 ./ (1 + exp(-x));
        end

        function s = softmax(x)
            s = exp(x) ./ sum(exp(x), 2);
        end
    end
end

function [X_train, y_train], X_test = loadMNIST(type)
    switch type
        case 'training'
            filename = 'mnist_train.mat';
        case 'testing'
            filename = 'mnist_test.mat';
        otherwise
            error('Invalid type');
    end

    load(filename);
    X_train = X;
    y_train = y;

    % Normalize the data
    X_train = X_train ./ 255;