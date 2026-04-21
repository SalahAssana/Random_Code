import numpy as np
from skimage import io, filters, segmentation
import matplotlib.pyplot as plt

class ImageSegmentation:
    def __init__(self, image_path):
        self.image = io.imread(image_path)
        self.gray_image = self.convert_to_gray()

    def convert_to_gray(self):
        return filters.rgb2gray(self.image)

    def apply_thresholding(self):
        return segmentation.threshold_sequential(self.gray_image, 0.5)

    def segment_objects(self):
        thresholded_image = self.apply_thresholding()
        return segmentation.slic(thresholded_image, compactness=10, sigma=1)

    def visualize_results(self, segmented_image):
        fig, ax = plt.subplots(1)
        ax.imshow(segmented_image)
        plt.show()

    def run_segmentation(self):
        segmented_image = self.segment_objects()
        self.visualize_results(segmented_image)


if __name__ == '__main__':
    image_path = 'path_to_your_image.jpg'
    segmentation_object = ImageSegmentation(image_path)
    segmentation_object.run_segmentation()