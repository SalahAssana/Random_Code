% Fractal Generator - Mandelbrot Set
%
% Copyright 2023, [Your Name]
%
% This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License.
%
% This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
%
% You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.

function fractal_generator

    % Define constants
    MIN_X = -2.5;
    MAX_X = 1.0;
    MIN_Y = -1.5;
    MAX_Y = 1.5;

    % Set the resolution of the image (increase for higher quality)
    RESOLUTION = 800;

    % Create a figure with a specified size
    fig = figure('Name', 'Mandelbrot Fractal', 'NumberTitle', 'off');
    set(fig, 'Position', [100 100 1024 768]);

    % Define the function to generate the fractal image
    function img = generate_fractal(min_x, max_x, min_y, max_y)
        x = (max_x - min_x) * linspace(0, 1, RESOLUTION) + min_x;
        y = (max_y - min_y) * linspace(0, 1, RESOLUTION) + min_y;

        % Initialize the image with zeros
        img = zeros(size(x));

        % Iterate over each pixel and calculate its distance from the origin
        for i = 1:RESOLUTION
            for j = 1:RESOLUTION
                z = complex(0);
                c = complex(x(i), y(j));

                % Calculate the Mandelbrot set for this pixel
                for k = 1:100
                    if abs(z) > 2
                        img(i, j) = k;
                        break;
                    end
                    z = z^2 + c;
                end
            end
        end

        % Normalize the image values to a range of [0, 255]
        img = uint8((img - min(img(:))) / (max(img(:)) - min(img(:))) * 255);
    end

    % Generate and display the fractal image
    img = generate_fractal(MIN_X, MAX_X, MIN_Y, MAX_Y);

    % Display the generated fractal image
    imshow(img);

end