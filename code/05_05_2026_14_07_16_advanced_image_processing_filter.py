import cv2
import numpy as np

class Filter:
    def __init__(self):
        self.kernel = None

    def load_kernel(self, kernel_path):
        self.kernel = cv2.imread(kernel_path, 0)
        if self.kernel is None:
            raise ValueError("Failed to load the filter kernel")

    def apply_filter(self, image):
        filtered_image = cv2.filter2D(image, -1, self.kernel)
        return filtered_image

class ImageProcessor:
    def __init__(self):
        self.filter = Filter()

    def process_image(self, image_path):
        image = cv2.imread(image_path)
        if image is None:
            raise ValueError("Failed to load the input image")

        try:
            self.filter.load_kernel('filter_kernel.png')
            filtered_image = self.filter.apply_filter(image)
            cv2.imwrite('filtered_image.png', filtered_image)
            print("Image processing completed successfully")
        except Exception as e:
            print(f"An error occurred: {str(e)}")

if __name__ == '__main__':
    processor = ImageProcessor()
    processor.process_image('input_image.jpg')