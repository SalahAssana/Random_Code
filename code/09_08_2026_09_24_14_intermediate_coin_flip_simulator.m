% Coin Flip Simulator
%
% This program simulates multiple coin flips and calculates statistics.

function results = coinFlipSimulator(numFlips)
    % Initialize variables
    heads = 0;
    tails = 0;

    for i = 1:numFlips
        % Simulate a single coin flip (heads or tails)
        if rand < 0.5
            heads = heads + 1;
        else
            tails = tails + 1;
        end
    end

    % Calculate statistics
    total = heads + tails;
    percentageHeads = (heads / total) * 100;
    percentageTails = (tails / total) * 100;

    results.heads = heads;
    results.tails = tails;
    results.total = total;
    results.percentageHeads = percentageHeads;
    results.percentageTails = percentageTails;
end

% Main program
if nargin == 0
    numFlips = 10000; % default number of flips
else
    numFlips = varargin{1};
end

results = coinFlipSimulator(numFlips);

fprintf('Heads: %d\n', results.heads);
fprintf('Tails: %d\n', results.tails);
fprintf('Total: %d\n', results.total);
fprintf('Percentage Heads: %.2f%%\n', results.percentageHeads);
fprintf('Percentage Tails: %.2f%%\n', results.percentageTails);