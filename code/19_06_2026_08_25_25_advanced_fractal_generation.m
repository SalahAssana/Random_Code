% Fractal Generation in MATLAB

classdef FractalGenerator
    methods
        function obj = FractalGenerator(iterations, scale)
            % Initialize recursive algorithm parameters
            obj.iterations = iterations;
            obj.scale = scale;
        end
        
        function fractal = generate(obj)
            % Initialize the linked list to store points
            points = linkedlist();
            
            % Recursively add points to the linked list
            [points, ~] = obj.addPoints(points);
            
            % Convert the linked list to a matrix for plotting
            fractal = cell2mat(matrixify(points));
        end
        
        function [new_points, new_scale] = addPoints(obj, points)
            % Base case: if we've reached the maximum iterations, stop
            if obj.iterations == 0
                return
            end
            
            % Calculate the midpoint of the current set of points
            midpoint_x = sum([points.x]) / size(points, 2);
            midpoint_y = sum([points.y]) / size(points, 2);
            
            % Create new points by scaling and translating the midpoint
            new_points = struct('x', [], 'y', []);
            for i = 1:obj.scale
                new_points(i).x = midpoint_x + rand() * (0.5 - obj.scale/2);
                new_points(i).y = midpoint_y + rand() * (0.5 - obj.scale/2);
            end
            
            % Recursively add the new points to the linked list
            [new_points, ~] = obj.addPoints(FractalGenerator(obj.iterations-1, obj.scale/3), new_points);
            
            % Update the scale for the next iteration
            new_scale = obj.scale / 3;
        end
        
        function matrix = matrixify(points)
            % Convert the linked list to a matrix
            matrix = zeros(size(points, 2), 2);
            i = 1;
            while ~isempty(points)
                point = points.dequeue();
                matrix(i, :) = [point.x; point.y];
                i = i + 1;
            end
        end
    end
    
end

% Main function to test the FractalGenerator class
function main()
    % Create a fractal generator with 10 iterations and a scale of 3
    generator = FractalGenerator(10, 3);
    
    % Generate the fractal
    fractal = generator.generate();
    
    % Plot the fractal
    plot(fractal(:, 1), fractal(:, 2));
end

main()