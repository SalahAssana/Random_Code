import numpy as np
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from keras.models import Sequential
from keras.layers import Dense

class NeuralNetworkClassifier:
    def __init__(self, X, y):
        self.X = X
        self.y = y
        self.scaler = StandardScaler()
        self.model = None

    def preprocess(self):
        self.X_scaled = self.scaler.fit_transform(self.X)

    def split_data(self):
        self.X_train, self.X_test, self.y_train, self.y_test = train_test_split(
            self.X_scaled, self.y, test_size=0.2, random_state=42
        )

    def build_model(self):
        self.model = Sequential()
        self.model.add(Dense(64, activation='relu', input_dim=self.X.shape[1]))
        self.model.add(Dense(32, activation='relu'))
        self.model.add(Dense(1, activation='sigmoid'))

    def compile_model(self):
        self.model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])

    def train_model(self):
        self.model.fit(
            self.X_train, self.y_train, epochs=10, batch_size=128, verbose=2
        )

    def evaluate_model(self):
        loss, accuracy = self.model.evaluate(self.X_test, self.y_test)
        print(f'Test accuracy: {accuracy:.2f}')

if __name__ == '__main__':
    # Synthetic data for demonstration purposes
    X = np.random.rand(1000, 10)
    y = (np.random.rand(1000) > 0.5).astype(int)

    nn = NeuralNetworkClassifier(X, y)
    nn.preprocess()
    nn.split_data()
    nn.build_model()
    nn.compile_model()
    nn.train_model()
    nn.evaluate_model()