% Project 5: Fractal Generation and Animation
% ADVANCED Complexity Level

classdef FractalGenerator < handle
    properties
        minReal
        maxReal
        minImag
        maxImag
    end
    
    methods
        function obj = FractalGenerator(minReal, maxReal, minImag, maxImag)
            obj.minReal = minReal;
            obj.maxReal = maxReal;
            obj.minImag = minImag;
            obj.maxImag = maxImag;
        end
        
        function [realGrid, imagGrid] = generateMandelbrot(obj, res)
            realGrid = zeros(res, res);
            imagGrid = zeros(res, res);
            
            for i = 1:res
                for j = 1:res
                    cReal = (obj.maxReal - obj.minReal) * (i / res) + obj.minReal;
                    cImag = (obj.maxImag - obj.minImag) * (j / res) + obj.minImag;
                    zReal = 0;
                    zImag = 0;
                    
                    for k = 1:100
                        zRealNew = zReal.^2 - zImag.^2 + cReal;
                        zImagNew = 2 .* zReal .* zImag + cImag;
                        
                        if (zRealNew^2 + zImagNew^2) > 4
                            realGrid(i, j) = zReal;
                            imagGrid(i, j) = zImag;
                            break;
                        end
                        
                        zReal = zRealNew;
                        zImag = zImagNew;
                    end
                end
            end
        end
        
        function animateMandelbrot(obj, realGrid, imagGrid)
            figure;
            for i = 1:100
                subplot(121);
                imagesc(realGrid, imagGrid);
                axis off;
                axis equal;
                title(['Iteration ', num2str(i)]);
                drawnow;
                
                subplot(122);
                imagesc(realGrid, imagGrid);
                axis off;
                axis equal;
                title(['Iteration ', num2str(i)]);
                drawnow;
            end
        end
    end
end

% Main Script
res = 400;
fractalGenerator = FractalGenerator(-2.0, 1.0, -1.5, 1.5);
[realGrid, imagGrid] = fractalGenerator.generateMandelbrot(res);

figure;
imagesc(realGrid, imagGrid);
axis off;
axis equal;

% Animate the Mandelbrot Fractal
animateMandelbrot(fractalGenerator, realGrid, imagGrid);