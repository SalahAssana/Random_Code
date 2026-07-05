import numpy as np
from keras.models import Sequential
from keras.layers import Dense
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

class NeuralNetworkClassifier:
    def __init__(self):
        self.X_train = None
        self.y_train = None
        self.X_test = None
        self.y_test = None
        self.model = None

    def generate_synthetic_data(self, num_samples=1000):
        # Generate synthetic data for binary classification problem
        np.random.seed(42)
        X = np.random.rand(num_samples, 20)
        y = (X[:, 0] > 0.5).astype(int)

        # Split the data into training and testing sets
        self.X_train, self.X_test, self.y_train, self.y_test = train_test_split(X, y, test_size=0.2, random_state=42)
        return

    def build_neural_network(self):
        # Define the neural network architecture
        model = Sequential()
        model.add(Dense(64, activation='relu', input_dim=20))
        model.add(Dense(32, activation='relu'))
        model.add(Dense(1, activation='sigmoid'))

        # Compile the model
        model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])
        self.model = model

    def train_neural_network(self):
        # Train the neural network on the training data
        self.model.fit(self.X_train, self.y_train, epochs=10, verbose=0)

    def evaluate_neural_network(self):
        # Evaluate the neural network on the testing data
        y_pred = self.model.predict(self.X_test) > 0.5
        accuracy = accuracy_score(self.y_test, y_pred)
        print(f'Neural Network Classifier Accuracy: {accuracy:.3f}')

if __name__ == '__main__':
    classifier = NeuralNetworkClassifier()
    classifier.generate_synthetic_data()
    classifier.build_neural_network()
    classifier.train_neural_network()
    classifier.evaluate_neural_network()