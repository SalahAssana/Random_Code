import cv2
import numpy as np
from matplotlib import pyplot as plt

class ImageProcessor:
    def __init__(self):
        pass

    def blur(self, image_path):
        # Read the input image
        img = cv2.imread(image_path)

        # Apply Gaussian Blur
        blurred_img = cv2.GaussianBlur(img, (5, 5), 0)

        # Display the original and blurred images
        plt.subplot(121), plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
        plt.title('Original'), plt.xticks([]), plt.yticks([])
        plt.subplot(122), plt.imshow(cv2.cvtColor(blurred_img, cv2.COLOR_BGR2RGB))
        plt.title('Blurred'), plt.xticks([]), plt.yticks([])
        plt.show()

    def sharpen(self, image_path):
        # Read the input image
        img = cv2.imread(image_path)

        # Apply Sharpen Filter
        kernel = np.array([[-1,-1,-1], [-1,9,-1], [-1,-1,-1]])
        sharpened_img = cv2.filter2D(img, -1, kernel)

        # Display the original and sharpened images
        plt.subplot(121), plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
        plt.title('Original'), plt.xticks([]), plt.yticks([])
        plt.subplot(122), plt.imshow(cv2.cvtColor(sharpened_img, cv2.COLOR_BGR2RGB))
        plt.title('Sharpened'), plt.xticks([]), plt.yticks([])
        plt.show()

    def threshold(self, image_path):
        # Read the input image
        img = cv2.imread(image_path)

        # Convert to grayscale and apply thresholding
        gray_img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        ret, thresh_img = cv2.threshold(gray_img, 127, 255, cv2.THRESH_BINARY)

        # Display the original, grayscale, and thresholded images
        plt.subplot(131), plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
        plt.title('Original'), plt.xticks([]), plt.yticks([])
        plt.subplot(132), plt.imshow(gray_img, cmap='gray')
        plt.title('Grayscale'), plt.xticks([]), plt.yticks([])
        plt.subplot(133), plt.imshow(thresh_img, cmap='gray')
        plt.title('Thresholded'), plt.xticks([]), plt.yticks([])
        plt.show()

if __name__ == '__main__':
    processor = ImageProcessor()
    processor.blur('image1.jpg')
    processor.sharpen('image2.jpg')
    processor.threshold('image3.jpg')