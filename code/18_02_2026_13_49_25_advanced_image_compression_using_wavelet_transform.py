from scipy import signal
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image

class WaveletTransformer:
    def __init__(self, image):
        self.image = image
        self.height, self.width = image.size
        self.approximation_coefficients = None
        self.detail_coefficients = None

    def wavelet_transform(self):
        coefficients = []
        for y in range(0, self.height, 2**7): 
            for x in range(0, self.width, 2**7):
                subimage = self.get_subimage(y, x)
                coeffs = signal.cwt(subimage, 'haar', [i/100.0 for i in range(1, 11)])
                coefficients.append(coeffs)

        return coefficients

    def get_subimage(self, y, x):
        subimage = []
        for dy in range(min(2**7, self.height - y), min(2**8, self.height)):
            row = []
            for dx in range(min(2**7, self.width - x)):
                pixel = (self.image.getpixel((x + dx, y + dy))[0] / 255.0) ** 2
                row.append(pixel)
            subimage.append(row)
        return np.array(subimage)

    def plot_coefficients(self, coefficients):
        fig, axes = plt.subplots(nrows=len(coefficients), ncols=1, figsize=(10, 30))
        for i, ax in enumerate(axes):
            ax.imshow(np.abs(coefficients[i]).T, cmap='hot', interpolation='nearest')
            ax.set_title(f"Wavelet Coefficients at {i}")
        plt.show()

    def compress_image(self):
        coefficients = self.wavelet_transform()
        approximation_coefficients = []
        detail_coefficients = []
        for i in range(len(coefficients)):
            low_pass_coeffs, high_pass_coeffs = signal.cwt_coeff(cA=coefficients[i][:, 0], cD=coefficients[i][:, -1])
            approximation_coefficients.append(low_pass_coeffs)
            detail_coefficients.append(high_pass_coeffs)

        return approximation_coefficients, detail_coefficients

    def reconstruct_image(self, coefficients):
        reconstructed_image = np.zeros((self.height, self.width))
        for i in range(len(coefficients)):
            y, x = 0, 0
            for dy in range(min(2**7, self.height), min(2**8, self.height)):
                for dx in range(self.width):
                    if (y + dy) % 2**7 == 0 and (x + dx) % 2**7 == 0:
                        reconstructed_image[y+dy][x+dx] = coefficients[i][y][x]
                    y += 1
                x += 1

        return reconstructed_image

    def plot_reconstructed_image(self, image):
        plt.imshow(np.sqrt(image).T, cmap='hot', interpolation='nearest')
        plt.show()

if __name__ == '__main__':
    image = Image.open('image.png').convert('L')
    transformer = WaveletTransformer(image)
    coefficients = transformer.compress_image()
    reconstructed_image = transformer.reconstruct_image(coefficients[0])
    transformer.plot_reconstructed_image(reconstructed_image)