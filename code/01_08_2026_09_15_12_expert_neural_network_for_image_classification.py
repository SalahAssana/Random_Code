# Neural Network for Image Classification
import tensorflow as tf
from tensorflow.keras.preprocessing.image import ImageDataGenerator
import numpy as np

class CNN:
    def __init__(self):
        self.model = self.create_model()

    def create_model(self):
        model = tf.keras.models.Sequential([
            tf.keras.layers.Conv2D(32, (3, 3), activation='relu', input_shape=(224, 224, 3)),
            tf.keras.layers.MaxPooling2D((2, 2)),
            tf.keras.layers.Flatten(),
            tf.keras.layers.Dense(128, activation='relu'),
            tf.keras.layers.Dropout(0.2),
            tf.keras.layers.Dense(8, activation='softmax')
        ])
        model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])
        return model

    def train(self, train_dir, val_dir):
        train_datagen = ImageDataGenerator(rescale=1./255)
        validation_datagen = ImageDataGenerator(rescale=1./255)

        train_generator = train_datagen.flow_from_directory(train_dir, target_size=(224, 224), batch_size=32, class_mode='categorical')
        validation_generator = validation_datagen.flow_from_directory(val_dir, target_size=(224, 224), batch_size=32, class_mode='categorical')

        self.model.fit(train_generator, epochs=10, validation_data=validation_generator)

    def evaluate(self, test_dir):
        test_datagen = ImageDataGenerator(rescale=1./255)
        test_generator = test_datagen.flow_from_directory(test_dir, target_size=(224, 224), batch_size=32, class_mode='categorical')
        loss, accuracy = self.model.evaluate(test_generator)
        print(f"Test Loss: {loss}, Test Accuracy: {accuracy}")

if __name__ == '__main__':
    cnn = CNN()
    train_dir = 'path_to_train_dir'
    val_dir = 'path_to_val_dir'
    test_dir = 'path_to_test_dir'
    cnn.train(train_dir, val_dir)
    cnn.evaluate(test_dir)