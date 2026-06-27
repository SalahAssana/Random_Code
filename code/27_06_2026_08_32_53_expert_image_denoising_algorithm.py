import numpy as np
from scipy import signal
import cv2
import time
from functools import partial

class ImageDenoiser:
    def __init__(self, image_path):
        self.image_path = image_path
        self.image = cv2.imread(self.image_path)
        self.noise_level = 0.1

    @staticmethod
    def compute_wavelet_transform(image):
        coefficients = []
        for level in range(3):
            a_coeffs, d_coeffs = pywt.wavedec(image, 'haar', level=level)
            coefficients.append(a_coeffs)
            coefficients.append(d_coeffs)
        return coefficients

    @staticmethod
    def reconstruct_image(coefficients):
        image = 0
        for level, (a_coeffs, d_coeffs) in enumerate(zip(*coefficients)):
            if a_coeffs is not None:
                image += pywt.wavethresh(a_coeffs, threshold=0.1)['coif']
        return image

    @staticmethod
    def denoise_wavelet(coefficients):
        denoised_coefficients = []
        for level, (a_coeffs, d_coeffs) in enumerate(zip(*coefficients)):
            if a_coeffs is not None:
                denoised_a_coeffs = pywt.threshold(a_coeffs, threshold=0.1, mode='soft')
                denoised_d_coeffs = signal.medfilt(d_coeffs, kernel_size=(3, 3))
                denoised_coefficients.append((denoised_a_coeffs, denoised_d_coeffs))
            else:
                denoised_coefficients.append((None, None))
        return denoised_coefficients

    @staticmethod
    def compute_median_filter(image):
        kernel = np.ones((5, 5)) / 25
        return signal.convolve2d(image, kernel, mode='same')

    def apply_denoising(self):
        coefficients = self.compute_wavelet_transform(self.image)
        denoised_coefficients = self.denoise_wavelet(coefficients)
        denoised_image = self.reconstruct_image(denoised_coefficients)
        denoised_image = cv2.cvtColor(denoised_image.astype(np.uint8), cv2.COLOR_BGR2GRAY)
        denoised_image = cv2.medianBlur(denoised_image, 5)
        return denoised_image

    def save_denoised_image(self):
        denoised_image = self.apply_denoising()
        cv2.imwrite('denoised_image.png', denoised_image)

if __name__ == '__main__':
    image_path = 'image.jpg'
    denoiser = ImageDenoiser(image_path)
    denoiser.save_denoised_image()