import pandas as pd
import numpy as np
from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import train_test_split
from keras.models import Sequential
from keras.layers import LSTM, Dense

class StockMarketAnalysis:
    def __init__(self):
        self.data = None

    def load_data(self, file_path):
        # Load stock market data from CSV file
        self.data = pd.read_csv(file_path)

    def preprocess_data(self):
        # Scale and normalize the data
        scaler = MinMaxScaler()
        self.data[['Open', 'High', 'Low', 'Close']] = scaler.fit_transform(
            self.data[['Open', 'High', 'Low', 'Close']])

    def split_data(self, train_size=0.8):
        # Split the data into training and testing sets
        self.train_data, self.test_data = train_test_split(
            self.data, test_size=(1 - train_size), random_state=42)

    def build_model(self):
        # Build a simple LSTM model for stock market prediction
        model = Sequential()
        model.add(LSTM(units=50, return_sequences=True))
        model.add(Dense(64, activation='relu'))
        model.add(Dense(4))  # Predict Open, High, Low, Close
        model.compile(loss='mean_squared_error', optimizer='adam')
        return model

    def train_model(self):
        # Train the model on the training data
        self.model.fit(
            np.array(self.train_data[['Open', 'High', 'Low', 'Close']]),
            np.array(self.train_data['Predicted']),
            epochs=50, batch_size=32)

    def evaluate_model(self):
        # Evaluate the model on the testing data
        loss = self.model.evaluate(
            np.array(self.test_data[['Open', 'High', 'Low', 'Close']]),
            np.array(self.test_data['Predicted']))
        print(f'Model evaluation: Loss={loss[0]:.4f}')

    def predict(self):
        # Make predictions on the testing data
        predictions = self.model.predict(
            np.array(self.test_data[['Open', 'High', 'Low', 'Close']]))
        return predictions

    def main(self, file_path='stock_market_data.csv'):
        if __name__ == '__main__':
            self.load_data(file_path)
            self.preprocess_data()
            self.split_data()
            model = self.build_model()
            self.train_model()
            self.evaluate_model()
            predictions = self.predict()
            print('Predictions:', predictions)

if __name__ == '__main__':
    analysis = StockMarketAnalysis()
    analysis.main()