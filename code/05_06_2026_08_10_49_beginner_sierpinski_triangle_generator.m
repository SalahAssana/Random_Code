% Sierpinski Triangle Generator in MATLAB

% Define the initial triangle
x = [0 1 0];
y = [0 0 1];

% Function to generate the Sierpinski triangle
function [new_x, new_y] = sierpinski(x, y)
    % Base case: If there is only one point left, return
    if length(x) == 3
        return
    end
    
    % Calculate the midpoints of the sides
    m1 = (x(2)+x(1))/2;
    m2 = (x(3)+x(1))/2;
    m3 = (x(3)+x(2))/2;
    
    % Create a new triangle with the midpoints and the original points
    new_x = [x(1) m1 x(2)];
    new_y = [y(1) y(1) y(2)];
    
    % Recursively generate the Sierpinski triangle for each half
    sierpinski(new_x, new_y);
    sierpinski([m1 x(2) m3], [y(1) y(2) y(2)]);
    sierpinski([x(1) m1 m2], [y(1) y(1) y(1)]);
end

% Generate the Sierpinski triangle
sierpinski(x, y);

% Plot the generated Sierpinski triangle
plot(x,y,'-o');
xlabel('X-axis');
ylabel('Y-axis');
title('Sierpinski Triangle');