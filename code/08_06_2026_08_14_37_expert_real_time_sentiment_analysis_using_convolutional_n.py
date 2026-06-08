# Real-time Sentiment Analysis using Convolutional Neural Networks
import numpy as np
import tensorflow as tf
from tensorflow.keras.preprocessing.text import Tokenizer
from tensorflow.keras.preprocessing.sequence import pad_sequences
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix
import random
import pickle

class SentimentAnalysis:
    def __init__(self):
        self.data_path = 'sentiment_data.pkl'
        self.model_path = 'model.h5'

    def load_data(self):
        with open(self.data_path, 'rb') as f:
            data = pickle.load(f)
        return data['train'], data['test']

    def preprocess_text(self, texts):
        tokenizer = Tokenizer(num_words=5000)
        tokenizer.fit_on_texts(texts)
        sequences = tokenizer.texts_to_sequences(texts)
        padded = pad_sequences(sequences, maxlen=200)
        return padded

    def train_model(self, X_train, y_train, epochs=10):
        model = tf.keras.Sequential([
            tf.keras.layers.Embedding(input_dim=5000, output_dim=128, input_length=200),
            tf.keras.layers.Conv1D(64, 3, activation='relu'),
            tf.keras.layers.MaxPooling1D(pool_size=2),
            tf.keras.layers.Flatten(),
            tf.keras.layers.Dense(64, activation='relu'),
            tf.keras.layers.Dropout(0.5),
            tf.keras.layers.Dense(2, activation='softmax')
        ])
        model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])
        history = model.fit(X_train, y_train, epochs=epochs, verbose=1)
        return model

    def evaluate_model(self, X_test, y_test):
        model = tf.keras.models.load_model(self.model_path)
        y_pred = model.predict_classes(X_test)
        accuracy = accuracy_score(y_test, y_pred)
        report = classification_report(y_test, y_pred)
        matrix = confusion_matrix(y_test, y_pred)
        return accuracy, report, matrix

    def main(self):
        X_train, y_train, X_test, y_test = self.load_data()
        X_train = self.preprocess_text(X_train)
        X_test = self.preprocess_text(X_test)
        model = self.train_model(X_train, y_train)
        model.save(self.model_path)
        accuracy, report, matrix = self.evaluate_model(X_test, y_test)
        print(f'Accuracy: {accuracy:.3f}')
        print('Classification Report:')
        print(report)
        print('Confusion Matrix:')
        print(matrix)

if __name__ == '__main__':
    sentiment_analysis = SentimentAnalysis()
    sentiment_analysis.main()