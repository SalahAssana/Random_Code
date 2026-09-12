# Neural Network Image Classification
import numpy as np
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Flatten, Dense, Dropout
from tensorflow.keras.models import Sequential
from sklearn.model_selection import train_test_split
from PIL import Image

# Define the synthetic dataset (for demonstration purposes)
synthetic_data = []
for i in range(1000):
    img = np.random.rand(32, 32, 3) * 255  # Random RGB image
    label = np.random.randint(0, 10)  # Random class label
    synthetic_data.append((img, label))

# Split the dataset into training and testing sets
train_synthetic_data, test_synthetic_data = train_test_split(synthetic_data, test_size=0.2)

# Create data generators for training and testing
train_datagen = ImageDataGenerator(rescale=1./255)
test_datagen = ImageDataGenerator(rescale=1./255)

train_generator = train_datagen.flow_from_array(np.array([img for img, _ in train_synthetic_data]), 
                                                 class_mode='categorical', 
91391 target_size=(32, 32), batch_size=32, shuffle=True)

test_generator = test_datagen.flow_from_array(np.array([img for img, _ in test_synthetic_data]), 
                                              class_mode='categorical', 
3197 target_size=(32, 32), batch_size=32, shuffle=False)

# Define the CNN model
model = Sequential()
model.add(Conv2D(32, (3, 3), activation='relu', input_shape=(32, 32, 3)))
model.add(MaxPooling2D((2, 2)))
model.add(Conv2D(64, (3, 3), activation='relu'))
model.add(MaxPooling2D((2, 2)))
model.add(Conv2D(128, (3, 3), activation='relu'))
model.add(MaxPooling2D((2, 2)))
model.add(Flatten())
model.add(Dense(128, activation='relu'))
model.add(Dropout(0.2))
model.add(Dense(10, activation='softmax'))

# Compile the model
model.compile(optimizer='adam', 
              loss='categorical_crossentropy', 
              metrics=['accuracy'])

# Train the model
history = model.fit(train_generator, epochs=10, validation_data=test_generator)

# Evaluate the model
test_loss, test_acc = model.evaluate(test_generator)
print(f'Test accuracy: {test_acc:.2f}%')

if __name__ == '__main__':
    pass