import numpy as np
from scipy.ndimage import convolve
import matplotlib.pyplot as plt

class ImageProcessor:
    def __init__(self, image):
        self.image = image.copy()

    def apply_filter(self, filter_kernel):
        filtered_image = convolve(self.image, filter_kernel)
        return filtered_image

    def display_results(self, original_image, filtered_image):
        fig, axs = plt.subplots(1, 2, figsize=(12, 6))
        axs[0].imshow(original_image, cmap='gray')
        axs[0].set_title('Original Image')
        axs[1].imshow(filtered_image, cmap='gray')
        axs[1].set_title('Filtered Image')
        plt.show()

def main():
    # Load synthetic image data
    original_image = np.random.rand(256, 256)

    # Define edge detection filter kernel (Laplacian of Gaussian)
    filter_kernel = np.array([[0, -1, 0],
                               [-1, 5, -1],
                               [0, -1, 0]]) / 9

    # Create an instance of the ImageProcessor class
    image_processor = ImageProcessor(original_image)

    # Apply the edge detection filter
    filtered_image = image_processor.apply_filter(filter_kernel)

    # Display the original and filtered images
    image_processor.display_results(original_image, filtered_image)

if __name__ == '__main__':
    main()