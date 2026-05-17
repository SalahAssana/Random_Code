import numpy as np
from PIL import Image
import colorsys

class ComplexNumber:
    def __init__(self, real, imag):
        self.real = real
        self.imag = imag

    def conjugate(self):
        return ComplexNumber(self.real, -1 * self.imag)

    def magnitude_squared(self):
        return (self.real ** 2) + (self.imag ** 2)

class FractalGenerator:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.image = np.zeros((height, width), dtype=np.uint8)
        self.escape_value = 4.0

    def generate_mandelbrot(self, xmin, xmax, ymin, ymax):
        for x in range(self.width):
            for y in range(self.height):
                c_real = (x / self.width * (xmax - xmin) + xmin) 
                c_imag = (y / self.height * (ymax - ymin) + ymin)
                z = ComplexNumber(0.0, 0.0)
                for i in range(256):
                    z_squared = z.conjugate() * z
                    z_real = z_squared.real + c_real
                    z_imag = z_squared.imag + c_imag
                    z = ComplexNumber(z_real, z_imag)
                    if z.magnitude_squared() > self.escape_value:
                        h = int(255 * i / 256.0)
                        v = int(255 * (1 - z.imag / np.sqrt(z.magnitude_squared())) / 2.0)
                        self.image[y][x] = 0x1000000 | (h << 16) | (v << 8)
                        break
        return self.image

    def save_image(self, filename):
        img = Image.fromarray(self.image)
        img.save(filename)

if __name__ == '__main__':
    generator = FractalGenerator(800, 600)
    image = generator.generate_mandelbrot(-2.0, 1.0, -1.5, 1.5)
    generator.save_image('mandelbrot.png')