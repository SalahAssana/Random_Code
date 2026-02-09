% Neural Network Image Classifier
classdef ImageClassifier
    methods
        function obj = train(input_dir, output_dir)
            % Load pre-trained ResNet50 model
            net = resnet50();
            
            % Convert image data to arrays
            images = imageDatastore(fullfile(input_dir, '*.jpg'));
            labels = readtable(fullfile(output_dir, 'labels.csv'), 'ReadRowNames', false);
            
            % Extract features from input images
            features = activations(net, images, 'pool');
            
            % Define output layers for classification
            classes = unique(labels.Label);
            num_classes = numel(classes);
            output_layer = fullyConnectedLayer(num_classes, ...
                'WeightLearnRateFactor', 10, ...
                'BiasLearnRateFactor', 10);
            output_layer = softmaxLayer;
            output_layer = classificationLayer;
            
            % Combine feature extraction and output layers
            net = seriesnetwork(net.output, output_layer);
            
            % Train the network using image features and labels
            options = trainingOptions('sgdm', 'MiniBatchSize', 64);
            [net, info] = trainNetwork(features, labels.Label, net, options);
        end
        
        function results = classify(input_dir)
            % Load pre-trained ResNet50 model
            net = resnet50();
            
            % Convert image data to arrays
            images = imageDatastore(fullfile(input_dir, '*.jpg'));
            
            % Extract features from input images
            features = activations(net, images, 'pool');
            
            % Classify input images using the trained network
            predictions = predict(net, features);
        end
    end
end

% Main script
if nargin == 0
    output_dir = fullfile(pwd, 'output');
    input_dir = fullfile(pwd, 'input');
    
    classifier = ImageClassifier();
    classifier.train(input_dir, output_dir);
    
    results = classifier.classify(input_dir);
    disp(results);
else
    % Use the provided directories
    output_dir = varargin{1};
    input_dir = varargin{2};
    
    classifier = ImageClassifier();
    classifier.train(input_dir, output_dir);
    
    results = classifier.classify(input_dir);
    disp(results);
end