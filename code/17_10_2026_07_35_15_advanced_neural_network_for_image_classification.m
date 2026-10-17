% Neural Network for Image Classification
classdef CatDogClassifier
    properties
        net
        trainImages
        testImages
    end
    
    methods
        function obj = CatDogClassifier()
            % Load training and testing images
            [obj.trainImages, ~] = imread('train/*.jpg');
            [obj.testImages, ~] = imread('test/*.jpg');
            
            % Define neural network architecture
            layers = [
                imageInputLayer([28 28 1], 'Normalization', 'none')
                convolution2dLayer(3, 10, 'Padding', 'same')
                maxPooling2dLayer(2, 2)
                reluLayer
                fullyConnectedLayer(128)
                dropoutLayer(0.5)
                fullyConnectedLayer(2)
                softmaxLayer
                classificationLayer('Classes', ['cat'; 'dog'])
            ];
            
            % Define options for training
            options = trainingOptions('sgd', ...
                'MaxEpochs', 10, ...
                'InitialLearnRate', 0.01, ...
                'MiniBatchSize', 64);
            
            % Train the network
            obj.net = trainNetwork(obj.trainImages, layers, options);
        end
        
        function classify = classifyImage(obj, image)
            % Preprocess the image
            image = imresize(image, [28 28]);
            image = permute(image, [3 1 2]);
            
            % Classify the image
            classification = predict(obj.net, reshape(image, [1 1 28 28]));
            classify = strcmp(classification, 'dog');
        end
    end
end

% Main script
if nargin == 0
    obj = CatDogClassifier();
    
    % Test the classifier
    for i = 1:size(obj.testImages, 4)
        image = obj.testImages(:,:,:,i);
        classify = obj.classifyImage(image);
        fprintf('Image %d: %s\n', i, classify);
    end
end