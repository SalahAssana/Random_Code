% Time Series Prediction Model - Intermediate Level

% Import necessary libraries
import mlr.*

% Define constants
PREDICTION_LENGTH = 10; % Number of future predictions to make
TRAINING_SET_SIZE = 0.8; % Percentage of the data used for training
TEST_SET_SIZE = 1 - TRAINING_SET_SIZE;

% Load synthetic time series data (replace with your own data)
data = load('stock_prices.mat');
series = data.series;

% Split data into training and testing sets
trainSetSize = size(series, 1) * TRAINING_SET_SIZE;
testSetSize = size(series, 1) - trainSetSize;
trainSeries = series(1:floor(trainSetSize), :);
testSeries = series(floor(trainSetSize)+1:end, :);

% Preprocess data by normalizing the values
maxVal = max(trainSeries);
minVal = min(trainSeries);
normTrainSeries = (trainSeries - minVal) / (maxVal - minVal);
normTestSeries = (testSeries - minVal) / (maxVal - minVal);

% Create a neural network with one hidden layer
hiddenLayerSize = 20;
net = feedforwardnet(hiddenLayerSize);
net.layers{1}.transferFcn = 'tansig';
net.trainFcn = 'trainlm';

% Train the neural network using the training data
[net, tr] = train(net, normTrainSeries);

% Make predictions on the testing data
predictions = predict(net, normTestSeries);

% De-normalize the predictions and convert them to original scale
maxVal = maxVal;
minVal = minVal;
normPredictions = (predictions * (maxVal - minVal)) + minVal;

% Plot the actual and predicted values
plot(testSeries, 'b');
hold on;
plot(normToOriginal(normalize_to_original(normTestSeries)), 'r');
hold off;

% Define a function to normalize data
function normData = normalize_to_original(data)
    maxVal = max(data);
    minVal = min(data);
    normData = (data - minVal) / (maxVal - minVal);
end

% Define a function to denormalize data
function originalData = normToOriginal(normalizedData)
    maxVal = max(normalizedData);
    minVal = min(normalizedData);
    originalData = (normalizedData * (maxVal - minVal)) + minVal;