% Neural Network Image Classifier
%
% Author: [Your Name]
%
% Description: Train a neural network using synthetic data to classify images based on various features (e.g. shapes, colors), and evaluate its performance using metrics such as accuracy and precision.

% Required Toolboxes: Neural Networks Toolbox, Image Processing Toolbox

% Import necessary toolboxes
import mlr.nn.*;
import mlr.image.*;

% Define the number of classes (shapes) to classify
num_classes = 3;

% Generate synthetic image data
img_data = zeros(1000, 28*28);
label_data = zeros(1, 1000);

for i = 1:1000
    % Randomly select a shape and color
    class_id = randi([1 num_classes]);
    
    % Generate random pixel values for the image
    img = zeros(28, 28);
    for j = 1:28
        for k = 1:28
            if (mod(j + k, 2) == 0)
                img(j,k) = 255;
            end
        end
    end
    
    % Add noise to the image
    img = img + randn(28, 28)*10;
    
    % Normalize pixel values
    img = img / max(max(img));
    
    % Convert the image to a column vector
    img_data(i,:) = reshape(img, 1, 28*28);
    
    % Set the corresponding label
    label_data(i) = class_id;
end

% Split data into training and testing sets
train_idx = randperm(1000);
train_img_data = img_data(train_idx(1:800), :);
train_label_data = label_data(train_idx(1:800));
test_img_data = img_data(train_idx(801:end), :);
test_label_data = label_data(train_idx(801:end));

% Define the neural network architecture
net = patternnet([784 256 128 num_classes]);

% Set the training options
options = trainOptions('max_failures', 10);

% Train the neural network
[net, tr] = train(net, train_img_data, train_label_data, options);

% Evaluate the neural network on the test data
test_err = mean(net.perform(test_img_data, test_label_data));

% Display the results
fprintf('Test error: %0.2f%%\n', 100*test_err);

% Use the trained neural network to classify new images
new_img = reshape(img_data(801,:), 28, 28);
new_class = net(new_img);

% Display the classification result
fprintf('Classified shape: %d\n', new_class);

% Save the trained neural network to a file
save('trained_net.mat', 'net');