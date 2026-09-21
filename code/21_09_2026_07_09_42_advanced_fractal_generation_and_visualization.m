% Fractal Generation and Visualization
% Author: <Your Name>

classdef MandelbrotFractal
    methods
        function obj = MandelbrotFractal(xmin,xmax,ymin,ymax,width,height,maxIter)
            % Initialize fractal parameters
            obj.xmin = xmin;
            obj.xmax = xmax;
            obj.ymin = ymin;
            obj.ymax = ymax;
            obj.width = width;
            obj.height = height;
            obj.maxIter = maxIter;
        end
        
        function [image, boundary] = generateFractal(obj)
            % Initialize complex plane
            cReal = linspace(obj.xmin, obj.xmax, obj.width);
            cImag = linspace(obj.ymin, obj.ymax, obj.height);
            
            % Pre-allocate image and boundary arrays
            image = zeros(obj.height, obj.width, 'uint8');
            boundary = zeros(obj.height, obj.width, 3, 'single');
            
            % Iterate over complex plane
            for i = 1:obj.height
                for j = 1:obj.width
                    zReal = cReal(j);
                    zImag = cImag(i);
                    iter = 0;
                    
                    % Calculate Mandelbrot set
                    while (zReal^2 + zImag^2 <= 4 && iter < obj.maxIter)
                        zTemp = zReal^2 - zImag^2 + cReal(j);
                        zImag = 2 * zReal * zImag + cImag(i);
                        zReal = zTemp;
                        iter = iter + 1;
                    end
                    
                    % Color the image based on iteration count
                    if iter == obj.maxIter
                        image(i, j) = 255;  % Black for escape
                    else
                        image(i, j) = uint8(255 * (iter / obj.maxIter));
                    end
                    
                    % Calculate boundary color
                    if (zReal^2 + zImag^2 <= 4)
                        boundary(i, j, :) = [0, 0, 1];  % Blue for boundary
                    else
                        boundary(i, j, :) = [255, 255, 255];  % White for background
                    end
                end
            end
            
            % Display the fractal image
            imshow(image);
        end
    end
end

% Main script to test MandelbrotFractal class
if nargout == 0
    obj = MandelbrotFractal(-2.5, 1.5, -1.5, 1.5, 800, 600, 256);
    [image, boundary] = obj.generateFractal;
end