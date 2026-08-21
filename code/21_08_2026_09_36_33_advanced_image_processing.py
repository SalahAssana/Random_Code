import cv2
import numpy as np

class ImageProcessor:
    def __init__(self):
        self.image = None

    def load_image(self, path):
        self.image = cv2.imread(path)

    def apply_grayscale(self):
        if self.image is not None:
            grayscale_image = cv2.cvtColor(self.image, cv2.COLOR_BGR2GRAY)
            return grayscale_image
        else:
            print("No image loaded")
            return None

    def apply_blur(self):
        if self.image is not None:
            blurred_image = cv2.blur(self.image, (5, 5))
            return blurred_image
        else:
            print("No image loaded")
            return None

    def apply_edge_detection(self):
        if self.image is not None:
            edge_detected_image = cv2.Canny(self.image, 100, 200)
            return edge_detected_image
        else:
            print("No image loaded")
            return None

    def save_results(self, path):
        grayscale_image = self.apply_grayscale()
        blurred_image = self.apply_blur()
        edge_detected_image = self.apply_edge_detection()

        cv2.imwrite(f"{path}_grayscale.png", grayscale_image)
        cv2.imwrite(f"{path}_blurred.png", blurred_image)
        cv2.imwrite(f"{path}_edge_detected.png", edge_detected_image)

    def __str__(self):
        return f"ImageProcessor instance with {self.image.shape[0]}x{self.image.shape[1]} image"


if __name__ == '__main__':
    processor = ImageProcessor()
    processor.load_image("test_image.jpg")
    processor.save_results("test_output")