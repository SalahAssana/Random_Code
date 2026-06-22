% SIR Disease Model Simulator

% Define constants
N = 1000; % Total population
gamma = 1/7; % Recovery rate (1/days)
beta = 0.0005; % Infection rate per day per infected person
I0 = 1; % Initial number of infected individuals
S0 = N - I0; % Initial susceptible population

% Time parameters
T = 365; % Total simulation time in days
dt = 1/30; % Time step (days)

% Initialize arrays for S, I, R and t
t = 0:dt:T;
S = zeros(size(t));
I = zeros(size(t));
R = zeros(size(size(t)));

% Initial conditions
S(1) = S0;
I(1) = I0;
R(1) = 0;

% Main simulation loop
for i = 2:length(t)
    Ntilde = S(i-1) + I(i-1);
    dSdt = -beta * (S(i-1)/Ntilde) * I(i-1);
    dIdt = beta * (S(i-1)/Ntilde) * I(i-1) - gamma * I(i-1);
    dRdt = gamma * I(i-1);
    
    S(i) = S(i-1) + dt*dSdt;
    I(i) = I(i-1) + dt*dIdt;
    R(i) = R(i-1) + dt*dRdt;
end

% Plot the results
figure;
plot(t, S, 'b', t, I, 'r', t, R, 'g');
xlabel('Time (days)');
ylabel('Number of individuals');
title('SIR Disease Model Simulator');

% Define a function to compute the reproductive number
function R0 = calculateR0(N, gamma, beta)
    R0 = beta * N / gamma;
end

if nargin == 0
    % Run the simulation and plot the results if script is run directly
    SIR_simulator();
else
    % Call the function to compute the reproductive number
    R0 = calculateR0(N, gamma, beta);
    fprintf('The reproductive number (R0) is %.2f.\n', R0);
end

function [S, I, R] = SIR_simulator()
    N = 1000; % Total population
    gamma = 1/7; % Recovery rate (1/days)
    beta = 0.0005; % Infection rate per day per infected person
    I0 = 1; % Initial number of infected individuals
    S0 = N - I0; % Initial susceptible population
    
    t = 0:dt:T;
    S = zeros(size(t));
    I = zeros(size(t));
    R = zeros(size(size(t)));
    
    S(1) = S0;
    I(1) = I0;
    R(1) = 0;
    
    for i = 2:length(t)
        Ntilde = S(i-1) + I(i-1);
        dSdt = -beta * (S(i-1)/Ntilde) * I(i-1);
        dIdt = beta * (S(i-1)/Ntilde) * I(i-1) - gamma * I(i-1);
        dRdt = gamma * I(i-1);
        
        S(i) = S(i-1) + dt*dSdt;
        I(i) = I(i-1) + dt*dIdt;
        R(i) = R(i-1) + dt*dRdt;
    end