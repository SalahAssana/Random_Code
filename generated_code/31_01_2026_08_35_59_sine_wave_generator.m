% Sine Wave Generator
% Generate a sine wave with adjustable frequency and amplitude

% Define the time array (0 to 10 seconds)
t = 0:0.01:10;

% Define the initial parameters
frequency = 1;  % Hz
amplitude = 1;   % units

% Calculate the sine wave using the defined frequency and amplitude
sine_wave = amplitude * sin(2 * pi * frequency * t);

% Plot the sine wave
plot(t, sine_wave);
xlabel('Time (seconds)');
ylabel('Amplitude');
title('Sine Wave Generator');

% Prompt user to adjust the frequency and amplitude
prompt = 'Enter a new frequency (Hz) or 0 to keep current: ';
new_frequency = input(prompt);
if new_frequency ~= 0
    frequency = new_frequency;
end

prompt = 'Enter a new amplitude: ';
new_amplitude = input(prompt);
if ~isempty(new_amplitude)
    amplitude = str2num(new_amplitude);
end

% Recalculate and plot the sine wave with the new parameters
sine_wave = amplitude * sin(2 * pi * frequency * t);
plot(t, sine_wave);
xlabel('Time (seconds)');
ylabel('Amplitude');
title('Sine Wave Generator');