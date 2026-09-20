% Coin Flip Simulator
% Beginner-level project for MATLAB

% Initialize heads counter
heads = 0;

% Loop until player gets 10 heads in a row
while true
    % Randomly generate a coin flip (0 or 1)
    flip = randi([0, 1]);
    
    % If the flip is heads (1), increment the heads counter
    if flip == 1
        heads = heads + 1;
        
        % If the player got 10 heads in a row, break out of the loop
        if heads >= 10
            break
    else
        % Reset the heads counter for new attempts
        heads = 0
    end
    
    % Display the current state (heads or tails)
    if flip == 1
        disp('Heads')
    else
        disp('Tails')
    end
end

% Display the final result: player got 10 heads in a row!
disp('Congratulations! You got 10 heads in a row!')