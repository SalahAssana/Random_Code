# Import necessary libraries
import numpy as np
from keras.models import Sequential
from keras.layers import Conv2D, MaxPooling2D, Flatten, Dense
from keras.preprocessing.image import ImageDataGenerator
from sklearn.model_selection import train_test_split
from PIL import Image

# Synthetic image data generation
def generate_synthetic_data(num_samples=1000):
    X = []
    y = []
    for _ in range(num_samples):
        img = np.random.randint(0, 255, size=(28, 28), dtype=np.uint8)
        X.append(img.reshape((1, 28, 28, 1)))
        label = np.random.randint(0, 10)
        y.append(label)
    return np.concatenate(X), np.array(y)

# Load synthetic data
X_train, y_train = generate_synthetic_data()

# Split data into training and validation sets
X_train, X_val, y_train, y_val = train_test_split(X_train, y_train, test_size=0.2, random_state=42)

# Define the neural network model
model = Sequential()
model.add(Conv2D(32, kernel_size=(3, 3), activation='relu', input_shape=(28, 28, 1)))
model.add(MaxPooling2D((2, 2)))
model.add(Flatten())
model.add(Dense(128, activation='relu'))
model.add(Dense(10))

# Compile the model
model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])

# Train the model
history = model.fit(X_train, y_train, epochs=5, validation_data=(X_val, y_val), verbose=2)

# Evaluate the model
test_loss, test_acc = model.evaluate(X_val, y_val)
print('Test accuracy:', test_acc)

# Use the model for image classification
def classify_image(img):
    img = img.reshape((1, 28, 28, 1))
    prediction = model.predict(img)
    return np.argmax(prediction)

if __name__ == '__main__':
    # Load a synthetic image and classify it
    img = Image.open('synthetic_image.png')
    img = np.array(img) / 255.0
    classification = classify_image(img)
    print('Classification:', classification)