from PIL import Image
import numpy as np

class FilterChain:
    def __init__(self):
        self.filters = []

    def add_filter(self, filter):
        self.filters.append(filter)

    def apply_filters(self, img):
        filtered_img = img.copy()
        for f in self.filters:
            filtered_img = f.apply(filtered_img)
        return filtered_img

class Filter:
    def __init__(self):
        pass

    def apply(self, img):
        raise NotImplementedError("Subclasses must implement apply method")

class GrayscaleFilter(Filter):
    def apply(self, img):
        img_array = np.array(img)
        grayscale_img = np.dot(img_array[...,:3], [0.299, 0.587, 0.114])
        return Image.fromarray(grayscale_img.astype('uint8')).convert('L')

class BlurFilter(Filter):
    def apply(self, img):
        img_array = np.array(img)
        blurred_img = np.zeros_like(img_array)
        for i in range(1, img_array.shape[0]-1):
            for j in range(1, img_array.shape[1]-1):
                pixel_sum = 0
                for k in range(-1,2):
                    for l in range(-1,2):
                        if 0 <= i+k < img_array.shape[0] and 0 <= j+l < img_array.shape[1]:
                            pixel_sum += img_array[i+k][j+l]
                blurred_img[i][j] = int(pixel_sum / 9)
        return Image.fromarray(blurred_img.astype('uint8'))

if __name__ == '__main__':
    filter_chain = FilterChain()
    filter_chain.add_filter(GrayscaleFilter())
    filter_chain.add_filter(BlurFilter())
    
    img = Image.open("input.jpg")
    filtered_img = filter_chain.apply_filters(img)
    
    filtered_img.save("output.jpg", "JPEG")