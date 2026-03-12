import numpy as np
from sklearn.preprocessing import StandardScaler
from keras.models import Sequential
from keras.layers import Dense

# Synthetic data generation
np.random.seed(0)
X = 10 * np.random.rand(1000, 2) - 5
y = (np.sum(X ** 2, axis=1) > 7).astype(int)

# Splitting the data into training and testing sets
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Standardizing the features
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# Building and training a neural network model
model = Sequential()
model.add(Dense(64, activation='relu', input_dim=2))
model.add(Dense(32, activation='relu'))
model.add(Dense(1, activation='sigmoid'))
model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])
history = model.fit(X_train, y_train, epochs=20, batch_size=128, verbose=0)

# Evaluating the performance of the neural network
y_pred = (model.predict(X_test) > 0.5).astype(int)
print("Accuracy:", np.mean(y_test == y_pred))

if __name__ == '__main__':
    pass