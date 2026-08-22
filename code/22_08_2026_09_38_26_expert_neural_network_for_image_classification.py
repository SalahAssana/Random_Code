# Neural Network for Image Classification
import tensorflow as tf
from tensorflow import keras
from skimage.io import imread
from skimage.transform import resize
from sklearn.model_selection import train_test_split
import numpy as np

if __name__ == '__main__':
    # Load the dataset (assuming it's a synthetic dataset)
    X_train, y_train = load_synthetic_dataset()

    # Split the data into training and validation sets
    X_train, X_val, y_train, y_val = train_test_split(X_train, y_train, test_size=0.2, random_state=42)

    # Define the neural network model
    model = keras.Sequential([
        keras.layers.Conv2D(32, (3, 3), activation='relu', input_shape=(224, 224, 3)),
        keras.layers.MaxPooling2D((2, 2)),
        keras.layers.Flatten(),
        keras.layers.Dense(128, activation='relu'),
        keras.layers.Dropout(0.2),
        keras.layers.Dense(10)
    ])

    # Compile the model
    model.compile(optimizer='adam',
                  loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
                  metrics=['accuracy'])

    # Train the model
    history = model.fit(X_train, y_train, epochs=5, 
                         validation_data=(X_val, y_val), verbose=2)

    # Evaluate the model on the test set
    loss, accuracy = model.evaluate(X_val, y_val)
    print(f'Test accuracy: {accuracy:.3f}')

    # Save the trained model
    model.save('image_classification_model.h5')

    def load_synthetic_dataset():
        # Load synthetic dataset (assuming it's a collection of images and labels)
        X = []
        y = []
        for i in range(1000):
            img = imread(f'img_{i}.jpg')
            img = resize(img, (224, 224))
            X.append(img)
            y.append(i % 10)

        return np.array(X), np.array(y)