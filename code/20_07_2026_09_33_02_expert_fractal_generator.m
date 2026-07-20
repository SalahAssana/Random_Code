% Fractal Generator
% Author: [Your Name]
% Date: [Current Date]

% Import necessary libraries
import mfilename
import java.awt.image.BufferedImage
import javax.swing.JFrame
import java.awt.Graphics;
import java.awt.geom.Point2D;

clear all; clc;

% Define constants and parameters
MAGNIFICATION = 4; % Magnification factor for each iteration
ITERATIONS = 5; % Number of iterations to generate the fractal
WIDTH = 600; % Width of the generated image
HEIGHT = 600; % Height of the generated image
RESOLUTION = 0.1; % Resolution of the generated image

% Define the recursive function to generate the fractal
function [x, y] = mandelbrot(c, maxIt)
    z = complex(0, 0);
    it = 0;
    while (norm(z) < 2 && it < maxIt)
        z = z.^2 + c;
        it = it + 1;
    end
    if (it == maxIt)
        x = 255; % Color code for the boundary of the fractal
    else
        x = floor(255 * it / maxIt);
    end
end

% Define a helper function to generate the fractal image
function [img] = generate_fractal()
    img = zeros(WIDTH, HEIGHT, 'uint8');
    for i = 1:WIDTH
        for j = 1:HEIGHT
            c = complex((i - WIDTH / 2) * RESOLUTION, (j - HEIGHT / 2) * RESOLUTION);
            [x, y] = mandelbrot(c, ITERATIONS);
            img(i, j) = x;
        end
    end
end

% Define a function to display the generated fractal image
function [] = show_fractal(img)
    frame = struct('data', zeros(WIDTH, HEIGHT, 'uint8'));
    for i = 1:WIDTH
        for j = 1:HEIGHT
            frame.data(i, j) = img(i, j);
        end
    end
    frame.setTitle('Mandelbrot Fractal');
    JFrame(frame).setVisible(true);
end

% Main script to generate and display the fractal
function [] = main()
    img = generate_fractal();
    show_fractal(img);
end
