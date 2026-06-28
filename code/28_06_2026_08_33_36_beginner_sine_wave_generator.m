% Sine Wave Generator
%
% This script generates a sine wave with adjustable frequency and amplitude.

% Define the function to generate the sine wave
function y = sineWave(t, f, A)
    % t: time array (input)
    % f: frequency (input)
    % A: amplitude (input)
    % y: output signal

    % Calculate the sine of each time point
    y = A * sin(2 * pi * f * t);
end

% Define the main function to generate and plot the sine wave
function main()
    % Set the parameters
    frequency = 1;  % Default frequency (Hz)
    amplitude = 1;   % Default amplitude
    time = 0:0.01:10;  % Time array (seconds)

    % Generate the sine wave
    signal = sineWave(time, frequency, amplitude);

    % Plot the sine wave
    plot(time, signal);
    title('Sine Wave Generator');
    xlabel('Time (s)');
    ylabel('Amplitude');
end

% Run the main function
main()