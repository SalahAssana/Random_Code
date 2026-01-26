% Sierpinski Triangle Generator in MATLAB

function sierpinski(n)
    % Base case: If n is 0, draw a single point
    if n == 0
        plot(0, 0, 'o');
    else
        % Recursive case: Draw the triangle and then recursively generate the three smaller triangles
        x = 0.5^n;         % Calculate the side length of the triangle
        y = sqrt(3)/2*x;   % Calculate the height of the triangle
        
        % Plot the triangle
        plot([x, 0, x], [y, y, 0], 'k-');
        
        % Recursively generate the three smaller triangles
        sierpinski(n - 1);
        sierpinski(n - 1);
        sierpinski(n - 1);
    end
end

% Run the function to generate the Sierpinski triangle
sierpinski(4);