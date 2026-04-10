import pandas as pd
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix
from datetime import datetime, timedelta
from typing import Dict, List

class WeatherForecast:
    def __init__(self):
        self.data = None
        self.model = None

    def load_data(self) -> None:
        """Load weather data from CSV file."""
        self.data = pd.read_csv('weather_data.csv')

    def preprocess_data(self) -> None:
        """Preprocess the data by converting date columns to datetime format and creating new features."""
        self.data['date'] = pd.to_datetime(self.data['date'])
        self.data['year'] = self.data['date'].dt.year
        self.data['month'] = self.data['date'].dt.month
        self.data['hour'] = self.data['date'].dt.hour

    def split_data(self) -> None:
        """Split the data into training and testing sets."""
        X = self.data.drop('weather', axis=1)
        y = self.data['weather']
        X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

    def train_model(self) -> None:
        """Train a Random Forest classifier on the training data."""
        self.model = RandomForestClassifier(n_estimators=100, random_state=42)
        self.model.fit(X_train, y_train)

    def evaluate_model(self) -> None:
        """Evaluate the trained model on the testing data."""
        y_pred = self.model.predict(X_test)
        print(f"Accuracy: {accuracy_score(y_test, y_pred):.3f}")
        print(classification_report(y_test, y_pred))
        print(confusion_matrix(y_test, y_pred))

    def forecast_weather(self) -> None:
        """Make a weather forecast for the next 7 days based on current conditions."""
        today = datetime.today()
        future_dates = [today + timedelta(days=i) for i in range(7)]
        current_conditions = self.data[self.data['date'] == today].drop('weather', axis=1)
        predictions = self.model.predict(current_conditions)
        for date, prediction in zip(future_dates, predictions):
            print(f"{date}: {prediction}")

if __name__ == '__main__':
    wf = WeatherForecast()
    wf.load_data()
    wf.preprocess_data()
    wf.split_data()
    wf.train_model()
    wf.evaluate_model()
    wf.forecast_weather()