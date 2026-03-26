import cv2
import numpy as np
from concurrent.futures import ThreadPoolExecutor

class ImageProcessor:
    def __init__(self):
        self.pool = ThreadPoolExecutor()

    def apply_filter(self, image_path, kernel_path):
        # Load the input image and kernel
        image = cv2.imread(image_path)
        kernel = cv2.imread(kernel_path, cv2.IMREAD_GRAYSCALE)

        # Create a result image with the same shape as the input image
        result = np.zeros_like(image)

        # Split the work into multiple threads
        futures = []
        for i in range(0, image.shape[0], 10):
            futures.append(self.pool.submit(self.apply_kernel_to_region, image, kernel, result, i, min(i+10, image.shape[0])))

        # Wait for all threads to finish and merge the results
        self.pool.shutdown()
        for future in futures:
            future.result()

        return result

    def apply_kernel_to_region(self, image, kernel, result, y, height):
        for x in range(0, image.shape[1]):
            patch = image[y:height, x:x+1]
            convolved = cv2.filter2D(patch, -1, kernel)
            result[y:height, x] = convolved

if __name__ == '__main__':
    processor = ImageProcessor()
    filtered_image = processor.apply_filter('input.jpg', 'kernel.png')
    cv2.imwrite('output.jpg', filtered_image)