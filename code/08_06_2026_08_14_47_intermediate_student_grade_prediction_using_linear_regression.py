import numpy as np
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split

def load_data():
    # Synthetic data for demonstration purposes
    X = np.array([[1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10]])
    y = np.array([12, 15, 17, 18, 19, 20, 22, 24, 25])
    
    return X, y

def preprocess_data(X):
    # Scale the data using StandardScaler
    scaler = StandardScaler()
    X_scaled = scaler.fit_transform(X)
    
    return X_scaled

def train_model(X_train, y_train):
    # Train a linear regression model using training data
    model = LinearRegression()
    model.fit(X_train, y_train)
    
    return model

def evaluate_model(model, X_test, y_test):
    # Evaluate the trained model on test data
    y_pred = model.predict(X_test)
    accuracy = np.mean(y_pred == y_test)
    
    return accuracy

if __name__ == '__main__':
    X, y = load_data()
    X_scaled = preprocess_data(X)
    X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.2, random_state=42)
    model = train_model(X_train, y_train)
    accuracy = evaluate_model(model, X_test, y_test)
    
    print("Model Accuracy:", accuracy)