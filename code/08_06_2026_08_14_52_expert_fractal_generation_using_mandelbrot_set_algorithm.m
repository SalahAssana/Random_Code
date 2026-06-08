% Fractal Generation using Mandelbrot Set Algorithm
%
% Copyright 2023 Your Name

function [] = generate_mandelbrot()
    % Define constants
    MAX_ITER = 1000;
    WIDTH = 800;
    HEIGHT = 600;
    XMIN = -2.5;
    XMAX = 1.0;
    YMIN = -1.5;
    YMAX = 1.5;

    % Create image
    img = zeros(HEIGHT, WIDTH);

    % Iterate over pixels
    for y = HEIGHT:-1:1
        for x = 1:WIDTH
            % Calculate complex number
            c_real = (x / WIDTH * (XMAX - XMIN) + XMIN);
            c_imag = (y / HEIGHT * (YMAX - YMIN) + YMIN);

            % Initialize variables
            z_real = 0;
            z_imag = 0;
            iter = 0;

            % Check if point is in Mandelbrot set
            while z_real^2 + z_imag^2 <= 4 && iter < MAX_ITER
                z_real_temp = z_real^2 - z_imag^2 + c_real;
                z_imag_temp = 2 * z_real * z_imag + c_imag;

                % Update variables
                z_real = z_real_temp;
                z_imag = z_imag_temp;

                % Increment iteration counter
                iter = iter + 1;
            end

            % Set pixel color based on iteration count
            if iter == MAX_ITER
                img(y, x) = 255;  % Black for points outside Mandelbrot set
            else
                img(y, x) = round(255 * (MAX_ITER - iter) / MAX_ITER);  % Color proportional to iteration count
            end
        end
    end

    % Display image
    imshow(img);
end