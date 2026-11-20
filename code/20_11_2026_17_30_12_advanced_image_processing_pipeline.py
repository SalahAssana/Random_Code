import cv2
import numpy as np
from typing import List, Tuple

class ImageProcessor:
    def __init__(self):
        self.image: np.ndarray = None

    def load_image(self, path: str) -> None:
        """Load an image from a file."""
        self.image = cv2.imread(path)

    def apply_grayscale(self) -> None:
        """Convert the image to grayscale."""
        self.image = cv2.cvtColor(self.image, cv2.COLOR_BGR2GRAY)

    def apply_blur(self) -> None:
        """Apply Gaussian blur to the image."""
        blurred_image: np.ndarray = cv2.GaussianBlur(self.image, (5, 5), 0)
        self.image = blurred_image

    def apply_thresholding(self, threshold: int) -> None:
        """Apply thresholding to the image."""
        _, thresh: np.ndarray = cv2.threshold(self.image, threshold, 255, cv2.THRESH_BINARY)
        self.image = thresh

    def save_image(self, path: str) -> None:
        """Save the processed image to a file."""
        cv2.imwrite(path, self.image)

def main() -> None:
    processor: ImageProcessor = ImageProcessor()
    processor.load_image("input.jpg")
    processor.apply_grayscale()
    processor.apply_blur()
    processor.apply_thresholding(127)
    processor.save_image("output.jpg")

if __name__ == '__main__':
    main()