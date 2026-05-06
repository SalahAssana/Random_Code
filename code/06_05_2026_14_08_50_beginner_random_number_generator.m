% Random Number Generator in MATLAB

% Initialize random number generator for reproducibility
rng('default')

% Define possible distributions (uniform, normal)
distributions = {'uniform', 'normal'};

% Ask user to select a distribution
distribution = input('Enter the desired distribution (uniform/normal): ', 's');

% Check if the entered distribution is valid
if any(strcmp(distribution, distributions))
    % Generate random numbers based on the selected distribution
    if strcmp(distribution, 'uniform')
        % Uniform distribution: 0 to 1
        r = rand(1);
    elseif strcmp(distribution, 'normal')
        % Normal distribution: mean = 0, std dev = 1
        r = normrnd(0, 1, 1, 1);
    end
    
    % Display the generated random number(s)
    fprintf('Random number: %.4f\n', r);
else
    error('Invalid distribution. Please enter uniform or normal.');
end