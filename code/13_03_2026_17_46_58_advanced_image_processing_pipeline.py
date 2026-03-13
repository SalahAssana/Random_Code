import cv2
import numpy as np
from functools import lru_cache

class ImageProcessor:
    def __init__(self):
        self.images = []

    @lru_cache(maxsize=None)
    def load_image(self, path):
        return cv2.imread(path)

    def apply_filter(self, image, filter_type):
        if filter_type == 'blur':
            return cv2.blur(image, (5, 5))
        elif filter_type == 'sharpen':
            kernel = np.array([[-1,-1,-1], [-1,9,-1], [-1,-1,-1]])
            return cv2.filter2D(image, -1, kernel)
        else:
            raise ValueError(f"Invalid filter type: {filter_type}")

    def apply_threshold(self, image, threshold):
        _, thresh = cv2.threshold(image, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
        return thresh

    def apply_contour(self, image, contour_size):
        contours, _ = cv2.findContours(image, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        contour = max(contours, key=cv2.contourArea)
        x, y, w, h = cv2.boundingRect(contour)
        return cv2.rectangle(image, (x, y), (x+w, y+h), (0, 255, 0), contour_size)

    def process_image(self, path):
        image = self.load_image(path)
        filtered = self.apply_filter(image, 'blur')
        thresholded = self.apply_threshold(filtered, 127)
        contoured = self.apply_contour(thresholded, 2)
        return contoured

if __name__ == '__main__':
    processor = ImageProcessor()
    images = ['image1.jpg', 'image2.jpg']
    for image in images:
        processed_image = processor.process_image(image)
        cv2.imwrite(f'processed_{image}', processed_image)