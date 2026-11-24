% Fractal Generator
% ADVANCED Complexity Project

classdef FractalGenerator < handle
    properties
        image
        xMin
        xMax
        yMin
        yMax
        scale
    end
    
    methods
        function obj = FractalGenerator(xMin, xMax, yMin, yMax, scale)
            obj.xMin = xMin;
            obj.xMax = xMax;
            obj.yMin = yMin;
            obj.yMax = yMax;
            obj.scale = scale;
            obj.image = zeros(1000, 1000);
        end
        
        function generate(obj)
            [x, y] = meshgrid(linspace(obj.xMin, obj.xMax, size(obj.image, 1)), ...
                linspace(obj.yMin, obj.yMax, size(obj.image, 2)));
            
            for i = 1:size(obj.image, 1)
                for j = 1:size(obj.image, 2)
                    z = complex(x(i, j), y(i, j));
                    
                    for k = 1:100
                        if abs(z) > 2
                            obj.image(i, j) = 255;
                            return
                        end
                        
                        z = z^2 + (0.5 * exp(1i * pi) - 0.5);
                    end
                    
                    obj.image(i, j) = 255;
                end
            end
        end
        
        function display(obj)
            imagesc(obj.image); 
            axis off; 
            colormap gray; 
            title('Mandelbrot Set');
        end
    end
end

% Entry point
if nargin == 0 || ~exist('input', 'var')
    input = struct();
end

fg = FractalGenerator(-2.5, 1.5, -1.5, 1.5, 10);
fg.generate();
fg.display();

%pause(30); % To display the fractal