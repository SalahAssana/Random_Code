% Simple PID Controller in MATLAB
%
% This is a simple Proportional-Integral-Derivative (PID) controller that 
% adjusts the setpoint to regulate a system's behavior.

% Define the parameters for the PID controller
Kp = 1; % proportional gain
Ki = 0.5; % integral gain
Kd = 0.2; % derivative gain

% Initialize the error and previous errors
error = 0;
prev_error = 0;

% Simulate the system's behavior over time
t = 0:0.1:10; % time array (0 to 10 seconds)
u = zeros(size(t)); % input array
y = zeros(size(t)); % output array

for i = 1:length(t)
    % Measure the current output and calculate the error
    y(i) = sin(2*pi*t(i));
    error = y(i) - 0.5; % desired output is 0.5
    
    % Calculate the PID control signal
    p_term = Kp * error;
    i_term = Ki * sum(error(1:i));
    d_term = Kd * (error - prev_error) / 0.1;
    u(i) = p_term + i_term + d_term;
    
    % Update the previous error for the next iteration
    prev_error = error;
end

% Plot the results
plot(t, y, 'b', t, u, 'r')
xlabel('Time (s)')
ylabel('Output and Control Signal')
title('Simple PID Controller in MATLAB')