import cv2
import numpy as np
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Flatten, Dense

class Filter:
    def __init__(self):
        self.model = None

    def load_model(self):
        if self.model is None:
            self.model = Sequential()
            self.model.add(Conv2D(32, (3, 3), activation='relu', input_shape=(224, 224, 3)))
            self.model.add(MaxPooling2D((2, 2)))
            self.model.add(Flatten())
            self.model.add(Dense(128, activation='relu'))
            self.model.add(Dense(1))
            self.model.compile(optimizer='adam', loss='binary_crossentropy')

    def apply_filter(self, image):
        self.load_model()
        predictions = self.model.predict(image)
        filtered_image = cv2.applyColorMap((predictions * 255).astype('uint8'), cv2.COLORMAP_JET)
        return filtered_image

def detect_edges(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    edges = cv2.Canny(gray, 50, 150)
    return edges

def main():
    image = cv2.imread('image.jpg')
    filter_obj = Filter()
    filtered_image = filter_obj.apply_filter(np.array([image]))
    edge_map = detect_edges(image)
    cv2.imshow('Filtered Image', filtered_image[0])
    cv2.imshow('Edge Map', edge_map)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()