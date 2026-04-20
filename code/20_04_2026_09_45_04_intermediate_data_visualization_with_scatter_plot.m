% Data Visualization with Scatter Plot
% Author: [Your Name]
% Date: [Current Date]

% Define function to create scatter plot
function createScatterPlot(xData, yData, titleStr)
    % Create figure and axis
    fig = figure;
    ax = axes(fig);
    
    % Set title and labels
    xlabel('X-axis');
    ylabel('Y-axis');
    title(titleStr);
    
    % Plot data with custom colors and markers
    plot(ax, xData, yData, 'Marker', '*', 'MarkerSize', 10, ...
        'MarkerFaceColor', 'r', 'MarkerEdgeColor', 'b', 'LineStyle', '--');
    
    % Add annotations
    annotation(ax, 'textarrow', [0.5, 0.5], 'String', 'Target', ...
        'HeadStyle', 'vintage', 'FontSize', 12);
end

% Synthetic data generation function
function [xData, yData] = generateSyntheticData(numPoints)
    % Generate random x and y values
    xData = rand(1, numPoints) * 100;
    yData = sin(xData) + 0.5 * randn(size(xData));
end

% Main script
if nargin == 0
    numPoints = 50;  % Default number of points
else
    numPoints = varargin{1};
end

[xData, yData] = generateSyntheticData(numPoints);
createScatterPlot(xData, yData, 'Sine Wave Scatter Plot');