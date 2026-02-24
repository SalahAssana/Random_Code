import cv2
import numpy as np
from scipy import ndimage

class ImageProcessor:
    def __init__(self):
        self.filter_bank = {
            'blur': lambda img: cv2.blur(img, (5, 5)),
            'sharpen': lambda img: cv2.filter2D(img, -1, np.array([[0, -1, 0], [-1, 5, -1], [0, -1, 0]])),
            'edge_detect': lambda img: cv2.Sobel(img, cv2.CV_8U, 1, 0)
        }

    def apply_filter(self, img, filter_name):
        if filter_name in self.filter_bank:
            return self.filter_bank[filter_name](img)
        else:
            print(f"Filter '{filter_name}' not found.")
            return None

    def extract_features(self, img):
        gray_img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        laplacian_img = cv2.Laplacian(gray_img, cv2.CV_8U)
        feature_map = ndimage.sobel(laplacian_img)
        return feature_map

    def process_image(self, img):
        filtered_img = self.apply_filter(img, 'blur')
        if filtered_img is None:
            return
        edge_detected_img = self.apply_filter(filtered_img, 'edge_detect')
        if edge_detected_img is None:
            return
        feature_map = self.extract_features(edge_detected_img)
        return feature_map

if __name__ == '__main__':
    processor = ImageProcessor()
    img = cv2.imread('image.jpg', cv2.IMREAD_COLOR)
    result = processor.process_image(img)
    if result is not None:
        cv2.imshow('Features', result)
        cv2.waitKey(0)