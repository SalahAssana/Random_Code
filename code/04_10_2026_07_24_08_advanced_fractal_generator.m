% Fractal Generator
classdef FractalGenerator < handle
    methods
        function obj = FractalGenerator(n, r)
            % Initialize fractal generation parameters
            obj.n = n;  % Number of iterations
            obj.r = r;  % Recursive scaling factor
        end
        
        function [x, y] = generate(obj)
            % Generate the Sierpinski Carpet Fractal using complex arithmetic
            z = 0;
            for i = 1:obj.n
                if abs(z) < 2
                    r = obj.r * exp(1i * atan2(imag(z), real(z)));
                    z = z + r;
                end
                x(i) = real(z);
                y(i) = imag(z);
            end
        end
    end
    
end

% Main script to generate and plot the fractal
if nargin < 1 || nargin > 2
    error('Usage: FractalGenerator(n, r)');
end
n = 10;
r = 0.5;

fg = FractalGenerator(n, r);
[x, y] = fg.generate();

% Plot the fractal
figure;
plot(x, y, 'o');
xlabel('Real Axis');
ylabel('Imaginary Axis');
title('Sierpinski Carpet Fractal');