% Neural Network-based Image Classification
%
% This script demonstrates an expert-level image classification program using convolutional neural networks (CNNs) and backpropagation.

% Import necessary libraries
import tensorflow.keras as keras
from tensorflow.keras.preprocessing.image import ImageDataGenerator
import numpy as np

% Define the model architecture
model = keras.Sequential([
    keras.layers.Conv2D(32, (3, 3), activation='relu', input_shape=(224, 224, 3)),
    keras.layers.MaxPooling2D((2, 2)),
    keras.layers.Flatten(),
    keras.layers.Dense(128, activation='relu'),
    keras.layers.Dropout(0.2),
    keras.layers.Dense(8, activation='softmax')
])

% Compile the model
model.compile(optimizer='adam',
              loss='categorical_crossentropy',
              metrics=['accuracy'])

% Load the training and testing data
train_datagen = ImageDataGenerator(rescale=1./255)
test_datagen = ImageDataGenerator(rescale=1./255)

train_dir = 'path/to/train/directory'
validation_dir = 'path/to/validation/directory'

batch_size = 32

train_generator = train_datagen.flow_from_directory(train_dir,
                                                      target_size=(224, 224),
                                                      batch_size=batch_size,
                                                      class_mode='categorical')

validation_generator = test_datagen.flow_from_directory(validation_dir,
                                                         target_size=(224, 224),
                                                         batch_size=batch_size,
                                                         class_mode='categorical')

% Train the model
history = model.fit(train_generator,
                    epochs=10,
                    validation_data=validation_generator)

% Evaluate the model
test_loss, test_acc = model.evaluate(validation_generator)