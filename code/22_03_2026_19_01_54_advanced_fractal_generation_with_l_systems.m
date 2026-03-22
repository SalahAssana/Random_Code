% L-System Fractal Generation in MATLAB

classdef LSystemGenerator
    methods
        function obj = LSystemGenerator(axiom, rules)
            % Constructor for the LSystemGenerator class
            obj.axiom = axiom;
            obj.rules = rules;
            obj.iterations = 0;
        end
        
        function generate(obj, iterations)
            % Generate the fractal by applying the L-system rules
            current_string = obj.axiom;
            for i = 1:iterations
                new_string = '';
                for char = current_string
                    if ismember(char, {'+', '-', '.'})
                        % Apply the rules based on the character type
                        if char == '+'
                            new_string = [new_string, applyRule(obj.rules, 'F')];
                        elseif char == '-'
                            new_string = [new_string, applyRule(obj.rules, 'G')];
                        elseif char == '.'
                            new_string = [new_string, applyRule(obj.rules, 'X')];
                    else
                        % Keep the character as it is
                        new_string = [new_string, char];
                    end
                end
                current_string = new_string;
                obj.iterations = i;
            end
            
            % Plot the fractal using the generated string
            plotFractal(current_string);
        end
        
        function rule = applyRule(rules, char)
            % Apply the L-system rules based on the character type
            for i = 1:length(rules)
                if rules{i}(1) == char
                    rule = rules{i}(2:end);
                    return;
                end
            end
            % Default rule: keep the character as it is
            rule = char;
        end
    end
    
end

function plotFractal(string)
    % Plot the fractal using the generated string
    x = 0;
    y = 0;
    for i = 1:length(string)
        switch string(i)
            case 'F'
                x = x + cos(pi/2);
                y = y + sin(pi/2);
            case 'G'
                x = x - cos(pi/2);
                y = y - sin(pi/2);
            case 'X'
                % No movement, just plot the point
                plot(x, y, 'o');
        end
    end
end

% Example usage:
axiom = 'F';
rules = {'FF', '+FG+F+G-', '-F-G+F+GG'};
generator = LSystemGenerator(axiom, rules);
generator.generate(6);

% Add more rules and iterations to generate different fractals.