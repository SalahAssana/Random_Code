% Convolutional Neural Network for Image Classification
% ADVANCED complexity project

% Import necessary packages
import keras
from keras.models import Sequential
from keras.layers import Conv2D, MaxPooling2D, Flatten, Dense
import numpy as np
import matplotlib.pyplot as plt

% Define synthetic image data
num_classes = 5;
num_samples_per_class = 1000;
image_size = 32;

X_train = np.random.rand(num_samples_per_class * num_classes, image_size, image_size, 1);
Y_train = np.zeros((num_samples_per_class * num_classes, num_classes));
for i = 1:num_classes
    start_idx = (i-1)*num_samples_per_class;
    end_idx = i*num_samples_per_class;
    Y_train(start_idx:end_idx, :) = 1 / num_classes;
end

X_test = np.random.rand(num_samples_per_class * num_classes, image_size, image_size, 1);
Y_test = np.zeros((num_samples_per_class * num_classes, num_classes));
for i = 1:num_classes
    start_idx = (i-1)*num_samples_per_class;
    end_idx = i*num_samples_per_class;
    Y_test(start_idx:end_idx, :) = 1 / num_classes;
end

% Define the neural network model
model = Sequential();
model.add(Conv2D(32, (3, 3), activation='relu', input_shape=[image_size, image_size, 1]));
model.add(MaxPooling2D((2, 2)));
model.add(Flatten());
model.add(Dense(num_classes, activation='softmax'));

% Compile the model
model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy']);

% Train the model
model.fit(X_train, keras.utils.to_categorical(Y_train), epochs=10);

% Evaluate the model on test data
score = model.evaluate(X_test, keras.utils.to_categorical(Y_test));
fprintf('Test loss: %.3f, Test accuracy: %.2f%%\n', score[0], score[1]*100);