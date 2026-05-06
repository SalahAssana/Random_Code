import cv2
import numpy as np

class ImageProcessingPipeline:
    def __init__(self, image_path):
        self.image = cv2.imread(image_path)
        self.gray_image = None
        self.blur_image = None
        self.threshold_image = None
        self.edges_image = None

    def apply_threshold(self, threshold_value):
        _, self.threshold_image = cv2.threshold(
            gray_image=self.gray_image,
            thresh=threshold_value,
            maxval=255,
            type=cv2.THRESH_BINARY
        )

    def apply_blur(self, kernel_size):
        self.blur_image = cv2.GaussianBlur(
            src=self.image,
            ksize=(kernel_size, kernel_size),
            sigmaX=0,
            sigmaY=0
        )

    def apply_edges_detection(self, aperture_size):
        self.edges_image = cv2.Canny(
            image=self.blur_image,
            apertureSize=aperture_size,
            threshold1=100,
            threshold2=200
        )

    def display_results(self):
        cv2.imshow('Original', self.image)
        cv2.imshow('Grayscale', self.gray_image)
        cv2.imshow('Thresholded', self.threshold_image)
        cv2.imshow('Blurred', self.blur_image)
        cv2.imshow('Edges', self.edges_image)

        cv2.waitKey(0)
        cv2.destroyAllWindows()

    def process_image(self):
        # Convert the image to grayscale
        self.gray_image = cv2.cvtColor(
            src=self.image,
            dst=cv2.COLOR_BGR2GRAY
        )

        # Apply thresholding
        self.apply_threshold(threshold_value=127)

        # Apply blur filter
        self.apply_blur(kernel_size=5)

        # Apply edges detection
        self.apply_edges_detection(aperture_size=3)

    def main(self):
        if __name__ == '__main__':
            image_path = 'path_to_your_image.jpg'
            pipeline = ImageProcessingPipeline(image_path)
            pipeline.process_image()
            pipeline.display_results()

if __name__ == '__main__':
    img_pipeline = ImageProcessingPipeline('image.jpg')
    img_pipeline.main()