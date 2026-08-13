import numpy as np
from sklearn.preprocessing import StandardScaler
from keras.models import Sequential
from keras.layers import Dense
from keras.optimizers import Adam
from keras.callbacks import EarlyStopping, ModelCheckpoint
from keras.utils import to_categorical
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix
from keras.wrappers.scikit_learn import KerasClassifier

# Synthetic data generation
np.random.seed(0)
n_samples = 1000
n_features = 20
n_classes = 3

X_train_synthetic = np.random.rand(n_samples, n_features)
y_train_synthetic = np.random.randint(0, n_classes, size=(n_samples,))
X_test_synthetic = np.random.rand(int(0.2*n_samples), n_features)
y_test_synthetic = y_train_synthetic[int(0.8*n_samples):]

# Data preprocessing
scaler = StandardScaler()
X_train_synthetic_scaled = scaler.fit_transform(X_train_synthetic)
X_test_synthetic_scaled = scaler.transform(X_test_synthetic)

# Model definition
def create_model():
    model = Sequential([
        Dense(64, activation='relu', input_shape=(n_features,)),
        Dense(32, activation='relu'),
        Dense(n_classes, activation='softmax')
    ])
    model.compile(optimizer=Adam(lr=0.001), loss='categorical_crossentropy', metrics=['accuracy'])
    return model

# Model training
model = KerasClassifier(build_fn=create_model)
early_stopping = EarlyStopping(monitor='val_loss', patience=5, min_delta=0.001)
model_checkpoint = ModelCheckpoint('best_model.hdf5', monitor='val_loss', save_best_only=True, mode='min')
history = model.fit(X_train_synthetic_scaled, to_categorical(y_train_synthetic), epochs=100, 
                    validation_data=(X_test_synthetic_scaled, to_categorical(y_test_synthetic)), 
                    callbacks=[early_stopping, model_checkpoint], verbose=2)

# Model evaluation
y_pred = model.predict(X_test_synthetic_scaled)
y_pred_class = np.argmax(y_pred, axis=1)
print('Accuracy:', accuracy_score(y_test_synthetic, y_pred_class))
print('Classification Report:')
print(classification_report(y_test_synthetic, y_pred_class))
print('Confusion Matrix:')
print(confusion_matrix(y_test_synthetic, y_pred_class))

if __name__ == '__main__':
    pass