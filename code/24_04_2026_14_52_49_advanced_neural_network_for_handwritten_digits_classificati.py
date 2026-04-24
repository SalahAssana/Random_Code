# Neural Network for Handwritten Digits Classification
import numpy as np
from keras.models import Sequential
from keras.layers import Dense, Dropout, Flatten
from keras.optimizers import Adam
from keras.utils import to_categorical
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
import matplotlib.pyplot as plt

class NeuralNetwork:
    def __init__(self):
        self.model = None

    def load_data(self):
        # Load MNIST dataset
        from keras.datasets import mnist
        (train_images, train_labels), (test_images, test_labels) = mnist.load_data()
        return train_images, train_labels, test_images, test_labels

    def build_model(self):
        self.model = Sequential()
        self.model.add(Flatten(input_shape=(28*28)))
        self.model.add(Dense(64, activation='relu'))
        self.model.add(Dropout(0.2))
        self.model.add(Dense(10, activation='softmax'))
        self.model.compile(optimizer=Adam(lr=0.001), loss='categorical_crossentropy', metrics=['accuracy'])

    def train_model(self, train_images, train_labels):
        train_labels = to_categorical(train_labels)
        self.model.fit(train_images, train_labels, epochs=5, batch_size=128)

    def evaluate_model(self, test_images, test_labels):
        test_labels = to_categorical(test_labels)
        loss, accuracy = self.model.evaluate(test_images, test_labels)
        print(f'Test accuracy: {accuracy:.2f}%')

    def plot_accuracy(self, train_loss, train_acc, val_loss, val_acc):
        plt.plot(train_loss)
        plt.plot(val_loss)
        plt.xlabel('Epoch')
        plt.ylabel('Loss')
        plt.title('Training and Validation Loss')
        plt.legend(['Train', 'Validation'], loc='upper right')
        plt.show()

    def main(self):
        train_images, train_labels, test_images, test_labels = self.load_data()
        X_train, X_val, y_train, y_val = train_test_split(train_images, train_labels, test_size=0.2, random_state=42)
        
        self.build_model()
        self.train_model(X_train, y_train)
        self.evaluate_model(test_images, test_labels)
        self.plot_accuracy(np.array([]), np.array([]), np.array([]), np.array([]))

if __name__ == '__main__':
    nn = NeuralNetwork()
    nn.main()