% Fractal Generation using Mandelbrot Set Algorithm
% This script demonstrates the use of iterative functions to generate fractals,
% specifically the Mandelbrot set.

% Define the function that calculates the next value in the sequence for a given point
function z = mandelbrot_set(c, max_iter)
    z = complex(0);
    for i = 1:max_iter
        if abs(z) > 2
            return;
        end
        z = z^2 + c;
    end
end

% Define the function that generates the fractal image
function img = generate_fractal(min_x, max_x, min_y, max_y, width, height)
    % Initialize the image with zeros
    img = zeros(height, width, 'uint8');
    
    % Calculate the range of real and imaginary parts for the complex plane
    dx = (max_x - min_x) / (width - 1);
    dy = (max_y - min_y) / (height - 1);
    
    % Iterate over each pixel in the image
    for i = 1:width
        for j = 1:height
            c = complex(min_x + i * dx, min_y + j * dy);
            iterations = mandelbrot_set(c, 100);
            if iterations < 100
                % Map the number of iterations to a color value
                img(j, i) = uint8(255 - (iterations / 100) * 255);
            end
        end
    end
end

% Generate and display the fractal image
min_x = -2.5;
max_x = 1.0;
min_y = -1.5;
max_y = 1.5;
width = 800;
height = 600;

img = generate_fractal(min_x, max_x, min_y, max_y, width, height);
figure;
imshow(img);

% Display the fractal image
title('Mandelbrot Set Fractal');