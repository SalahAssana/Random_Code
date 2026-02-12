import pandas as pd
from sklearn.preprocessing import MinMaxScaler
from keras.models import Sequential
from keras.layers import LSTM, Dense, Dropout
from keras.callbacks import EarlyStopping, ModelCheckpoint

class StockMarketAnalyzer:
    def __init__(self, data_file):
        self.data = pd.read_csv(data_file)
        self.scaler = MinMaxScaler()
        self.model = None

    def preprocess_data(self):
        self.data['Date'] = pd.to_datetime(self.data['Date'])
        self.data.set_index('Date', inplace=True)
        self.data.dropna(inplace=True)
        self.data['Close'] = self.data['Close'].apply(lambda x: float(x.replace(',', '')))
        self.data[['Open', 'High', 'Low', 'Close']] = self.scaler.fit_transform(self.data[['Open', 'High', 'Low', 'Close']])
        return self.data

    def build_lstm_model(self):
        model = Sequential()
        model.add(LSTM(units=50, input_shape=(1, 1)))
        model.add(Dense(1))
        model.compile(optimizer='adam', loss='mean_squared_error')
        return model

    def train_lstm_model(self, epochs=100):
        X_train, y_train = self.data['Close'][:-30], self.data['Close'][30:]
        X_train = X_train.reshape(-1, 1, 1)
        self.model.fit(X_train, y_train, epochs=epochs, validation_data=(X_train, y_train), verbose=2)
        return self.model

    def predict_lstm_model(self):
        X_test = self.data['Close'][:-30].reshape(-1, 1, 1)
        predictions = self.model.predict(X_test)
        return predictions

    def evaluate_model(self, actual_values):
        mse = ((self.model.predict(self.data['Close'][:-30].reshape(-1, 1, 1)) - actual_values) ** 2).mean()
        rmse = (mse ** 0.5)
        print(f'MSE: {mse:.4f}, RMSE: {rmse:.4f}')

    def run_analyzer(self):
        self.data = self.preprocess_data()
        self.model = self.build_lstm_model()
        self.model = self.train_lstm_model()
        predictions = self.predict_lstm_model()
        actual_values = self.data['Close'][30:]
        self.evaluate_model(actual_values)

if __name__ == '__main__':
    analyzer = StockMarketAnalyzer('stock_data.csv')
    analyzer.run_analyzer()