% Simple GUI Calculator
% Author: [Your Name]
% Complexity Level: BEGINNER

% Create figure for the calculator
fig = figure('Name', 'Simple Calculator');
set(fig, 'Position', [100 100 300 400]);

% Create text field for input
inputField = edit('Units', 'Normalized', 'Position', [0.1 0.8 0.8 0.05], 'BackgroundColor', 'white');

% Create buttons for basic arithmetic operations
buttonPanel = uipanel('Title', '', 'Units', 'Normalized', 'Position', [0.1 0.6 0.8 0.2]);
addButton = uibutton('Text', '+', 'Parent', buttonPanel, 'Units', 'Normalized');
subButton = uibutton('Text', '-', 'Parent', buttonPanel, 'Units', 'Normalized');
mulButton = uibutton('Text', '*', 'Parent', buttonPanel, 'Units', 'Normalized');
divButton = uibutton('Text', '/', 'Parent', buttonPanel, 'Units', 'Normalized');

% Create equals button
equalsButton = uibutton('Text', '=', 'Parent', fig, 'Units', 'Normalized');
set(equalsButton, 'Position', [0.6 0.7 0.4 0.05]);

% Define callback functions for buttons
function result = plusClick(src, eventdata)
    inputField.String = num2str(str2num(inputField.String) + 1);
end

function result = minusClick(src, eventdata)
    inputField.String = num2str(str2num(inputField.String) - 1);
end

function result = multiplyClick(src, eventdata)
    inputField.String = num2str(str2num(inputField.String) * 2);
end

function result = divideClick(src, eventdata)
    if str2num(inputField.String) ~= 0
        inputField.String = num2str(str2num(inputField.String) / 2);
    else
        inputField.String = 'Error: Division by zero';
    end
end

function result = equalsClick(src, eventdata)
    try
        output = str2num(inputField.String);
        if src.Text == '+'
            output = output + str2num(inputField.String);
        elseif src.Text == '-'
            output = output - str2num(inputField.String);
        elseif src.Text == '*'
            output = output * str2num(inputField.String);
        elseif src.Text == '/'
            if output ~= 0
                output = output / str2num(inputField.String);
            else
                output = 'Error: Division by zero';
            end
        end
        inputField.String = num2str(output);
    catch
        inputField.String = 'Error: Invalid input';
    end
end

% Set callback functions for buttons
set(addButton, 'ButtonDownFcn', @plusClick);
set(subButton, 'ButtonDownFcn', @minusClick);
set(mulButton, 'ButtonDownFcn', @multiplyClick);
set(divButton, 'ButtonDownFcn', @divideClick);
set(equalsButton, 'ButtonDownFcn', @equalsClick);

% Show the GUI
uiwait(fig);