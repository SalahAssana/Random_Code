import tensorflow as tf
from sklearn.datasets import make_moons
from sklearn.model_selection import train_test_split
import numpy as np

class NeuralNetwork:
    def __init__(self, learning_rate=0.01, n_iterations=1000):
        self.learning_rate = learning_rate
        self.n_iterations = n_iterations

    def load_data(self):
        X, y = make_moons(500, noise=0.20)
        X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
        return X_train, X_test, y_train, y_test

    def initialize_weights(self):
        self.weights1 = tf.Variable(tf.random_normal([2, 3]))
        self.weights2 = tf.Variable(tf.random_normal([3, 1]))

    def feedforward(self, inputs):
        hidden_layer = tf.nn.sigmoid(tf.matmul(inputs, self.weights1))
        output = tf.matmul(hidden_layer, self.weights2)
        return output

    def train(self, X_train, y_train):
        for _ in range(self.n_iterations):
            prediction = self.feedforward(X_train)
            error = 0.5 * (prediction - y_train) ** 2
            gradient_weights1 = tf.matmul(tf.transpose(X_train), (2 * (prediction - y_train) * tf.nn.sigmoid derivative(prediction)))
            gradient_weights2 = tf.matmul(tf.transpose(hidden_layer), 2 * (prediction - y_train))
            self.weights1.assign_add(self.learning_rate * gradient_weights1)
            self.weights2.assign_add(self.learning_rate * gradient_weights2)

    def test(self, X_test):
        prediction = self.feedforward(X_test)
        return tf.reduce_mean((prediction - y_test) ** 2).numpy()

if __name__ == '__main__':
    nn = NeuralNetwork()
    X_train, X_test, y_train, y_test = nn.load_data()
    nn.initialize_weights()
    nn.train(X_train, y_train)
    print("Mean Squared Error (MSE): ", nn.test(X_test))