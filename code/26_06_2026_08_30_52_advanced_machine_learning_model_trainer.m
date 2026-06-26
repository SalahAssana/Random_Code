% Machine Learning Model Trainer
% Copyright (c) 2023 Your Name

classdef ModelTrainer < handle
    methods
        function obj = ModelTrainer(data_size)
            % Initialize model trainer with synthetic data of given size
            if nargin < 1
                error('No input data size provided');
            end
            
            % Generate synthetic data (X, y) for training
            X = rand(data_size, 10); % features
            y = sin(X(:, 1)) + 0.5 * cos(X(:, 2)) + 0.3 * sin(X(:, 3)); % labels
            
            % Split data into training and testing sets (70% train, 30% test)
            [X_train, X_test, y_train, y_test] = split_data(X, y, 0.7);
            
            % Define models to train
            models = {
                @linear_regression;
                @decision_tree;
                @random_forest;
                @support_vector_machine;
                @neural_network
            };
            
            % Train and evaluate each model
            for i = 1:length(models)
                model = models{i};
                [trained_model, train_loss] = train_model(model, X_train, y_train);
                test_loss = evaluate_model(trained_model, X_test, y_test);
                fprintf('Model %s: Train loss %.4f, Test loss %.4f\n', ...
                    func2str(models{i}), train_loss, test_loss);
            end
        end
        
        function [X_train, X_test, y_train, y_test] = split_data(X, y, ratio)
            % Split data into training and testing sets based on given ratio
            n_samples = size(X, 1);
            idx = randperm(n_samples);
            train_idx = idx(1:round(ratio*n_samples));
            test_idx = idx(round(ratio*n_samples)+1:end);
            
            X_train = X(train_idx, :);
            X_test = X(test_idx, :);
            y_train = y(train_idx);
            y_test = y(test_idx);
        end
        
        function [trained_model, train_loss] = train_model(model, X, y)
            % Train a machine learning model using the given data
            trained_model = model(X, y);
            train_loss = mean((y - feval(@model, X, trained_model)) .^ 2);
        end
        
        function test_loss = evaluate_model(model, X, y)
            % Evaluate the performance of a trained model on new data
            test_loss = mean((y - feval(@model, X, model)) .^ 2);
        end
    end
    
    methods (Access = private)
        function output = linear_regression(X, y)
            % Linear Regression Model
            beta0 = mean(y) / mean(ones(size(y,1),1));
            beta1 = (mean((X - mean(X)).*(y - beta0)))/...
                mean((X - mean(X)).^2);
            output = @(x) beta0 + beta1*x;
        end
        
        function output = decision_tree(X, y)
            % Decision Tree Model
            output = fitrtree(X, y, 'Method', 'classification');
        end
        
        function output = random_forest(X, y)
            % Random Forest Model
            output = fitrensemble(X, y, 'Method', 'bagging', 'NumTrees', 100);
        end
        
        function output = support_vector_machine(X, y)
            % Support Vector Machine Model
            output = fitcsvm(X, y, 'KernelFunction', 'rbf', 'OptimizeHyperparameters', true);
        end
        
        function output = neural_network(X, y)
            % Neural Network Model
            net = patternnet([size(X,2), 10, 1]);
            net.layers{2}.transferFcn = 'tansig';
            net.trainFcn = 'traingdx';
            [~,yhat] = net(X,y);
            output = @(x) yhat;
        end
    end
end

% Run the model trainer on synthetic data with size 1000
trainer = ModelTrainer(1000);