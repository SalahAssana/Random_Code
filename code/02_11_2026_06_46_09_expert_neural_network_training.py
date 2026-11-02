#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import tensorflow as tf
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
import numpy as np
import matplotlib.pyplot as plt

class NeuralNetwork:
    def __init__(self, num_classes):
        self.num_classes = num_classes
        self.model = None

    def build_model(self, input_dim):
        if self.model is not None:
            return

        self.model = tf.keras.models.Sequential([
            tf.keras.layers.Flatten(input_shape=(28, 28)),
            tf.keras.layers.Dense(128, activation='relu'),
            tf.keras.layers.Dropout(0.2),
            tf.keras.layers.Dense(self.num_classes)
        ])

    def compile_model(self):
        if self.model is None:
            return

        self.model.compile(optimizer='adam',
                           loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
                           metrics=['accuracy'])

    def train_model(self, X_train, y_train, epochs=10):
        if self.model is None:
            return

        self.model.fit(X_train, y_train, epochs=epochs, verbose=False)

    def evaluate_model(self, X_test, y_test):
        if self.model is None:
            return

        predictions = self.model.predict(X_test)
        predicted_classes = tf.argmax(predictions, axis=1).numpy()
        accuracy = accuracy_score(y_test, predicted_classes)

        print(f'Evaluation Accuracy: {accuracy:.2f}%')

    def load_data(self):
        (X_train, y_train), (X_test, y_test) = tf.keras.datasets.mnist.load_data()

        X_train, X_val = train_test_split(X_train, test_size=0.2, random_state=42)
        return X_train, y_train, X_val, y_test

    def main(self):
        if __name__ == '__main__':
            num_classes = 10
            input_dim = 784

            model = NeuralNetwork(num_classes)

            # Load data
            X_train, y_train, X_val, y_val = model.load_data()

            # Build and compile the model
            model.build_model(input_dim)
            model.compile_model()

            # Train the model
            model.train_model(X_train, y_train, epochs=10)

            # Evaluate the model on validation set
            model.evaluate_model(X_val, y_val)

if __name__ == '__main__':
    neural_network = NeuralNetwork(10)
    neural_network.main()