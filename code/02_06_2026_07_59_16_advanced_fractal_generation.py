import numpy as np
import matplotlib.pyplot as plt

class ComplexNumber:
    def __init__(self, real=0, imag=0):
        self.real = real
        self.imag = imag

    def __add__(self, other):
        return ComplexNumber(self.real + other.real, self.imag + other.imag)

    def __mul__(self, other):
        real_part = self.real * other.real - self.imag * other.imag
        imag_part = self.real * other.imag + self.imag * other.real
        return ComplexNumber(real_part, imag_part)

    def magnitude(self):
        return np.sqrt(self.real**2 + self.imag**2)


class Mandelbrot:
    def __init__(self, width=800, height=600, max_iter=256):
        self.width = width
        self.height = height
        self.max_iter = max_iter

    def generate_fractal(self):
        complex_plane = np.zeros((self.height, self.width), dtype=np.uint8)
        for y in range(self.height):
            for x in range(self.width):
                c = ComplexNumber(x / (self.width - 1) * 3.5 - 2.5,
                                  y / (self.height - 1) * 2 - 1)
                z = ComplexNumber(0, 0)
                for i in range(self.max_iter):
                    if z.magnitude() > 2:
                        complex_plane[y, x] = i
                        break
                    z = c + z * z
        return complex_plane

    def display_fractal(self, fractal):
        plt.imshow(fractal, cmap='hot', interpolation='none')
        plt.show()


def main():
    mandelbrot = Mandelbrot()
    fractal = mandelbrot.generate_fractal()
    mandelbrot.display_fractal(fractal)


if __name__ == '__main__':
    main()