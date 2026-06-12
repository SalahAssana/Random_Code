import cv2
import numpy as np
from collections import deque

class ImageFilter:
    def __init__(self, image_path):
        self.image = cv2.imread(image_path)
        self.filter_queue = deque()

    def apply_blur(self):
        blur_kernel = [[1/9, 1/9, 1/9],
                        [1/9, 8/9, 1/9],
                        [1/9, 1/9, 1/9]]
        blurred_image = cv2.filter2D(self.image, -1, np.array(blur_kernel))
        self.filter_queue.append(blurred_image)

    def apply_edges(self):
        edges_image = cv2.Canny(self.image, 100, 200)
        self.filter_queue.append(edges_image)

    def apply_sharpen(self):
        sharpen_kernel = [[0, -1, 0],
                           [-1, 5, -1],
                           [0, -1, 0]]
        sharpened_image = cv2.filter2D(self.image, -1, np.array(sharpen_kernel))
        self.filter_queue.append(sharpened_image)

    def display_filters(self):
        for i, filter_image in enumerate(self.filter_queue):
            cv2.imshow(f"Filter {i+1}", filter_image)
        cv2.waitKey(0)
        cv2.destroyAllWindows()

    def run(self):
        self.apply_blur()
        self.apply_edges()
        self.apply_sharpen()
        self.display_filters()

if __name__ == '__main__':
    image_filter = ImageFilter('image.jpg')
    image_filter.run()