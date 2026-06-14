% Fractal Generator

% Import necessary libraries
import MATLAB.fltk.all;

classdef FractalGenerator < handle
    methods
        function obj = FractalGenerator()
            % Initialize fractal generator
            obj.size = 800;
            obj.center_x = 400;
            obj.center_y = 300;
            obj.iterations = 5;
            obj.color_map = [0.3, 0.2; 0.4, 0.8];
        end
        
        function generate_fractal(obj)
            % Create figure
            figure('Name', 'Fractal Generator');
            
            % Initialize fractal array
            fractal_array = zeros(obj.size, obj.size, 3);
            
            % Generate fractal
            for i = 1:obj.iterations
                for j = 1:obj.size
                    for k = 1:obj.size
                        if (k - obj.center_x)^2 + (j - obj.center_y)^2 <= (i / obj.iterations * 100) ^ 2
                            fractal_array(j, k, :) = [0.7, 0.3, 0.4];
                        end
                    end
                end
            end
            
            % Display fractal
            imagesc(fractal_array);
            colormap(obj.color_map);
            axis off;
            axis equal;
        end
        
    end
    
end

% Main function to run the fractal generator
function main()
    fg = FractalGenerator();
    fg.generate_fractal();
end

main();
