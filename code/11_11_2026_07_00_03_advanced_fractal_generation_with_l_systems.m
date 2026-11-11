% LSystem Fractal Generation

classdef LSystem
    properties
        axiom
        productionRules
        iterationCount
    end
    
    methods
        function obj = LSystem(axiom, rules, iterations)
            obj.axiom = axiom;
            obj.productionRules = rules;
            obj.iterationCount = iterations;
        end
        
        function str = generate(obj)
            str = obj.axiom;
            for i = 1:obj.iterationCount
                newStr = '';
                for c = str(:)'
                    switch(c{1})
                        case {'F'}
                            newStr = [newStr 'F'];
                        case {'+'}
                            newStr = [newStr '+'];
                        case {'-'}
                            newStr = [newStr '-'];
                        otherwise
                            for rule = obj.productionRules(:)'
                                if strcmp(rule{1}, c{1})
                                    newStr = [newStr, rule{2}];
                                end
                            end
                    end
                end
                str = newStr;
            end
        end
        
        function plotFractal(obj)
            hold on;
            for i = 1:length(obj.generate())
                switch(obj.generate()(i))
                    case 'F'
                        line([0 1], [0 0], 'Color', 'k');
                    case '+'
                        % Turn right
                        theta = pi/2;
                        x = cos(theta);
                        y = sin(theta);
                        plot([0, x], [0, y]);
                    case '-'
                        % Turn left
                        theta = -pi/2;
                        x = cos(theta);
                        y = sin(theta);
                        plot([0, x], [0, y]);
                end
            end
            hold off;
        end
        
    end
    
end

% Main script
if nargin < 1 || nargin > 3
    error('Usage: LSystemFractal(axiom, rules, iterations)');
else
    axiom = 'FX';
    rules = {'X -> F[-F]+F'};
    iterations = 7;
    
    lsys = LSystem(axiom, rules, iterations);
    lsys.plotFractal();
end
