import numpy as np
from sklearn.utils import shuffle
from keras.models import Sequential
from keras.layers import Dense, Dropout, Conv2D, MaxPooling2D
from keras.optimizers import Adam
from keras.preprocessing.image import ImageDataGenerator
from keras.regularizers import l2

# Define constants
BATCH_SIZE = 128
EPOCHS = 10
VALIDATION_SPLIT = 0.2

# Load MNIST dataset
(x_train, y_train), (x_test, y_test) = np.load('mnist.npy')

# Normalize pixel values to be between 0 and 1
x_train, x_test = x_train / 255.0, x_test / 255.0

# Shuffle training data
x_train, y_train = shuffle(x_train, y_train)

# Define the neural network model
model = Sequential()
model.add(Conv2D(32, (3, 3), activation='relu', input_shape=(28, 28, 1)))
model.add(MaxPooling2D((2, 2)))
model.add(Dropout(0.25))
model.add(Flatten())
model.add(Dense(128, kernel_regularizer=l2(0.01), activation='relu'))
model.add(Dropout(0.5))
model.add(Dense(10, activation='softmax'))

# Compile the model
model.compile(optimizer=Adam(lr=0.001), loss='categorical_crossentropy', metrics=['accuracy'])

# Define data generators for training and validation sets
train_datagen = ImageDataGenerator(rescale=1./255)
validation_datagen = ImageDataGenerator(rescale=1./255)

train_generator = train_datagen.flow_from_array(x_train, y_train, target_size=(28, 28), batch_size=BATCH_SIZE, class_mode='categorical')
validation_generator = validation_datagen.flow_from_array(x_test, y_test, target_size=(28, 28), batch_size=BATCH_SIZE, class_mode='categorical')

# Train the model
model.fit(train_generator, epochs=EPOCHS, validation_data=validation_generator, verbose=2)

# Evaluate the model on test data
loss, accuracy = model.evaluate(x_test, y_test)
print('Test loss:', loss)
print('Test accuracy:', accuracy)

if __name__ == '__main__':
    pass