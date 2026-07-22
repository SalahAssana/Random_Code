% Machine Learning Model Training and Evaluation in MATLAB
%
% Copyright 2023 [Your Name]

classdef MLModel
    properties
        X_train
        y_train
        X_test
        y_test
    end
    
    methods
        function obj = train(X_train, y_train)
            % Train the model using logistic regression algorithm
            obj.X_train = X_train;
            obj.y_train = y_train;
            
            % Define the logistic regression parameters
            alpha = 0.01;
            max_iter = 1000;
            theta = zeros(size(y_train, 2), 1);
            J_history = zeros(max_iter, 1);
            
            for i = 1:max_iter
                % Compute the gradients of the cost function
                grad = (1/size(X_train, 1)) * X_train * (logistic(obj.X_train*theta) - y_train');
                
                % Update the parameters using gradient descent
                theta = theta - alpha * grad;
                
                % Store the cost function value at each iteration
                J_history(i) = compute_cost(obj.X_train, obj.y_train, theta);
            end
            
            % Set the trained model parameters
            obj.theta = theta;
        end
        
        function y_pred = predict(obj, X_test)
            % Make predictions using the trained model
            y_pred = logistic(X_test*obj.theta);
        end
    end
    
end

function J = compute_cost(X_train, y_train, theta)
    % Compute the cost function value for a given set of parameters
    J = (1/size(X_train, 1)) * sum((logistic(X_train*theta) - y_train).^2);
end

function y = logistic(x)
    % Compute the sigmoid function for a given input
    y = 1 ./ (1 + exp(-x));
end

% Create synthetic data for training and testing
X_train = rand(1000, 10);
y_train = round(rand(1000, 1) > 0.5);

X_test = rand(500, 10);
y_test = round(rand(500, 1) > 0.5);

% Train the model
model = MLModel();
model.train(X_train, y_train);

% Make predictions on the test set
y_pred = model.predict(X_test);

% Evaluate the model's performance using accuracy and precision metrics
accuracy = sum(y_pred == y_test)/size(y_test, 1);
precision = sum(y_pred(y_test == 1) == 1)/sum(y_test == 1);

fprintf('Accuracy: %.2f%%\n', accuracy*100);
fprintf('Precision: %.2f%%\n', precision*100);