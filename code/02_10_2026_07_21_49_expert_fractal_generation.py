#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
from PIL import Image

class FractalGenerator:
    def __init__(self):
        self.image_width = 1024
        self.image_height = 1024
        self.iterations = 1000
        self.max_value = 2.0

    def mandelbrot(self, x, y, width, height):
        ca = (x / width) * self.max_value + (-self.max_value / 2)
        cb = (y / height) * self.max_value + (-self.max_value / 2)

        zr = 0.0
        zi = 0.0

        for i in range(self.iterations):
            if abs(zr) > self.max_value or abs(zi) > self.max_value:
                return 255 - int((i * 256) / self.iterations)
            zr_new = zr * zr - zi * zi + ca
            zi_new = 2.0 * zr * zi + cb
            zr, zi = zr_new, zi_new

        return 255

    def generate_fractal(self):
        img = Image.new('RGB', (self.image_width, self.image_height))
        pixels = np.zeros((self.image_width, self.image_height, 3), dtype=np.uint8)

        for x in range(self.image_width):
            for y in range(self.image_height):
                color = self.mandelbrot(x, y, self.image_width, self.image_height)
                if color > 0:
                    pixels[x, y, :] = (255, int(color * 2.55), 0)

        img.putdata(pixels.flatten())
        img.save('fractal.png')

    def main(self):
        generator = FractalGenerator()
        generator.generate_fractal()

if __name__ == '__main__':
    main()