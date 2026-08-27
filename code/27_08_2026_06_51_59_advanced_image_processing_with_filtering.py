import numpy as np
from scipy import ndimage
from PIL import Image

class Filter:
    def __init__(self):
        pass

    def blur(self, img):
        return ndimage.gaussian_filter(img, sigma=1)

    def sharpen(self, img):
        kernel = np.array([[0, -1, 0], [-1, 5, -1], [0, -1, 0]])
        return ndimage.convolve(img, kernel)

def apply_filters(image_path):
    image = Image.open(image_path)
    image_array = np.array(image)

    filter_obj = Filter()
    blurred_image = filter_obj.blur(image_array)
    sharpened_image = filter_obj.sharpen(blurred_image)

    return blurred_image, sharpened_image

if __name__ == '__main__':
    blurred_image, sharpened_image = apply_filters('input.jpg')
    Image.fromarray(blurred_image).show()
    Image.fromarray(sharpened_image).show()