import cv2
import numpy as np
from functools import lru_cache

class Filter:
    def __init__(self):
        pass

    @lru_cache(maxsize=None)
    def apply(self, image):
        raise NotImplementedError

class GrayscaleFilter(Filter):
    def apply(self, image):
        return cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

class BlurFilter(Filter):
    def __init__(self, kernel_size=5):
        self.kernel_size = kernel_size
        self.blur_kernel = np.ones((kernel_size, kernel_size)) / (kernel_size ** 2)

    @lru_cache(maxsize=None)
    def apply(self, image):
        return cv2.filter2D(image, -1, self.blur_kernel)

class SharpenFilter(Filter):
    def __init__(self):
        pass

    @lru_cache(maxsize=None)
    def apply(self, image):
        kernel = np.array([[-1,-1,-1], [-1,9,-1], [-1,-1,-1]])
        return cv2.filter2D(image, -1, kernel)

class EdgeDetectionFilter(Filter):
    def __init__(self):
        pass

    @lru_cache(maxsize=None)
    def apply(self, image):
        return cv2.Canny(image, 100, 200)

def process_image(image_path):
    image = cv2.imread(image_path)
    filtered_images = [filter_.apply(image) for filter_ in [GrayscaleFilter(), BlurFilter(), SharpenFilter(), EdgeDetectionFilter()]]
    return filtered_images

if __name__ == '__main__':
    filtered_images = process_image('input.jpg')
    for i, image in enumerate(filtered_images):
        cv2.imshow(f'Filtered Image {i}', image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()