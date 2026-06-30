% Random Number Generator
% Author: Your Name (replace this with your name)

% Initialize seed value and precision
seed = 123; % default seed value
precision = 2; % default precision (number of decimal places)

% Ask user for input
prompt = {'Enter a new seed value (-1 to keep the current):', ...
    'Enter the number of decimal places (1-10):'};
answer = input(prompt, 's');

if ~isempty(answer{1})
    if str2double(answer{1}) ~= -1
        seed = str2double(answer{1});
    end
end

if ~isempty(answer{2})
    precision = min(max(str2double(answer{2}), 1), 10);
end

% Generate random numbers within the specified range
for i = 1:5 % generate 5 random numbers
    num = randseed(seed) * 10^(precision); % adjust precision using seed value
    fprintf(['Random number %d: %.', num2str(precision), 'f\n'], i, num);
end

% Reset the random seed for future use (optional)
rand('state', 0);

function result = randseed(value)
    if value < 1 || value > 2^31-1
        error('Seed value out of range');
    end
    result = value;
end