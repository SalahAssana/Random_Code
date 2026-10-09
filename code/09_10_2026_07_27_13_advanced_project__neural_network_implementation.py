import numpy as np
from sklearn.datasets import make_moons
from sklearn.preprocessing import StandardScaler

class NeuralNetwork:
    def __init__(self, X_train, y_train):
        self.X_train = X_train
        self.y_train = y_train
        self.n_inputs = X_train.shape[1]
        self.n_outputs = len(np.unique(y_train))
        self.W1 = np.random.rand(self.n_inputs, 256)
        self.b1 = np.zeros((1, 256))
        self.W2 = np.random.rand(256, self.n_outputs)
        self.b2 = np.zeros((1, self.n_outputs))

    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))

    def sigmoid_derivative(self, x):
        return x * (1 - x)

    def forward_propagation(self, X):
        hidden_layer = self.sigmoid(np.dot(X, self.W1) + self.b1)
        output_layer = self.sigmoid(np.dot(hidden_layer, self.W2) + self.b2)
        return output_layer

    def backpropagation(self, X, y):
        # Forward Propagation
        hidden_layer = self.sigmoid(np.dot(X, self.W1) + self.b1)
        output_layer = self.sigmoid(np.dot(hidden_layer, self.W2) + self.b2)

        # Error Calculation
        error = (y - output_layer)

        # Backward Propagation
        delta_output = error * self.sigmoid_derivative(output_layer)
        delta_hidden = np.dot(delta_output, self.W2.T) * self.sigmoid_derivative(hidden_layer)
        
        # Weight Updates
        dW1 = np.dot(X.T, (delta_hidden[:, 0:256] * self.sigmoid_derivative(hidden_layer)))
        db1 = np.sum(delta_hidden[:, 0:256], axis=0)
        dW2 = np.dot(hidden_layer.T, delta_output)
        db2 = np.sum(delta_output, axis=0)

        # Update Weights
        self.W1 -= 0.01 * dW1
        self.b1 -= 0.01 * db1
        self.W2 -= 0.01 * dW2
        self.b2 -= 0.01 * db2

    def train(self, epochs):
        for _ in range(epochs):
            self.backpropagation(self.X_train, self.y_train)

    def predict(self, X):
        return self.forward_propagation(X)

if __name__ == '__main__':
    X_train, y_train = make_moons(n_samples=1000, noise=0.2)
    scaler = StandardScaler()
    X_train = scaler.fit_transform(X_train)
    nn = NeuralNetwork(X_train, y_train)
    nn.train(10000)
    predictions = nn.predict(X_train)