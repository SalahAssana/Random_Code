# Import necessary libraries
import numpy as np
from sklearn.preprocessing import StandardScaler
from keras.models import Sequential
from keras.layers import Dense
from keras.utils import to_categorical
from keras.callbacks import EarlyStopping, ModelCheckpoint
from keras.wrappers.scikit_learn import KerasClassifier
from sklearn.model_selection import train_test_split

# Synthetic data generation for this example
np.random.seed(42)
X = np.random.rand(1000, 10)
y = np.random.randint(0, 2, size=(1000,))

# Preprocessing and feature scaling
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# Split the data into training and testing sets
train_X, test_X, train_y, test_y = train_test_split(X_scaled, y, test_size=0.2, random_state=42)

# Define the neural network model architecture
def create_model():
    model = Sequential()
    model.add(Dense(64, activation='relu', input_shape=(10,)))
    model.add(Dense(32, activation='relu'))
    model.add(Dense(2, activation='softmax'))
    return model

# Compile and train the model with early stopping
model = KerasClassifier(build_fn=create_model)
early_stopping = EarlyStopping(monitor='val_loss', patience=5)
modelcheckpoint = ModelCheckpoint('best_model.hdf5', monitor='val_loss', save_best_only=True, mode='min')
history = model.fit(train_X, to_categorical(train_y), epochs=100, batch_size=128, validation_data=(test_X, to_categorical(test_y)), 
                    callbacks=[early_stopping, modelcheckpoint], verbose=2)

# Evaluate the trained model
y_pred = model.predict(test_X)
y_pred_class = np.argmax(y_pred, axis=1)
print('Test accuracy:', np.mean(y_pred_class == test_y))