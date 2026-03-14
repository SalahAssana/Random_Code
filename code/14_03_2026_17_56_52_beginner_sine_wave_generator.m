% Sine Wave Generator
% Generate a sine wave given its frequency and amplitude
% Suitable for audio processing applications

% Initialize time vector (0 to 2pi seconds)
t = 0:0.01:6.28;

% Define the frequency and amplitude of the sine wave
freq = 440; % Hz (A4)
amp = 1;

% Generate the sine wave using MATLAB's built-in function
y = amp * sin(2 * pi * freq * t);

% Plot the generated sine wave
plot(t, y);
xlabel('Time (s)');
ylabel('Amplitude');
title('Sine Wave Generator');
grid on;